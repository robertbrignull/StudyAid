console.log '> loading modules'

http = require 'http'
express = require 'express'
namespace = require('express-namespace')
filesystem = require 'fs'
path = require 'path'

config = require __dirname + '/config/config.json'

#########################
# EXPRESS CONFIGURATION #
#########################

console.log '> configuring'

console.log '  - using basepath ' + config.basepath

app = express()
server = http.createServer app

app.configure ->
    app.set 'views', __dirname + '/views'
    app.set 'view engine', 'jade'
    app.use express.bodyParser()
    app.use express.logger('dev')
    app.use express.errorHandler
        dumpExceptions: true,
        showStack: true

app.use config.basepath, express.static(__dirname + '/public')

##########
# ROUTES #
##########

console.log '> routes'

jadeParams =
    'basepath': config.basepath

app.namespace jadeParams.basepath, ->
    # expose the rest interface
    console.log '  - REST'

    # we only have one controller
    console.log '  - controller'
    app.get '/', (req, res) ->
        res.render 'studyAid', jadeParams

    # however it may have many views
    console.log '  - pages'
    filesystem.readdirSync(__dirname + '/views/pages').forEach (page) ->
        if path.extname(page) == '.jade'
            do (page) ->
                console.log '    - pages/' + path.basename(page, '.jade')
                app.get 'views/pages/' + path.basename(page, '.jade') + '.html', (req, res) ->
                    res.render  'pages/' + path.basename(page, '.jade'), jadeParams

################
# START SERVER #
################

app.use app.router
server.listen config.port
console.log '> Server started on port ' + server.address().port