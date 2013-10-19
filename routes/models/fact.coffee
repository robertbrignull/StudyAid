db = (require '../rest-mongo').db
ObjectID = (require 'mongoskin').ObjectID
factCollection = db.collection('factmodels')

{mergeFactWithType, findFactType} = require './factType'
async = require 'async'

exports.methods = []

createFact = (args, done) ->
    # make sure all the arguments are there
    if not args.name? or not args.course?
        done 400

    # construct the new fact in memory here
    fact = {}

    fact.name = args.name
    fact.course = ObjectID(args.course)
    fact.statement = args.statement

    fact.proofs = JSON.parse (args.proofs ? '[]')
    for proof in JSON.parse args.proofs
        proof.dependencies = (JSON.parse (proof.dependencies ? '[]')).map (d) -> ObjectID(d._id)

    # try to work out the type from the name
    findFactType args.type, (err, type) ->
        if err?
            console.log 'Error finding fact type'
            console.log err
            done 500
            return

        if not type?
            console.log 'No fact type found'
            done 400
            return

        fact.type = type._id

        done undefined, fact, type

getDependencies = (proof) -> (done) ->
    tasks = []
    if proof? and proof.dependencies?
        for dependency, i in proof.dependencies
            do (proof, dependency, i) ->
                tasks.push (callback) ->
                    factCollection.findById dependency, {_id: 1, name: 1}, (err, fact) ->
                        proof.dependencies[i] = fact
                        callback err

    async.parallel tasks, done

exports.methods.push
    name: 'factmodel'
    type: 'get'
    params: ['_id']
    method: (req, res) ->
        factCollection.findById req.params._id, (err, fact) ->
            if err?
                console.log 'Error finding fact by id'
                console.log err
                res.send 500, {}
                return

            tasks = [mergeFactWithType fact]
            if fact.proofs?
                for proof in fact.proofs
                    tasks.push getDependencies proof

            async.parallel tasks, (err) ->
                if err?
                    console.log 'Error merging with dependencies or factType'
                    console.log  err
                    res.send 500, {}
                    return

                res.send 200, fact

exports.methods.push
    name: 'factmodel'
    type: 'get'
    params: []
    method: (req, res) ->
        if not req.query.course?
            res.send 400, {}
            return

        factCollection.find {course: req.query.course}, (err, facts) ->
            if err?
                console.log 'Error finding facts for course'
                console.log err
                res.send 500, {}
                return

            tasks = []
            for fact in facts
                tasks.push mergeFactWithType fact
                if fact.proofs?
                    for proof in fact.proofs
                        tasks.push getDependencies proof

            async.parallel tasks, (err) ->
                if err?
                    console.log 'Error merging with dependencies or factType'
                    console.log  err
                    res.send 500, {}
                    return

                res.send 200, facts

exports.methods.push
    name: 'factmodel' 
    type: 'put'
    params: ['_id']
    method: (req, res) ->
        createFact req.body.factmodel, (err, fact, type) ->
            if err?
                res.send err, {}
                return

            # push that to the database
            factCollection.updateById req.params._id, fact, {}, (err, n) ->
                if err?
                    console.log 'Error updating fact'
                    console.log err
                    res.send 500, {}
                    return

                if n != 1
                    console.log 'Tried to update nonexistance fact'
                    res.send 400, {}
                    return

                res.send 200,
                    _id: req.params._id
                    color: type.color
                    canHaveProof: type.canHaveProof

exports.methods.push
    name: 'factmodel' 
    type: 'post'
    params: []
    method: (req, res) ->
        createFact req.body.factmodel, (err, fact, type) ->
            if err?
                res.send err, {}
                return

            # push that to the database
            factCollection.insert fact, {}, (err, result) ->
                if err?
                    console.log 'Error inserting fact'
                    console.log err
                    res.send 500, {}
                    return
                
                res.send 200,
                    _id: result[0]._id
                    color: type.color
                    canHaveProof: type.canHaveProof

exports.methods.push
    name: 'factmodel'
    type: 'delete'
    params: ['_id']
    method: (req, res) ->
        factCollection.removeById req.params._id, {}, (err, n) ->
            if err?
                console.log 'Error deleting fact'
                console.log err
                res.send 500, {}
                return

            res.send 200, {}