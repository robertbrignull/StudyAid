db = (require '../rest-mongo').db
factTypeCollection = db.collection('facttypemodels')

exports.methods = []

merge = (facts, types, done) ->
	for fact in facts
		type = types[fact.type]

		if not type?
			done 'Type not recognized'
			return

		fact.type = type.name
		fact.color = type.color
		fact.canHaveProof = type.canHaveProof

	done undefined, facts

exports.mergeFactWithType = (facts, done) ->
	# Just get all fact types, there aren't many of them
	factTypeCollection.find().toArray (err, typeArray) ->
		if err?
			done err
			return

		# convert into a map for easier access
		types = {}
		for type in typeArray
			types[type._id] = type

		if toString.call(facts) == '[object Array]'
			merge facts, types, done
		else
			merge [facts], types, (err, facts) ->
				done err, facts[0]