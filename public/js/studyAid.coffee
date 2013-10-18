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

    course: (args) =>
        @render false

        @set 'factList', new Batman.Set

        StudyAid.App.CourseModel.find args.courseId, (err, course) =>
            if err?
                console.log 'Error getting course'
                console.log err

            @set 'currentCourse', course
            @set 'currentFact', undefined

            StudyAid.App.FactMinimalModel.load {course: args.courseId}, (err, facts) =>
                if err?
                    console.log 'Error getting facts'
                    console.log err
                else
                    Batman.Set.apply @get('factList'), facts

                view = @render
                    source: 'pages/course'
                    cache: false

    fact: (args) =>
        @render false

        StudyAid.App.CourseModel.find args.courseId, (err, course) =>
            if err?
                console.log 'Error getting course'
                console.log err

            @set 'currentCourse', course

            StudyAid.App.FactModel.find args.factId, (err, fact) =>
                if err?
                    console.log 'Error getting fact'
                    console.log err

                @set 'currentFact', fact

                view = @render
                    source: 'pages/fact'
                    cache: false



    resetCourseResponse: (course) =>
        if course.isStudyAidModel
            @set 'courseResponse', course.clone()
        else
            @set 'courseResponse', new StudyAid.App.CourseModel
                name: ''

    saveCourse: (course) =>
        isNewCourse = not course.get('_id')?

        course.save (err) =>
            if err?
                console.log 'Error saving course'
                console.log err
                return

            if isNewCourse
                Batman.redirect '/course/' + course.get('_id')

    deleteCourse: (course) =>
        course.destroy (err) =>
            if err?
                console.log 'Error removing course'
                console.log err
                return

            Batman.redirect '/'



    resetFactResponse: (fact) =>
        if fact.isStudyAidModel
            @set 'factResponse', fact.clone()
        else
            @set 'factResponse', new StudyAid.App.FactModel
                name: ''
                type: 'Theory'
                color: 'FF0000'
                canHaveProof: true
                course: @get('currentCourse._id')
                statement: ''
                proofs: new Batman.Set

    saveFact: (fact) =>
        isNewFact = not fact.get('_id')?

        fact.save (err) =>
            if err?
                console.log 'Error saving fact'
                console.log err
                return

            if isNewFact
                Batman.redirect '/course/' + fact.get('course') + '/fact/' + fact.get('_id')

    deleteFact: (fact) =>
        fact.destroy (err) =>
            if err?
                console.log 'Error removing fact'
                console.log err
                return

            Batman.redirect '/course/' + fact.get('course')

StudyAid.App.run()