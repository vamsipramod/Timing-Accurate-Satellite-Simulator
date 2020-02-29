#!/bin/bash
# My first script

if [ "$1" != "" ]; then
    ./src/decompressor decompress compressedLog > $1
else
    ./src/decompressor decompress compressedLog > mylogfile.log
fi

# ./src/decompressor decompress 