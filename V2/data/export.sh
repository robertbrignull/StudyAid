#!/bin/bash

DB=StudyAid
COLLECTIONS=("coursemodels" "factmodels" "facttypemodels")

DIR=`dirname $(readlink -f $0)`

rm $DIR/*.json

for c in "${COLLECTIONS[@]}"
do
    mongoexport --db $DB --collection $c --out $DIR/$c.json
done