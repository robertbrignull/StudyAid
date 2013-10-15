StudyAid.App.root                                   'studyAid#root'
StudyAid.App.route 'course/:courseId',              'studyAid#course'
StudyAid.App.route 'course/:courseId/fact/:factId', 'studyAid#fact'

class StudyAid.App.StudyAidController extends Batman.Controller
    routingKey: 'studyAid'

    root: (args) =>
        @render false

        @set 'currentCourse', undefined
        @set 'currentFact', undefined

        @set 'courseList', new Batman.Set

        StudyAid.App.CourseModel.load (err, courses) =>
            if err?
                console.log 'Error getting courses'
                console.log err
            else
                Batman.Set.apply @get('courseList'), courses

            view = @render
                source: 'pages/root'
                cache: false
            view.on 'ready', =>

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

    fact: (args) =>
        @render false

        @set 'currentCourse', new StudyAid.App.CourseModel
            _id: 1
            name: 'Complex Analysis'

        @set 'currentFact', new StudyAid.App.FactModel
            _id: 1
            name: 'Triangle inequality'
            type: 'Proposition'
            color: 'FF0000'
            canHaveProof: true
            course: 1
            statement: 'Suppose that \\(f\\) is holomorphic on and inside a simple closed curve \\(\\gamma\\) except at isolated singularities \\(a_1,...a_m\\) inside \\(\\gamma\\). Then\n\\[\\int_\\gamma f(z)dz = 2\\pi i\\sum_{k=1}^mres(f;a_k)\\]'
            proofs: new Batman.Set(
                new StudyAid.App.ProofModel
                    _id: 1
                    name: ''
                    text: 'Suppose that \\(f\\) is holomorphic on and inside a simple closed curve \\(\\gamma\\) except at isolated singularities \\(a_1,...a_m\\) inside \\(\\gamma\\). Then\n\\[\\int_\\gamma f(z)dz = 2\\pi i\\sum_{k=1}^mres(f;a_k)\\]'
                    dependencies: new Batman.Set(
                        new StudyAid.App.FactMinimalModel
                            _id: 1
                            name: 'Distance between points'
                    )
            )

        view = @render
            source: 'pages/fact'
            cache: false



    resetCourseResponse: =>
        @set 'courseResponse', new StudyAid.App.CourseModel
            name: ''

    saveCourse: =>
        @get('courseResponse').save (err) =>
            if err?
                console.log 'Error saving course'
                console.log err
                return

            if @get('courseList')?
                @get('courseList').add @get('courseResponse')

StudyAid.App.run()