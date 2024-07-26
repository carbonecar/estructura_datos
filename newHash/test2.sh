#!/bin/bash
echo "Prueba del hash extensible, coincidente con mensaje #2958 del grupo yahoo (Bloques de 256K)"
rm ./test/test2.*
./ExtensibleHash ./test/test2 -I < ./test/test2-1-insert.txt
./ExtensibleHash ./test/test2 -s > test2-salida.txt

./ExtensibleHash ./test/test2 -q < ./test/test2-2-delete.txt
./ExtensibleHash ./test/test2 -s >> test2-salida.txt

./ExtensibleHash ./test/test2 -I < ./test/test2-3-insert.txt
./ExtensibleHash ./test/test2 -s >> test2-salida.txt

./ExtensibleHash ./test/test2 -q < ./test/test2-4-delete.txt
./ExtensibleHash ./test/test2 -s >> test2-salida.txt

./ExtensibleHash ./test/test2 -I < ./test/test2-5-insert.txt
./ExtensibleHash ./test/test2 -s >> test2-salida.txt



