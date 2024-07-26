#!/bin/sh

## Veo cuantos parametros hay. Si no tiene exactamente 2, muestro la ayuda
if [ "$#" != "3" ]; then
    echo "Leer la documentacion adjunta para obtener los parametros validos"
    exit
fi

## RUTAS
HASH="../ppmc-h"
BTREE="../ppmc-b"
CMD=""
STORE=""

## ORDEN
ORDEN=$2

## PRUEBAS
PRUEBA=$1


case "$3" in
    hash|HASH|Hash)
	CMD=$HASH
	STORE="Hash"
	;;
	
    BTREE|Btree|btree)
	CMD=$BTREE
	STORE="B#-Tree"
	;;
	
    *)
	echo "No conozco al almacenaimento $3"
	exit
    ;;
esac

case $PRUEBA in
    1)
	echo "Ejecutando la prueba 1: Comprimir y descomprimir el archivo arithmetic.txt (Archivo de texto)"
	echo "Los contextos seran almacenados en $STORE"
	echo ""
	echo "* Comprimiendo..."
	rm trash* >/dev/null
	eval "cat ./arithmetic.txt|$CMD -c $ORDEN -f trash.pmw > ./salida-compresion-test1.LSD"

	echo "* Descomprimiendo..."
	rm trash* >/dev/null
	eval "cat ./salida-compresion-test1.LSD|$CMD -d $ORDEN -f trash.pmw > ./salida-test1.txt"
	
	echo "* Resultados (Tamaños en bytes): "
	echo -n "Archivo original:"
	du -h -b arithmetic.txt
	
	echo -n "Archivo comprimido:"
	du -h -b salida-compresion-test1.LSD
	
	echo -n "Archivo descomprimido:"
	du -h -b salida-test1.txt
	
	echo "Salida del comando diff"
	DIFF=`diff arithmetic.txt salida-test1.txt`
	if [ "$DIFF" = "" ]; then
	    echo "Son iguales"
	else
	    echo $DIFF
	fi
    ;;
    
    2)
	echo "Ejecutando la prueba 2: Comprimir y descomprimir el archivo bsod.png (Archivo binario)"
	echo "Los contextos seran almacenados en $STORE"
	echo ""
	echo "* Comprimiendo..."
	rm trash* >/dev/null
	eval "cat ./bsod.png|$CMD -c $ORDEN -f trash.pmw > ./salida-compresion-test2.LSD"

	echo "* Descomprimiendo..."
	rm trash* >/dev/null
	eval "cat ./salida-compresion-test2.LSD|$CMD -d $ORDEN -f trash.pmw > ./salida-test2.png"
	
	echo "* Resultados (Tamaños en bytes): "
	echo -n "Archivo original:"
	du -h -b bsod.png
	
	echo -n "Archivo comprimido:"
	du -h -b salida-compresion-test2.LSD
	
	echo -n "Archivo descomprimido:"
	du -h -b salida-test2.png
	
	echo "Salida del comando diff"
	DIFF=`diff bsod.png salida-test2.png`
	if [ "$DIFF" = "" ]; then
	    echo "Son iguales"
	else
	    echo $DIFF
	fi
    ;;
    
    3)
	echo "Ejecutando la prueba 3: Comprimir y descomprimir el archivo bsod.ansi (Representacion string de una imagen)"
	echo "Los contextos seran almacenados en $STORE"
	echo ""
	echo "* Comprimiendo..."
	rm trash* >/dev/null
	eval "cat ./bsod.ansi|$CMD -c $ORDEN -f trash.pmw > ./salida-compresion-test3.LSD"

	echo "* Descomprimiendo..."
	rm trash* >/dev/null
	eval "cat ./salida-compresion-test3.LSD|$CMD -d $ORDEN -f trash.pmw > ./salida-test3.ansi"
	
	echo "* Resultados (Tamaños en bytes): "
	echo -n "Archivo original:"
	du -h -b bsod.ansi
	
	echo -n "Archivo comprimido:"
	du -h -b salida-compresion-test3.LSD
	
	echo -n "Archivo descomprimido:"
	du -h -b salida-test3.ansi
	
	echo "Salida del comando diff"
	DIFF=`diff bsod.ansi salida-test3.ansi`
	if [ "$DIFF" = "" ]; then
	    echo "Son iguales"
	else
	    echo $DIFF
	fi
    ;;
    
    4)
    	echo "Ejecutando la prueba 4: Comprimir y descomprimir el archivo bsod.xbm (Representacion string de una imagen, en formato array)"
	echo "Los contextos seran almacenados en $STORE"
	echo ""
	echo "* Comprimiendo..."
	rm trash* >/dev/null
	eval "cat ./bsod.xbm|$CMD -c $ORDEN -f trash.pmw > ./salida-compresion-test4.LSD"

	echo "* Descomprimiendo..."
	rm trash* >/dev/null
	eval "cat ./salida-compresion-test4.LSD|$CMD -d $ORDEN -f trash.pmw > ./salida-test4.xbm"
	
	echo "* Resultados (Tamaños en bytes): "
	echo -n "Archivo original:"
	du -h -b bsod.xbm
	
	echo -n "Archivo comprimido:"
	du -h -b salida-compresion-test4.LSD
	
	echo -n "Archivo descomprimido:"
	du -h -b salida-test4.xbm
	
	echo "Salida del comando diff"
	DIFF=`diff bsod.xbm salida-test2.xbm`
	if [ "$DIFF" = "" ]; then
	    echo "Son iguales"
	else
	    echo $DIFF
	fi

    ;;
    
    *)
	echo "Eh?"
    ;;
    
esac 
echo ""
echo ""