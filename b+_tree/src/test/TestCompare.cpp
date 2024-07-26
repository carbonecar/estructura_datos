/*
 * TestCompare.cpp
 *
 *  Created on: Apr 24, 2010
 *      Author: carlos
 */

#include "TestCompare.h"
#include "../BPlusTree/Element.h"
#include "../BPlusTree/EqualElementComparator.h"
#include <vector>
#include <cstdio>

using namespace std;
TestCompare::TestCompare() {

}

void TestCompare::run(){
	Element* elem1=new Element();
	Element* elem2=new Element();

	elem1->setKey(1);
	elem2->setKey(2);

	if(*elem1>*elem2){

	}else{
		cout<<" elem1 es mayor a elem2";
	}

	elem1->setKey(2);
	if(*elem1==*elem2){
		cout<<"son iguales"<<endl;
	}else{
		cout<<"error en la comparacion"<<endl;
	}

	elem1->setKey(1);
	vector<Element* > elements;
	elements.push_back(elem1);
	elements.push_back(elem2);
	std::vector<Element*>::iterator it;
	cout<<"Mostramos Los elementos del vector"<<endl;
	for(it=elements.begin();it!=elements.end();it++){
		cout<<*(*it)<<endl;
	}
	cout<<"Buscamos un elemento con clave 3"<<endl;
	//hay que hacer el find a mano porque para comparar el vector deberia de ser de referencias y no de punteros
	//o en su defecto crear un functor
	it = find_if(elements.begin(), elements.end(), bind2nd(EqualElementComparator(),new Element(2,"abc",3)));
	if(it!=elements.end()){
		cout<<"encontrado"<<endl;
		cout<< *(*it);


	}
}

TestCompare::~TestCompare() {
}
