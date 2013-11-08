#!/bin/bash

DB=StudyAid
COLLECTIONS=("coursemodels" "factmodels" "facttypemodels")

DIR=`dirname $(readlink -f $0)`

mongo $DB --eval "db.dropDatabase()"

for c in "${COLLECTIONS[@]}"
do
    mongoimport --db $DB --collection $c --file $DIR/$c.json
done