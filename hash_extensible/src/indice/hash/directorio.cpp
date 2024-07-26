/*
 * directorio.cpp
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */

#include "directorio.h"
#include "../../utiles/utiles.h"
#include "debug.h"


Directorio::Directorio(string dirfile, string bktfile,unsigned int maxBucketKeys)
{
	this->_profundidad = 0;
	this->_maxClavesPorCubo = maxBucketKeys;
	this->_debug = NULL;


	//Manejo de archivos
	bool existen = Util::archivoExiste(dirfile);

	this->dirfile = new LennyArchivo(dirfile,sizeof(int));
	this->bktfile = new LennyArchivo(bktfile,maxBucketKeys);

	//Borro si quedó basura
	if ((this->dirfile->size() == 0) || (this->bktfile->size()==0))
	{
		this->dirfile->vaciar();
		this->bktfile->vaciar();
		existen = false;
	}

	if (existen)
	{
		//Creo un nuevo bucket y le asigno direccion 0
		this->_cuboActual = new Cubo (this, maxBucketKeys);
		this->_cuboActual->_direccion = -1;
		this->_cuboActual->_profundidad = 0;

		//Tengo que abrir el archivo
		this->cargar();

	} else {
		//Tengo que crear un indice nuevo

		this->_cubo.resize(1,0);

		//Creo un nuevo bucket y le asigno direccion 0
		this->_cuboActual = new Cubo (this, maxBucketKeys);
		this->_cuboActual->_direccion = 0;
		this->_cuboActual->_profundidad = this->_profundidad;

		//Grabo el nuevo bucket a disco y me guardo el numero de bloque en el vector
		this->_cubo[0] = this->guardarCubo(this->_cuboActual);
	}

}

Directorio::~Directorio()
{
	this->guardar();
}

/**
 * Guarda un cubo a disco
 * Recibe el cubo
 * Devuelve el numero de bloque
 */
unsigned int Directorio::guardarCubo (Cubo* bucket)
{
	//Serializo el bucket
	string data = bucket->serializar();
	int addr = bucket->_direccion;
	if (addr != -1)
	{
		//El bucket ya tiene direccion, lo guardo en el mismo lugar que estaba
		this->bktfile->escribir(data,addr);
	} else {
		//El bucket no tiene direccion, es nuevo, tengo que agregarlo y asignarle un numero
		//unsigned int registro = this->bktfile->agregar(data);

		int registro = this->buscarHueco();
		if (registro == -1)
		{
			registro = this->bktfile->agregar(data);
		} else {
			this->bktfile->escribir(data,registro);
		}

		bucket->_direccion = registro;
		addr = registro;
	}
	return addr;
}

/**
 * Busca un bloque de archivo donde guardar el bucket
 */
int Directorio::buscarHueco ()
{
	int result = -1;

	for (unsigned int k = 0; k < this->bktfile->elementos() ; k++)
	{
		string data = this->bktfile->leer(k);
		if (this->_cuboActual->asNew(data))
		{
			result = k;
			break;
		}
	}

	return result;
}

/**
 * Carga un bucket de disco a memoria
 * Recibe un bucket destino, y el numero de bloque a leer
 */
bool Directorio::cargarCubo (Cubo* bucket, unsigned int bucketAddr)
{
	//Si el bucket no está, entonces me voy de la funcion
	unsigned int elementos = bktfile->elementos();
	unsigned int elemento = bucketAddr;
	unsigned int elementoActual = (unsigned) this->_cuboActual->_direccion;

	//Si está cargado, no lo recargo
	if (elementoActual ==  bucketAddr) return true;

	//Si el bloque que pido no está en el archivo, salgo
	if (elemento >= elementos) return false;

	//Leo el bucket, lo deserializo y le asigno el numerito
	string data = this->bktfile->leer(bucketAddr);
	bucket->_direccion = bucketAddr;
	bucket->_debug = this->_debug;
	bucket->deserializar(data);
	return true;
}

