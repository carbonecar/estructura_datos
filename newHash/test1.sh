#!/bin/bash
rm ./test/test1.*
./ExtensibleHash ./test/test1 -I < ./test/test1-insert.txt
./ExtensibleHash ./test/test1 -s > test1-salida.txt
echo "Los resultados se guardaron en el archivo test1-salida.txt"
