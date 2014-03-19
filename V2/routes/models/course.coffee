db = (require '../rest-mongo').db
ObjectID = (require 'mongoskin').ObjectID
courseCollection = db.collection('coursemodels')
factCollection = db.collection('factmodels')

async = require 'async'
latex = require '../latex'

exports.methods = []

exports.methods.push
    name: 'coursemodel'
    type: 'get'
    params: []
    method: (req, res) ->
        courseCollection.find().toArray (err, courses) ->
            if err?
                console.log 'Error finding all courses'
                console.log err
                res.send 500, {}
                return

            res.send 200, courses

exports.methods.push
    name: 'coursemodel'
    type: 'get'
    params: ['_id']
    method: (req, res) ->
        courseCollection.findById req.params._id, (err, course) ->
            if err?
                console.log 'Error finding course by id'
                console.log err
                res.send 500, {}
                return

            res.send 200, course

exports.methods.push
    name: 'coursemodel' 
    type: 'put'
    params: ['_id']
    method: (req, res) ->
        args = req.body.coursemodel

        # make sure all the arguments are there
        if not args.name?
            res.send 400, {}

        courseCollection.updateById req.params._id, {name: args.name}, {}, (err, n) ->
            if err?
                console.log 'Error updating course'
                console.log err
                res.send 500, {}
                return

            if n != 1
                console.log 'Tried to update nonexistance course'
                res.send 500, {}
                return

            res.send 200, {_id: req.params._id}

exports.methods.push
    name: 'coursemodel' 
    type: 'post'
    params: []
    method: (req, res) ->
        args = req.body.coursemodel

        # make sure all the arguments are there
        if not args.name?
            res.send 400, {}

        # create the new course object
        course =
            name: args.name

        # save it to the database
        courseCollection.insert course, {}, (err, result) ->
            if err?
                console.log 'Error adding new course'
                console.log err
                res.send 500, {}
                return
            
            res.send 200, {_id: result[0]._id}

exports.methods.push
    name: 'coursemodel'
    type: 'delete'
    params: ['_id']
    method: (req, res) ->
        # try to remove all facts as well, unfortunately we have to load them first
        factCollection.find({course: ObjectID(req.params._id)}).toArray (err, facts) ->
            if err?
                console.log 'Error finding facts while deleting course'
                console.log err
                res.send 500, {}
                return

            # delete the actual course in the database
            courseCollection.removeById req.params._id, {}, (err, n) ->
                if err?
                    console.log 'Error deleting course'
                    console.log err
                    res.send 500, {}
                    return

                # and delete all facts
                factCollection.remove {course: ObjectID(req.params._id)}, (err, n) ->
                    if err?
                        console.log 'Error deleting facts after deleting course'
                        console.log err
                        res.send 500, {}
                        return

                    # remove any rendered images
                    tasks = []
                    for fact in facts
                        tasks.push latex.remove fact

                    async.parallel tasks, (err) ->
                        if err?
                            console.log 'Error deleting images when deleting course'
                            console.log err
                            res.send 500, {}
                            return

                        res.send 200, {}
