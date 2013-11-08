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
                    @set 'factList', @get('factList').sortedBy('index')

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

        course.save (err, course) =>
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

        fact.save (err, fact) =>
            if err?
                console.log 'Error saving fact'
                console.log err
                return

            if isNewFact
                Batman.redirect '/course/' + fact.get('course') + '/fact/' + fact.get('_id')

            else
                updateSrc = (obj, name) ->
                    $('#' + name).attr 'src', Batman.config.pathPrefix + '/image/latex/' + obj.get('_id') + '.png'

                updateSrc fact, 'factImg'

                fact.get('proofs').forEach (proof) ->
                    updateSrc proof, 'proof' + proof.get('_id') + 'Img'

    deleteFact: (fact) =>
        fact.destroy (err) =>
            if err?
                console.log 'Error removing fact'
                console.log err
                return

            Batman.redirect '/course/' + fact.get('course')

    moveFact: (fact, dir) =>
        if @get('inMoveMode')
            @set 'inMoveMode', false

            if @get('factToMove')? and (dir == 'above' or dir == 'below')
                index = parseInt fact.get('index')
                if dir == 'below'
                    index += 1

                moveCommand = new StudyAid.App.MoveCommandModel
                    fact: @get('factToMove._id')
                    index: index

                moveCommand.save (err) =>
                    @get('factList').forEach (f) =>
                        i = parseInt(f.get('index'))
                        if i >= index
                            f.set 'index', i + 1
                    @set 'factToMove.index', index
                    @set 'factToMove', undefined

                    @set 'factList', @get('factList').sortedBy('index')

        else
            @set 'factToMove', fact
            @set 'inMoveMode', true

    resetProofResponse: (proof) =>
        if proof.isStudyAidModel
            @set 'proofResponse', proof.clone()
        else
            @set 'proofResponse', new StudyAid.App.ProofModel
                name: ''
                text: ''
                dependencies: new Batman.Set

    createProof: (proof, fact) =>
        proof.set '_id', (new Date).getTime()
        fact.get('proofs').add proof
        @saveFact fact

    deleteProof: (proof, fact) =>
        fact.get('proofs').remove proof
        @saveFact fact



    resetDependencyResponse: =>
        @set 'dependencyResponse', new StudyAid.App.FactMinimalModel
        @set 'dependencyList', new Batman.Set

    loadDependencies: =>
        if @loadDependencyTimeout?
            clearTimeout @loadDependencyTimeout

        @loadDependencyTimeout = setTimeout =>
            @set 'dependencyList', new Batman.Set

            if @get('dependencyResponse.name') != ''
                StudyAid.App.FactMinimalModel.load {course: @get('currentCourse._id'), namePartial: @get('dependencyResponse.name')}, (err, facts) =>
                    if err?
                        console.log 'Error loading possible facts for dependency'
                        console.log err
                        return

                    Batman.Set.apply @get('dependencyList'), facts

                    # let the DOM update before trying to set the dropdown list value
                    if facts.length > 0
                        setTimeout =>
                            @set 'dependencyResponse._id', facts[0].get('_id')
                        , 0
        , 300

    createDependency: (dep, proof, fact) =>
        dependency = @get('dependencyList').find((d) -> d.get('_id') == dep.get('_id'))
        
        isSameFact = fact.get('_id') == dependency.get('_id')
        isAlreadyDependency = proof.get('dependencies').find((d) -> d.get('_id') == dependency.get('_id'))?
        
        if dependency? and not isSameFact and not isAlreadyDependency
            proof.get('dependencies').add dependency
            @saveFact fact

    deleteDependency: (dependency, proof, fact) =>
        proof.get('dependencies').remove dependency
        @saveFact fact

StudyAid.App.run()