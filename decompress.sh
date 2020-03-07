#!/bin/bash
# My first script

if [ "$1" != "" ]; then
    ./src/NanoLog/runtime/decompressor decompress compressedLog > $1
else
    ./src/NanoLog/runtime/decompressor decompress compressedLog > mylogfile.log
fi

# ./src/decompressor decompress 
