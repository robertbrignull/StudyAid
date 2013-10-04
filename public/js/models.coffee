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

class StudyAid.App.FactMinimalModel extends StudyAid.BaseModel
    @storageKey: 'factminimalmodel'

    @encode '_id', 'name'