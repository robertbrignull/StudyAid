filesystem = require 'fs'
path = require 'path'

config = (require __dirname + '/../config/config.json').database.mongo

mongo = require 'mongoskin'
db = mongo.db('mongodb://' + config.server + ':' + config.port + '/' + config.database, {safe: true})
exports.db = db

# Gather rest functions from files in the models directory
# and expose them here so the server can access them
exports.methods = []

filesystem.readdirSync(__dirname + '/models').forEach (file) ->
    if path.extname(file) == '.coffee'
        collection = require './models/' + path.basename(file, '.coffee')
        for method in collection.methods
            exports.methods.push method

# There is no enforced schema but here's how it should look
#
# Course = {
# 	_id: ObjId
# 	name: String            # how the user identifies the course
# }

# Fact = {
# 	_id: ObjId
# 	name: String            # how the user identifies the fact
# 	type: ObjId             # a pointer to a FactType
# 	course: ObjId           # a pointer to a Course
# 	statement: String       # the statement of the fact, in LaTeX
# 	proofs: [Proof]         # an inline array of Proofs
# 	rendered: String        # a hash of the last statement rendered
# }

# Proof = {
# 	_id: ObjId
# 	name: String            # optional name, may be blank
# 	text: String            # the body of the proof, in LaTeX
# 	dependencies: [ObjId]   # an array of pointers to Facts
# 	rendered: String        # a hash of the last text rendered
# }

# FactType = {
# 	_id: ObjId
# 	name: String            # the name of the fact type
# 	color: String           # a color in hex notation
# 	canHaveProof: Boolean   # whenther or not to offer proof buttons
# }