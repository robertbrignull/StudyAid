StudyAid.App.root                               'studyAid#root'

class StudyAid.App.StudyAidController extends Batman.Controller
    routingKey: 'studyAid'

    root: (args) ->
        @render false

StudyAid.App.run()