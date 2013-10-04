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