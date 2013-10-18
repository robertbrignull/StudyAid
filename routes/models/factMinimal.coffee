db = (require '../rest-mongo').db
ObjectID = (require 'mongoskin').ObjectID
factCollection = db.collection('factmodels')

mergeFactWithType = (require './factType').mergeFactWithType

exports.methods = []

exports.methods.push
    name: 'factminimalmodel'
    type: 'get'
    params: []
    method: (req, res) ->
    	factCollection.find({course: ObjectID(req.query.course)}, {_id: 1, name: 1, type: 1, course: 1}).toArray (err, facts) ->
    		if err?
    			console.log 'Error getting minimal facts'
    			console.log err
    			res.send 500, {}
    			return

    		(mergeFactWithType facts) (err, facts) ->
    			if err?
    				console.log 'Error merging with factType'
    				console.log err
    				res.send 500, {}
    				return

    			res.send 200, facts