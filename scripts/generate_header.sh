#!/bin/sh

header="$1"
source="$2"
xml="$3"

if test "x$xml" = "x"; then
    echo "Usage:"
    echo "    $0 <header> <source> <xml>"
    exit 1
fi

INCLUDE=""
test "x$header" != "x" && INCLUDE="-i header/$header"

#qdbusxml2cpp -i QtZeitgeist/BaseTypes $INCLUDE -p $source: $xml
qdbusxml2cpp -p $source: $xml
