/*
 * cubo.cpp
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */

#include "cubo.h"
#include "directorio.h"
#include "funcionhash.h"
#include "../../utiles/utiles.h"

Directorio * directorio;

Cubo::Cubo(void* dir, unsigned int limite)
{
	//Máxima cantidad de keys que guardo en el cubo
	this->setLimitado(true);
	this->setLimite(limite);

	this->_direccion = -1;
	this->_profundidad = -1;
	this->_dir = dir;
	this->_del = false;
	directorio = (Directorio*) dir;

}

Cubo::~Cubo()
{
	// TODO Auto-generated destructor stub
}

string Cubo::serializar()
{
	string dbg;
	dbg = "Serializando bloque";this->writeDebug(dbg);
	dbg = "Numero de bloque: "; dbg.append(Util::toString(this->_direccion)); this->writeDebug(dbg);
	string result = "";
	result.append (Util::SerializeBool(this->_del));
	result.append (Util::SerializeInt(this->elementos()));
	dbg = "Elementos: "; dbg.append(Util::toString(this->elementos())); this->writeDebug(dbg);

	for (map<int, string>::iterator it = this->_elemento.begin() ; it != this->_elemento.end() ; ++it)
	{
		result.append(Util::SerializeInt(it->first));
		result.append(Util::SerializeString(it->second));
		dbg = Util::toString(it->first); dbg.append (" <-> "); dbg.append(it->second); this->writeDebug(dbg);
	}
	result.append (Util::SerializeInt(this->_profundidad));
	dbg = "Profundidad: "; dbg.append(Util::toString(this->_profundidad)); this->writeDebug(dbg); this->writeDebug("");
	return result;
}

void Cubo::deserializar(string data)
{
	this->_elemento.clear();
	string dbg = "";
	this->_del = Util::DeSerializeBool(data);
	dbg = "Deserializando bloque";this->writeDebug(dbg);
	dbg = "Numero de bloque: "; dbg.append(Util::toString(this->_direccion)); this->writeDebug(dbg);
	unsigned int elements = Util::DeSerializeInt(data);
	dbg = "Elementos: "; dbg.append(Util::toString(elements)); this->writeDebug(dbg);

	for (unsigned int k = 0; k < elements ; k++)
	{
		int clave = Util::DeSerializeInt(data);
		string reg = Util::DeSerializeString(data);
		this->_elemento.insert (pair <int,string>(clave,reg));
		dbg = Util::toString(clave); dbg.append (" <-> "); dbg.append(reg); this->writeDebug(dbg);
	}
	this->_profundidad = Util::DeSerializeInt(data);
	dbg = "Profundidad: "; dbg.append(Util::toString(this->_profundidad)); this->writeDebug(dbg); this->writeDebug("");
}

bool Cubo::insertar(int key, string data)
{
	//Si la clave está insertada, no la inserto un carajo
	if (this->existe(key)) return false;

	//Trato de insertar, si falla es porque no hay capacidad
	bool resultado = cTextIndex::insertar(key,data);

	if (resultado)
	{
		//Pude insertar, le digo al directorio que me guarde
		directorio->guardarCubo(this);
		return resultado;
	}

	//No pude insertar, no tenía espacio
	unsigned int pos = this->MakeAddress(key,directorio->_profundidad);
	bananaSplit(pos);
	return directorio->insertar(key, data);
}


bool Cubo::modificar (int key, string data)
{
	//Si la clave no está insertada, me tomo el palo
	if (!this->existe(key)) return false;

	//Trato de modificar, si falla es porque no hay capacidad
	bool resultado = cTextIndex::modificar(key,data);

	if (resultado)
	{
		//Pude modificar, le digo al directorio que me guarde
		directorio->guardarCubo(this);
	}
	return resultado;
}

bool Cubo::eliminar (int key)
{

	unsigned int myPos = this->MakeAddress(key,directorio->_profundidad);

	bool result = cTextIndex::eliminar(key);
	if (! result) return false;
	if (this->elementos()==0)
	{
		this->intentarCombinar(myPos);

	} else {
		directorio->guardarCubo(this);
	}
	return true;
}

/**
 * Intenta combinar el cubo actual con su par
 */
bool Cubo::intentarCombinar(unsigned int myPos)
{
	//unsigned int delta = this->_profundidad/2;
	unsigned int delta = (1 << this->_profundidad)/2;
	//unsigned int pos1 = (myPos + delta) % (directorio->_cubo.size()+1);
	unsigned int pos1 = (myPos + delta) % (directorio->_cubo.size());
	//unsigned int pos2 = (myPos - delta) % (directorio->_cubo.size()+1);
	unsigned int pos2 = (myPos - delta) % (directorio->_cubo.size());

	unsigned int elem1 = directorio->_cubo[pos1];
	unsigned int elem2 = directorio->_cubo[pos2];

	if (elem1 == elem2)
	{
		directorio->_cubo[myPos] = elem1;
		this->_del = true;
		directorio->guardarCubo(this);
		directorio->cargarCubo(this,elem1);
		this->_profundidad--;
		directorio->guardarCubo(this);
		directorio->achicarTabla();
		return true;
	}
	directorio->guardarCubo(this);
	return false;
}

