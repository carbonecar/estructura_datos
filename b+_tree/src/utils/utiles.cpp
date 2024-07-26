/*
 * util.cpp
 *
 *  Created on: 03/10/2009
 *      Author: leonardo
 */

#include "utiles.h"
#include <stdio.h>

Util::Util() {

}

Util::~Util() {
}


string Util::SerializeInt(int value)
{
	char *memoria = (char*)&value;
	string response (memoria,sizeof(int));
	return response;
}

string Util::SerializeString (string value)
{
	string response (SerializeInt(value.length()));
	response.append(value);
	return response;
}

string Util::SerializeBool (bool value)
{
	if (value) return "1";
	return "0";
}

string Util::SerializeChar (char value)
{
	string response = " ";
	response[0] = value;
	return response;
}

int Util::DeSerializeInt (string &data)
{
	int *result = new int;
	data.copy((char*)result,sizeof(int));
	data.erase(0,sizeof(int));
	return *result;
}

string Util::DeSerializeString (string& data)
{
	string size (data,0,4);
	int tam = DeSerializeInt(size);

	string info (data,4,tam);

	data.erase(0,sizeof(int));
	data.erase(0,tam);
	return info;

}

bool Util::DeSerializeBool (string &data)
{
	bool response = true;
	if (data[0] == '0') response = false;
	data.erase(0,1);
	return response;
}

char Util::DeSerializeChar (string &data)
{
	char response = data[0];
	data.erase(0,1);
	return response;
}


string Util::toString(int value)
{
	std::stringstream out;
	out << value;
	return  out.str();
}

int	Util::toInt (string str)
{
	stringstream ss(str);
	int n;
	ss >> n;
	return n;
}

bool Util::archivoExiste (string filename)
{
	if (FILE * file = fopen(filename.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	return false;
}
