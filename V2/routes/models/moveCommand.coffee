db = (require '../rest-mongo').db
ObjectID = (require 'mongoskin').ObjectID
factCollection = db.collection('factmodels')

exports.methods = []

exports.methods.push
    name: 'movecommandmodel'
    type: 'post'
    params: []
    method: (req, res) ->
        if not req.body.movecommandmodel.fact? or
            not req.body.movecommandmodel.index?
                res.send 400, {}
                return

        index = parseInt req.body.movecommandmodel.index

        factCollection.update {index: {$gte: index}}, {$inc: {index: 1}}, {multi: true}, (err) ->
            if err?
                console.log 'Error incrementing indexes for move'
                console.log err
                res.send 500, {}
                return

            factCollection.updateById req.body.movecommandmodel.fact, {$set: {index: index}}, (err) ->
                if err?
                    console.log 'Error moving fact'
                    console.log err
                    res.send 500, {}
                    return

                res.send 200, {}