/**
 * Me parto en dos cubos
 * Devuelve un cubo nuevo
 */
Cubo* Cubo::bananaSplit(unsigned int currentPos)
{

	//Calculo la posicion actual
	//unsigned int currentPos = this->MakeAddress(this->getClave(0),directorio->_profundidad);

	unsigned int d = directorio->_profundidad;
	if (this->_profundidad == d)
	{
		//Duplico la tabla
		directorio->duplicarTabla();

		//Creo un nuevo bucket (lo uso para redistribuir)
		Cubo* newBucket = new Cubo (directorio, this->_limite);
		directorio->guardarCubo(newBucket);

		//Lo inserto a la tabla
		directorio->insertarCubo(newBucket->_direccion, currentPos, currentPos);

		//Incremento las profundidades
		this->_profundidad++;
		newBucket->_profundidad = this->_profundidad;

		//Redistribuyo el bucket actual con el nuevo
		Redistribute (*newBucket);

		//Guardo los dos buckets
		directorio->guardarCubo(this);
		directorio->guardarCubo(newBucket);

		//Libero memoria
		directorio->_cuboActual=this;
		delete newBucket;

	} else {
		this->_profundidad++;

		//Creo un nuevo bucket (lo uso para redistribuir)
		Cubo* newBucket = new Cubo (directorio, this->_limite);
		newBucket->_profundidad = this->_profundidad;
		directorio->guardarCubo(newBucket);

		unsigned int delta = (1 << newBucket->_profundidad);

		unsigned int elem = currentPos;
		do
		{
			directorio->_cubo[elem] = newBucket->_direccion;
			elem = ((elem + delta) % directorio->_cubo.size());
		} while (elem != currentPos);

		this->Redistribute(*newBucket);
		//Guardo los dos buckets
		directorio->guardarCubo(this);
		directorio->guardarCubo(newBucket);
		delete newBucket;
	}

	return NULL;
}

/**
 * Redistribuyo el bucket actual con el nuevo
 */
void Cubo::Redistribute (Cubo & newBucket)
{
	string reg = "";
	reg = "Redistribuyendo entre bloque "; reg.append (Util::toString(this->_direccion));reg.append (" y ");reg.append (Util::toString(newBucket._direccion)); this->writeDebug(reg);

	for(int i = this->elementos() -1 ; i >= 0 ; i--)
	{
		int clave = this->getClave(i);
		string reg = this->getReg(i);

		int bucketAddr = directorio->encontrar(clave);
		if (bucketAddr != this->_direccion)
		{
			//El hash recalculado va al blucket nuevo, lo muevo.
			newBucket.cTextIndex::insertar(clave,reg);
			cTextIndex::eliminar(clave);
		}
	}

	//Info de estado
	this->writeDebug("Estado luego de la redistribucion");
	reg = "Bloque: "; reg.append (Util::toString(this->_direccion));this->writeDebug(reg);
	reg = "Profundidad: "; reg.append (Util::toString(this->_profundidad));this->writeDebug(reg);
	reg = "Elementos: "; reg.append (Util::toString(this->elementos()));this->writeDebug(reg);
	for (unsigned int k = 0; k < this->elementos() ; k++)
	{
		reg = Util::toString(this->getClave(k)); reg.append(" <-> "); reg.append (this->getReg(k));this->writeDebug(reg);
	}

	this->writeDebug("");

	reg = "Bloque: "; reg.append (Util::toString(newBucket._direccion));this->writeDebug(reg);
	reg = "Profundidad: "; reg.append (Util::toString(newBucket._profundidad));this->writeDebug(reg);
	reg = "Elementos: "; reg.append (Util::toString(newBucket.elementos()));this->writeDebug(reg);
	for (unsigned int k = 0; k < newBucket.elementos() ; k++)
	{
		reg = Util::toString(newBucket.getClave(k)); reg.append(" <-> "); reg.append (newBucket.getReg(k));this->writeDebug(reg);
	}
	this->writeDebug("");
}

bool Cubo::asNew(string data)
{
	bool flag = Util::DeSerializeBool(data);
	return (flag);
}
/*
string Cubo::toHuman(compoReg * clave)
{
	string result = "";
	result.append("#Cubo: "); result.append(Util::toString(this->_direccion));result.append("\n");
	if (this->_del)
	{
		result.append("Cubo libre\n");

	} else {
		result.append("Profundidad: "); result.append(Util::toString(this->_profundidad));result.append("\n");
		result.append (cTextIndex::toHuman(clave));
	}

	return result;

}
*/

string Cubo::toHuman()
{
	string result = "";
	result.append("#Cubo: "); result.append(Util::toString(this->_direccion));result.append("\n");
	if (this->_del)
	{
		result.append("Cubo libre\n");

	} else {
		result.append("Profundidad: "); result.append(Util::toString(this->_profundidad));result.append("\n");
		result.append (cTextIndex::toHuman());
	}

	return result;

}