/**
 * Inserta una clave y el numero de bloque al que pertenece
 * Recibe la clave y el numero de bloques
 * Devuelve true o false segun si se pudo realizar o no
 */
bool Directorio::insertar (int key, string data)
{
	//Busco la clave
	bool found = exists(key);

	//Si la clave no se encontró, entonces la inserto en el bucket actual
	if (found) return false;	//Existe, entonces no la inserto

	return this->_cuboActual->insertar(key, data);
}

bool Directorio::modificar (int key, string data)
{
	if (!exists(key)) return false;

	bool result = this->_cuboActual->modificar(key,data);
	if (!result)
	{
		this->_cuboActual->eliminar(key);
		return this->insertar(key, data);
	}
	return result;
}

/**
 * Elimina una clave del bloque al que pertenece
 * Recibe una clave
 * Devuelve si pudo eliminar o no.
 */
bool Directorio::eliminar (int key)
{
	//Busco la clave en el directorio
	int bucketAddr = this->encontrar(key);

	//Cargo el bucket que corresponde a la clave
	this->cargarCubo(this->_cuboActual,(unsigned) bucketAddr);

	//Devuelvo el resultado de eliminar la clave
	return this->_cuboActual->eliminar(key);
}

/**
 * Busca una clave y devuelve el bloque al que está asociado
 * Recibe la clave
 * devuelve el numero de bloque en el archivo de datos
 */
string Directorio::buscar (int key)
{
	//string dbg = "";
	//dbg = "Buscando clave "; dbg.append (key); this->writeDebug(dbg);

	//Busco la direccion y cargo el bucket
	int bucketAddr = this->encontrar(key);
	//dbg = "Direccion del bucket "; dbg.append (Util::toString(bucketAddr)); this->writeDebug(dbg);

	if (this->_cuboActual->_direccion != bucketAddr)
	{
		//dbg = "Cargo el bucket "; dbg.append (Util::toString(bucketAddr)); this->writeDebug(dbg);
		this->cargarCubo(this->_cuboActual, (unsigned) bucketAddr);
	}

	//Busco dentro del bucket
	if (this->_cuboActual->existe(key)) return this->_cuboActual->buscar(key);
	return "";
}

bool Directorio::exists(int key)
{
	int bucketAddr = this->encontrar(key);
	//dbg = "Direccion del bucket "; dbg.append (Util::toString(bucketAddr)); this->writeDebug(dbg);

	if (this->_cuboActual->_direccion != bucketAddr)
	{
		//dbg = "Cargo el bucket "; dbg.append (Util::toString(bucketAddr)); this->writeDebug(dbg);
		this->cargarCubo(this->_cuboActual, (unsigned) bucketAddr);
	}

	//Busco dentro del bucket
	return this->_cuboActual->existe(key);
}

/**
 * Dada una clave, busca el bucket en el que está alojada la informacion
 */
int Directorio::encontrar(int key)
{

	return this->_cubo[cFuncionHash::MakeAddress (key,this->_profundidad)];
}

int Directorio::duplicarTabla()
{
	//Copio la tabla actual
	vector<unsigned int> temporal (this->_cubo);

	//Ajusto el tamaño de la tabla actual
	this->_cubo.clear();
	this->_cubo.resize(temporal.size() * 2,0);

	//Copio los elementos de una tabla a la otra
	for (unsigned int j = 0; j < temporal.size() ; ++j)
	{
		this->_cubo[j] = temporal[j];
		this->_cubo[temporal.size()+j] = temporal[j];
	}

	//Incremento la profundidad y actualizo el total de celdas
	this->_profundidad ++;
	return this->_profundidad;
}

