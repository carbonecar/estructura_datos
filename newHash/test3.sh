#!/bin/bash
rm ./test/test3.*
./ExtensibleHash ./test/test3 -I < ./test/test3-1-insert.txt
./ExtensibleHash ./test/test3 -b < ./test/test3-2-search.txt
./ExtensibleHash ./test/test3 -s >test3-salida.txt
