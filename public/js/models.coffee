class StudyAid.BaseModel extends Batman.Model
    @primaryKey: '_id'
    @persist Batman.RestStorage
    @urlPrefix: Batman.config.pathPrefix + '/rest'
    urlPrefix: Batman.config.pathPrefix + '/rest'

    clone: () ->
        return (new @constructor).fromRawJSON(@toJSON())

    fromRawJSON: (json) ->
        @fromJSON json

class StudyAid.App.CourseModel extends StudyAid.BaseModel
    @storageKey: 'coursemodel'

    @encode '_id', 'name'

class StudyAid.App.FactModel extends StudyAid.BaseModel
    @storageKey: 'factmodel'

    @encode '_id', 'name', 'type', 'color', 'canHaveProof', 'course', 'statement', 'rendered'

    @encode 'proofs',
        encode: (oldProofs) ->
            newProofs = []
            oldProofs.forEach (proof) ->
                newProofs.push proof.toJSON()
            return JSON.stringify newProofs

        decode: (oldProofs) ->
            newProofs = new Batman.Set
            for proof in oldProofs
                newProofs.add (new StudyAid.App.ProofModel).fromJSON(proof)
            return newProofs

    fromRawJSON: (json) ->
        if json.proofs?
            json.proofs = JSON.parse json.proofs
        return @fromJSON json


class StudyAid.App.ProofModel extends StudyAid.BaseModel
    @storageKey: 'proofmodel'

    @encode '_id', 'name', 'text', 'rendered'

    @encode 'dependencies',
        encode: (oldDependencies) ->
            newDependencies = []
            oldDependencies.forEach (dependency) ->
                newDependencies.push dependency.toJSON()
            return JSON.stringify newDependencies

        decode: (oldDependencies) ->
            newDependencies = new Batman.Set
            for dependency in oldDependencies
                newDependencies.add (new StudyAid.App.FactMinimalModel).fromJSON(dependency)
            return newDependencies

    fromRawJSON: (json) ->
        if json.dependencies?
            json.dependencies = JSON.parse json.dependencies
        return @fromJSON json

class StudyAid.App.FactMinimalModel extends StudyAid.BaseModel
    @storageKey: 'factminimalmodel'

    @encode '_id', 'name'