int Directorio::achicarTabla()
{
	//No hay nada que colapsar si la profundidad es cero
	if (this->_profundidad == 0) return 0;

	//Copio la tabla
	vector<unsigned int> temporal (this->_cubo);

	unsigned int newSize = temporal.size() / 2;

	//Me aseguro que todas las entradas estén habilitadas para colapsar
	for(unsigned int i =0; i<newSize;i++)
		if(this->_cubo[i] != this->_cubo[newSize+i]) return -1;


	this->_cubo.clear();
	this->_cubo.resize(newSize,0);

	//Copio los elementos a la tabla definitiva
	for (unsigned int j = 0; j < (unsigned)newSize; j++)
	{
		this->_cubo[j] = temporal[j];
	}

	this->_profundidad --;
	return this->_profundidad;
}

bool Directorio::insertarCubo (int bucketAddr, int first, int last)
{
	for(int i=first; i<= last;i++)	this->_cubo[i] = bucketAddr;
	return true;

}

void Directorio::guardar()
{
	this->dirfile->vaciar();
	this->dirfile->agregar(Util::SerializeInt(this->_profundidad));
	for (unsigned int i = 0; i < this->_cubo.size() ; i ++)
	{
		unsigned int c = this->_cubo[i];
		this->dirfile->agregar(Util::SerializeInt(c));
	}

	//Guardar el bucket actual

}

void Directorio::cargar()
{
	unsigned int registros = this->dirfile->elementos();

	//Tamaño de dispersion
	string record = this->dirfile->leer(0);
	this->_profundidad = Util::DeSerializeInt(record);
	unsigned int tam = 1 << this->_profundidad;

	//Tamaño de la tabla
	this->_cubo.clear();
	this->_cubo.resize(tam,0);

	//Levanto la info
	for(unsigned int i = 1 ; i < registros ; i++)
	{
		string record = this->dirfile->leer(i);
		this->_cubo[i-1] = Util::DeSerializeInt(record);
	}

	//Levanto un bucket
	unsigned int direccion = this->_cubo[0];
	this->cargarCubo(this->_cuboActual,direccion);
}

void Directorio::setDebug(Debug * dbg)
{
	this->_debug = dbg;
	this->_cuboActual->setDebug(dbg);
}

void Directorio::writeDebug (string data)
{
	if (this->_debug != NULL) this->_debug->writeln(data);
}

/*
string Directorio::informe (compoReg * clave)
{
	string result = "";
	result.append("Profundidad global: "); result.append(Util::toString(this->_profundidad)); result.append("\n");

	result.append ("Tabla: ");
	for (unsigned int k = 0; k < this->_cubo.size();k++)
	{
		result.append(Util::toString(this->_cubo[k]));
		result.append(" ");
	}
	result.append("\n");

	Cubo * temp = new Cubo(this,this->_maxClavesPorCubo);

	for (unsigned int k = 0; k < this->bktfile->elementos() ; k++)
	{
		if (k == (unsigned)this->_cuboActual->_direccion)
		{
			result.append(this->_cuboActual->toHuman(clave));
		} else {
			this->cargarCubo(temp,k);
			result.append(temp->toHuman(clave));
		}
	}
	delete temp;



	return result;
}
*/


string Directorio::informe ()
{
	string result = "";
	result.append("Profundidad global: "); result.append(Util::toString(this->_profundidad)); result.append("\n");

	result.append ("Tabla: ");
	for (unsigned int k = 0; k < this->_cubo.size();k++)
	{
		result.append(Util::toString(this->_cubo[k]));
		result.append(" ");
	}
	result.append("\n");

	Cubo * temp = new Cubo(this,this->_maxClavesPorCubo);

	for (unsigned int k = 0; k < this->bktfile->elementos() ; k++)
	{
		if (k == (unsigned)this->_cuboActual->_direccion)
		{
			result.append(this->_cuboActual->toHuman());
		} else {
			this->cargarCubo(temp,k);
			result.append(temp->toHuman());
		}
	}
	delete temp;



	return result;
}

