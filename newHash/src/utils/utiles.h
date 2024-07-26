/*
 * util.h
 *
 */

#ifndef UTILES_H_
#define UTILES_H_

#include <string>
#include <sstream>

enum cacheStrategy {writeback, writetrhough};

using namespace std;

const int TAM_VARIABLE = -1;

class Util {
public:
	Util();
	virtual ~Util();

	static string	toString (int value);
	static int		toInt (string value);
	static string 	SerializeInt(int value);
	static string 	SerializeString (string value);
	static string 	SerializeBool (bool value);
	static string 	SerializeChar (char value);
	static int 	DeSerializeInt (string &data);
	static string 	DeSerializeString (string& data);
	static bool 	DeSerializeBool (string &data);
	static char 	DeSerializeChar (string &data);
	static bool	archivoExiste (string filename);
};

#endif /* UTILES_H_ */
