filesystem = require 'fs'
path = require 'path'
async = require 'async'
crypto = require 'crypto'
spawn = require('child_process').spawn

config = require __dirname + '/../config/config.json'
renderPath = __dirname + '/..' + config.renderPath

db = (require './rest-mongo').db
ObjectID = (require 'mongoskin').ObjectID
factCollection = db.collection('factmodels')

# Returns a boolean of whether the given id
# currently has an image rendered
imageExists = (id) ->
    filesystem.existsSync renderPath + '/' + id + '.png'

# Takes an object and some text and provides a function
# that renders the text and stores it at the id of the object,
# also stores on the object the hash of the latest render.
renderImage = (obj, text) -> (callback) ->
    if not text?
        text = ''

    shasum = crypto.createHash 'sha1'
    shasum.update text
    hash = shasum.digest 'hex'

    if hash == obj.rendered and imageExists obj._id
        callback()
        return

    imageRoot = renderPath + '/' + obj._id

    text =
        '\\documentclass[a4paper]{article}' +
        '\\usepackage{geometry}' +
        '\\usepackage[active,tightpage]{preview}' +
        '\\begin{document}' +
        '\\begin{preview}' +
        text +
        '\\end{preview}' +
        '\\end{document}'

    filesystem.writeFile imageRoot + '.latex', text, (err) ->
        if err?
            callback err
            return

        # render the latex to a huge pdf
        latex = spawn 'pdflatex', ['-halt-on-error', '-output-directory', renderPath, imageRoot + '.latex']

        latex.stderr.on 'data', (data) ->
            console.log 'latex stderr: ' + data

        latex.on 'close', (code) ->
            if code != 0
                callback 'latex exited with code ' + code
                return

            pdftoppm = spawn 'pdftoppm', ['-png', '-singlefile', '-r', '200', imageRoot + '.pdf', imageRoot]

            pdftoppm.stderr.on 'data', (data) ->
                console.log 'pdftoppm stderr: ' + data

            pdftoppm.on 'close', (code) ->
                if code != 0
                    callback 'pdftoppm exited with code ' + code
                    return

                filesystem.unlinkSync imageRoot + '.latex'
                filesystem.unlinkSync imageRoot + '.pdf'
                filesystem.unlinkSync imageRoot + '.aux'
                filesystem.unlinkSync imageRoot + '.log'

                obj.rendered = hash

                callback()

# Returns a function that deletes the currently
# rendered image for the given id
removeImage = (id) -> (callback) ->
    filesystem.unlink renderPath + '/' + id + '.png', (err) ->
    callback()

# Renders a fact and all of its proofs
exports.render = (fact) -> (done) ->
    tasks = []

    tasks.push(renderImage fact, fact.statement)

    if fact.proofs?
        for proof in fact.proofs
            tasks.push(renderImage proof, proof.text)

    async.parallel tasks, (err) ->
        factCollection.updateById fact._id, {$set: {rendered: fact.rendered}}, (err) ->
            done err

# Removes the images for a fact and all of its proofs
exports.remove = (fact) -> (done) ->
    tasks = []

    tasks.push removeImage fact._id

    if fact.proofs?
        for proof in fact.proofs
            tasks.push removeImage proof._id

    async.parallel tasks, (err) ->
        done err
