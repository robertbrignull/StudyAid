db = (require '../rest-mongo').db
coursesCollection = db.collection('coursemodels')

exports.methods = []

exports.methods.push
    name: 'coursemodel'
    type: 'get'
    params: []
    method: (req, res) ->
        coursesCollection.find().toArray (err, courses) ->
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
        coursesCollection.findById req.params._id, (err, course) ->
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

        coursesCollection.updateById req.params._id, {name: args.name}, {}, (err, n) ->
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
        coursesCollection.insert course, {}, (err, result) ->
            if err?
                console.log 'Error adding new course'
                console.log err
                res.send 500, {}
                return
            
            res.send 200, result[0]

exports.methods.push
    name: 'coursemodel'
    type: 'delete'
    params: ['_id']
    method: (req, res) ->
        coursesCollection.removeById req.params._id, {}, (err, n) ->
            if err?
                console.log 'Error deleting course'
                console.log err
                res.send 500, {}
                return

            res.send 200, {}