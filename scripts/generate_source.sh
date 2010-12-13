#!/bin/sh

header="$1"
source="$2"
xml="$3"

if test "x$xml" = "x" ; then
    echo "Usage:"
    echo "    $0 <header> <source> <xml>"
    exit 1
fi

qdbusxml2cpp  -i $header -p :$source $xml
