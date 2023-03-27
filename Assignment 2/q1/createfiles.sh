#!/bin/bash

for i in {1..47}
do
    filename="sam${i}.txt"
    echo "This is file $i" > "$filename"
done
