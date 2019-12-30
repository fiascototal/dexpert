#!/bin/bash

if [ $# -eq 0 ]; then
    echo "[-] usage: ./compil.sh file1.java file2.java ..."
    exit 1
fi

javac $* || exit 1
dx --dex --output=test.dex *.class || exit 2
