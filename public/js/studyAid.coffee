StudyAid.App.root                               'studyAid#root'

class StudyAid.App.StudyAidController extends Batman.Controller
    routingKey: 'studyAid'

    root: (args) =>
        @render false

        @set 'courseList', new Batman.Set(
            new StudyAid.App.CourseModel
                _id: 1
                name: 'Complex Analysis'
            new StudyAid.App.CourseModel
                _id: 2
                name: 'Linear Algebra'
        )

        view = @render
            source: 'pages/root'
            cache: false

StudyAid.App.run()