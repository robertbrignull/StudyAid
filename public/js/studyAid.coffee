StudyAid.App.root                               'studyAid#root'
StudyAid.App.route 'course',                    'studyAid#course'

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

    course: (args) =>
        @render false

        @set 'currentCourse', new StudyAid.App.CourseModel
            _id: 1
            name: 'Complex Analysis'

        @set 'factList', new Batman.Set(
            new StudyAid.App.FactMinimalModel
                _id: 1
                name: 'Distance between points'
            new StudyAid.App.FactMinimalModel
                _id: 2
                name: 'Triangle inequality'
        )

        view = @render
            source: 'pages/course'
            cache: false

StudyAid.App.run()