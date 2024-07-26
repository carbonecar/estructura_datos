# CONFIGURACION
################

# Nombre del ejecutable.
target_hash = ppmc-h

target_BTree = ppmc-b

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
fuentesIndexHash  = src/Persistence/Archivo.cpp \
		src/Persistence/FreeSpaceManager.cpp \
		src/Persistence/Block.cpp \
		src/Persistence/PersistorBase.cpp \
		$(wildcard ./src/Hash/*.cpp) \
		$(wildcard ./src/aritmetic/*.cpp) \
		$(wildcard ./src/compresor/*.cpp) \
		src/ppmcindex/Index.cpp \
		src/ppmcindex/IndexHash.cpp \
		$(wildcard ./src/logger/exceptions/*.cpp) \
		$(wildcard ./src/logger/*.cpp) \
		$(wildcard ./src/utils/*.cpp) \
		$(wildcard ./src/main/hash/*.cpp) \
		$(wildcard ./src/main/*.cpp) \
		main/main_hash.cpp

fuentesIndexBTree  = $(wildcard ./src/BPlusTree/*.cpp) \
		$(wildcard ./src/exceptions/*.cpp) \
		$(wildcard ./src/Persistence/*.cpp) \
		$(wildcard ./src/aritmetic/*.cpp) \
		$(wildcard ./src/compresor/*.cpp) \
		src/ppmcindex/Index.cpp \
		src/ppmcindex/IndexBtree.cpp \
		$(wildcard ./src/logger/exceptions/*.cpp) \
		$(wildcard ./src/logger/*.cpp) \
		$(wildcard ./src/strategies/*.cpp) \
		$(wildcard ./src/utils/*.cpp) \
		$(wildcard ./src/main/btree/*.cpp) \
		$(wildcard ./src/main/*.cpp) \
		main/main_btree.cpp

# REGLAS
#########

.PHONY: all clean

hash :$(target_hash)
o_files_Hash = $(patsubst %.$(extension),%.o,$(fuentesIndexHash))
$(target_hash): $(o_files_Hash)
	$(enlazador) $(LDFLAGS) $(o_files_Hash) $(LOADLIBES) $(LDLIBS) -o $(target_hash)

btree :$(target_BTree)
o_files_BTree = $(patsubst %.$(extension),%.o,$(fuentesIndexBTree))
$(target_BTree): $(o_files_BTree)
	$(enlazador) $(LDFLAGS) $(o_files_BTree) $(LOADLIBES) $(LDLIBS) -o $(target_BTree)


all: $(hash) $(btree)

clean:
	$(RM) -rf $(o_files_Hash)
	$(RM) -rf $(o_files_BTree)
