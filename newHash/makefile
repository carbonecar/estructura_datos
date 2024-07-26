# CONFIGURACION
################

# Nombre del ejecutable.
target = ExtensibleHash

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

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
fuentes  = $(wildcard ./src/Hash/*.cpp) \
	$(wildcard ./src/Persistence/exceptions/*.cpp) \
	$(wildcard ./src/Persistence/*.cpp) \
	$(wildcard ./src/utils/*.cpp) \
	$(wildcard ./src/main/*.cpp) \
	$(wildcard ./src/*.cpp)

# REGLAS
#########

.PHONY: all clean

all: $(target)

o_files = $(patsubst %.$(extension),%.o,$(fuentes))

$(target): $(o_files)
	$(enlazador) $(LDFLAGS) $(o_files) $(LOADLIBES) $(LDLIBS) -o $(target)

clean:
	$(RM) -rf $(o_files)
