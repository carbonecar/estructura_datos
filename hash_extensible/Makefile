# CONFIGURACION
################

# Nombre del ejecutable.
target = hash

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

# Archivos con el código fuente que componen el ejecutable.

#Utilidades generales

fuentes = src/utiles/utiles.cpp
fuentes +=src/utiles/excepciones.cpp

#almacenamiento
fuentes += src/almacenamiento/LennyAlmacenamiento.cpp
fuentes += src/almacenamiento/LennyArchivo.cpp

#hash

fuentes += src/indice/hash/debug.cpp
fuentes += src/indice/hash/funcionhash.cpp
fuentes += src/indice/hash/textindex.cpp
fuentes += src/indice/hash/cubo.cpp
fuentes += src/indice/hash/directorio.cpp
fuentes += src/indice/indice.cpp
fuentes += src/indice/indiceHash.cpp

#Cargador
fuentes += src/main.cpp

# CONFIGURACION "AVANZADA"
###########################

# Opciones para el compilador C/C++ en modo ansi.
#CFLAGS = -Wall -ansi -pedantic-errors
CFLAGS = -Wall -ansi -pedantic-errors

# Para valgrind o debug
CFLAGS += -ggdb -DDEBUG

# Opciones para el compilador C++.
#CXXFLAGS = $(CFLAGS) -fno-inline
CXXFLAGS = $(CFLAGS) 

# Opciones del enlazador.
#LDFLAGS


# VARIABLES CALCULADAS A PARTIR DE LA CONFIGURACION
####################################################

# Uso enlazador de c++ si es código no C.
ifeq ($(extension), c)
enlazador = $(CC)
else
enlazador = $(CXX)
endif

# Si no especifica archivos, tomo todos.
fuentes ?= $(wildcard *.$(extension))


# REGLAS
#########

.PHONY: all clean

all: $(target)

o_files = $(patsubst %.$(extension),%.o,$(fuentes))

$(target): $(o_files)
	$(enlazador) $(LDFLAGS) $(o_files) $(LOADLIBES) $(LDLIBS) -o $(target)

clean:
	@$(RM) -fv $(o_files) $(target)
