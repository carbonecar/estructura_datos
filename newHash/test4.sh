#!/bin/bash
rm ./test/test4.*
./ExtensibleHash ./test/test4 -I < ./test/test4-1-insert.txt
./ExtensibleHash ./test/test4 -q < ./test/test4-2-delete.txt
./ExtensibleHash ./test/test4 -b < ./test/test4-3-search.txt
./ExtensibleHash ./test/test4 -s > test4-salida.txt
