# CONFIGURACION
################

# Nombre del ejecutable.
target = BPlusTree

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

# Archivos con el código fuente que componen el ejecutable.

# Archivos a compilar
# Carpeta /BPlusTree:
fuentes += src/BPlusTree/BNode.cpp \
	src/BPlusTree/BPlusTree.cpp \
	src/BPlusTree/Element.cpp \
	src/BPlusTree/EqualElementComparator.cpp \
	src/BPlusTree/KeyElement.cpp \
	src/BPlusTree/LeafNode.cpp \
	src/BPlusTree/MainTree.cpp \
	src/BPlusTree/Node.cpp \
	src/BPlusTree/NodeFactory.cpp

# Carpeta /exceptions:
fuentes += src/exceptions/BufferOverflowException.cpp \
	src/exceptions/ElementAlreadyExists.cpp \
	src/exceptions/ElementNotFoundException.cpp \
	src/exceptions/KeyNotFoundException.cpp \
	src/exceptions/OperationNotFoundException.cpp \
	src/exceptions/OverflowException.cpp \
	src/exceptions/ProgramException.cpp

# Carpeta /Persistence:
fuentes += src/Persistence/Archivo.cpp \
	src/Persistence/Block.cpp \
	src/Persistence/FreeSpaceManager.cpp \
	src/Persistence/PersistorBase.cpp \
	src/Persistence/PersistorBTree.cpp \
	src/Persistence/Persistor.cpp

# Carpeta /Persistence/exceptions:
fuentes += src/Persistence/exceptions/excepciones.cpp \
	src/Persistence/exceptions/FailFileWriteException.cpp \
	src/Persistence/exceptions/FileNotFoundexception.cpp \
	src/Persistence/exceptions/NotFindFreeNodeException.cpp \
	src/Persistence/exceptions/PersistorInitializedException.cpp \
	src/Persistence/exceptions/PersistorNotInitializedException.cpp \
	src/Persistence/exceptions/WrongBlockSize.cpp


# Carpeta /strategies:
fuentes += src/strategies/BalanceStrategy.cpp \
	src/strategies/BalanceStrategyFactory.cpp \
	src/strategies/ComposedBalanceStrategy.cpp \
	src/strategies/DeleteBalanceStrategy.cpp \
	src/strategies/InsertBalanceStrategy.cpp \
	src/strategies/ModifyBalanceStrategy.cpp \
	src/strategies/OverflowStrategy.cpp \
	src/strategies/UnderflorRootStrategy.cpp \
	src/strategies/UnderflowStrategy.cpp


#Carpeta /utils:
fuentes += src/utils/ConfigurationMananger.cpp \
	   src/utils/ConfigFile.cpp \
	   src/utils/const.h \
	   src/utils/types.h \
	   src/utils/utiles.cpp 

#Directorio /tests:
fuentes += src/test/BPlusTreeTest.cpp \
	   src/test/TestCompare.cpp \
	   src/test/TestConfigurationManager.cpp \
	   src/test/TestFreeSpaceManager.cpp \
	   src/test/TestPersistor.cpp \
	   src/test/TestSerialization.cpp

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

# REGLAS
#########

.PHONY: all clean

all: $(target)

o_files = $(patsubst %.$(extension),%.o,$(fuentes))

$(target): $(o_files)
	$(enlazador) $(LDFLAGS) $(o_files) $(LOADLIBES) $(LDLIBS) -o $(target)

clean:
	$(RM) -rfv $(o_files)

