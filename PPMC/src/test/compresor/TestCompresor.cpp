/*
 * TestCompresor.cpp
 *
 *  Created on: 19/06/2010
 *      Author: leonardo
 */

#include "TestCompresor.h"
#include "../../compresor/PPMC.h"
#include "../../ppmcindex/IndexHash.h"

TestCompresor::TestCompresor() {
	// TODO Auto-generated constructor stub

}

TestCompresor::~TestCompresor() {
	// TODO Auto-generated destructor stub
}

void TestCompresor::runTest()
{
	this->testCompressExclusive();
	this->testUncompressExclusive();
	//this->testCompressNonExclusive();
	//this->testUncompressNonExclusive();
}

void TestCompresor::testCompressExclusive()
{
	try{
		unlink("salidaCompresionExclusion.txt");
		unlink("testHash_hash.bk");
		unlink("testHash_hash.bk.fs");
		unlink("testHash_hash.dir");
		unlink("testHash_hash.dir.fs");
	} catch (...) {

	}
	//La entrada de datos (no uso CIN porque me mete ruido)
	std::fstream entrada("entrada.txt",std::fstream::in);
	std::fstream salida;

	salida.open("salidaCompresionExclusion.txt",std::fstream::out);

	PPMC ppmc(16,6,true,false);
	ppmc.setIndex(new IndexHash("testHash"));
	ppmc.compress(&entrada,&salida, true);

	entrada.close();

	salida.seekg(0,std::fstream::beg);
	salida.close();

}

void TestCompresor::testUncompressExclusive() {
	try{
			//unlink("salida.txt");
			unlink("testHash_hash.bk");
			unlink("testHash_hash.bk.fs");
			unlink("testHash_hash.dir");
			unlink("testHash_hash.dir.fs");
	} catch (...) {

	}
	//La entrada de datos (no uso CIN porque me mete ruido)
	std::fstream entrada("salidaCompresionExclusion.txt",std::fstream::in);
	std::fstream salida("salidaDescompresionExclusion.txt",std::fstream::out);

	PPMC ppmc(16,6,true,false);
	ppmc.setIndex(new IndexHash("testHash"));
	ppmc.unCompress(&entrada,&salida, true);

	entrada.close();
}

void TestCompresor::testCompressNonExclusive()
{
	try{
		unlink("salidaCompresionSinExclusion.txt");
		unlink("testHash_hash.bk");
		unlink("testHash_hash.bk.fs");
		unlink("testHash_hash.dir");
		unlink("testHash_hash.dir.fs");
	} catch (...) {

	}
	//La entrada de datos (no uso CIN porque me mete ruido)
	std::fstream entrada("entrada.txt",std::fstream::in);
	std::fstream salida;

	salida.open("salidaCompresionSinExclusion.txt",std::fstream::out);

	PPMC ppmc(16,6,true,false);
	ppmc.setIndex(new IndexHash("testHash"));
	ppmc.compress(&entrada,&salida, false);

	entrada.close();

	salida.seekg(0,std::fstream::beg);
	salida.close();

}

void TestCompresor::testUncompressNonExclusive() {
	try{
			//unlink("salida.txt");
			unlink("testHash_hash.bk");
			unlink("testHash_hash.bk.fs");
			unlink("testHash_hash.dir");
			unlink("testHash_hash.dir.fs");
	} catch (...) {

	}
	//La entrada de datos (no uso CIN porque me mete ruido)
	std::fstream entrada("salidaCompresionSinExclusion.txt",std::fstream::in);
	std::fstream salida("salidaDesompresionSinExclusion.txt",std::fstream::out);

	PPMC ppmc(16,6,true,false);
	ppmc.setIndex(new IndexHash("testHash"));
	ppmc.unCompress(&entrada,&salida, false);

	entrada.close();
}
