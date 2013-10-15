filesystem = require 'fs'
path = require 'path'

config = (require __dirname + '/../config/config.json').database.mongo

mongo = require 'mongoskin'
db = mongo.db(config.server + ':' + config.port + '/' + config.database, {safe: true})
exports.db = db

# Gather rest functions from files in the models directory
# and expose them here so the server can access them
exports.methods = []

filesystem.readdirSync(__dirname + '/models').forEach (file) ->
    if path.extname(file) == '.coffee'
        collection = require './models/' + path.basename(file, '.coffee')
        for method in collection.methods
            exports.methods.push method