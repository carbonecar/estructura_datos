#include "PPMC.h"
#include "../utils/const.h"
#include <exception>
#include <vector>
#include "../exceptions/PPMCExceptions.h"
#include "../utils/utiles.h"


PPMC::PPMC(int presicion, int ordenMax, bool loggear,bool loggearAritmetic)
{
	this->estadisticCounter = new EstadisticCounter();
	this->presicion=presicion;
	this->ordenMax = ordenMax;
	this->rootContext = new DistributionTable();

	for (int i = 0 ; i < C_ESC; i++)
	{
		this->rootContext->addCharacter((charDT) i);
	}
	this->logger = Logger::getInstance();
	this->loggear = loggear;
	this->loggearAritmetic = loggearAritmetic;
}

PPMC::~PPMC(){
	delete this->rootContext;
	delete this->estadisticCounter;
}

void PPMC::compress(istream * entrada, ostream * salida, bool exclusion)
{
	log ("*** Iniciando compresion ***");
	string tmp = "";

	Arithmetic aritmetic (NULL, (fstream*) salida, Arithmetic::COMPRESS,loggearAritmetic);
	DistributionTable table;

	charDT c;
	std::vector<unsigned char> exclusionVector;

	//Obtengo un contexto vacío y otro que me sirve para pararme en los contextos anteriores
	Context * currentContext = new Context (this->ordenMax);
	Context * workContext = new Context (0);
	currentContext->addCharacter(C_ESC);

	unsigned int countESC = 0;
	unsigned char tmpC;

	unsigned long bytesRead = 0;

	while (!entrada->eof())
	{
		tmpC = entrada->get();

		if(!entrada->eof())
			c = (charDT)tmpC;
		else
			c = C_EOF;

		bytesRead++;

		*workContext = *currentContext;
		table = *workContext->getDistributionTable();

		//Inicializo el vector de exclusiones
		exclusionVector.clear();

		log(c);
		log("Contexto: " + workContext->getStringContext());

		bool found = false;
		bool root = false;

		while (!found) {
			found = table.isCharacterInTable(c);

			//Excluyo caracteres
			if (exclusion) table.removeCharacters(exclusionVector);

			if (!found)
			{
				countESC++;

				aritmetic.compress(C_ESC, table);

				//Agrego los caracteres al vector de exclusión
				std::vector<char> tempVector = table.getCharsVector();
				exclusionVector.insert(exclusionVector.end(),tempVector.begin(), tempVector.end());

				try
				{
					workContext->previousContext();
					table = *workContext->getDistributionTable();
					log("No se encuentra el caracter en el contexto actual. Paso al contexto <" + workContext->getStringContext()+">");

				} catch (std::exception *e) {
					log("No se encuentra el caracter en el contexto actual. Paso al contexto -1");
					table = *this->rootContext;
					root = true;
				}
			}
			else
			{
				log("Se encuentra el caracter en el contexto actual (" + workContext->getStringContext()+")");
				if (!root)
					this->estadisticCounter->addContextHit(workContext->getStringContext());
				aritmetic.compress(c, table);
			}

		}

		updateContext(currentContext,c,countESC);
		countESC = 0;

	}
	this->estadisticCounter->setOriginalFilesize(bytesRead);
	this->estadisticCounter->setFinalFilesize(aritmetic.getBytesCounter());

	delete currentContext;
	delete workContext;
}

void PPMC::unCompress(istream * entrada, ostream * salida, bool exclusion)
{
	log("*** Iniciando descompresion ***");
	Arithmetic aritmetic ((fstream*)entrada, NULL, Arithmetic::UNCOMPRESS,loggearAritmetic);

	Context * currentContext = new Context (this->ordenMax);
	Context * workContext = new Context(0);

	currentContext->addCharacter(C_ESC);
	*workContext = *currentContext;

	DistributionTable table = *workContext->getDistributionTable();

	unsigned int countESC = 0;

	charDT c;

	std::vector<unsigned char> exclusionVector;

	c = aritmetic.uncompress(table);
	unsigned long bytesWrite = 0;
	bool root = false;

	while (c != C_EOF)
	{
		log(c);
		if (c != C_ESC)
		{
			updateContext(currentContext,c,countESC);
			countESC = 0;

			*workContext = *currentContext;
			this->estadisticCounter->addContextHit(workContext->getStringContext());

			table = *workContext->getDistributionTable();

			salida->put(c);
			bytesWrite++;
			//Inicializo el vector de exclusiones
			exclusionVector.clear();

			if (root)
				log ("Encontre el caracter en el contexto -1");

			else
				log ("Encontre el caracter en el contexto ("+workContext->getStringContext()+")");

		} else {
			countESC++;

			//Agrego los caracteres al vector de exclusión
			std::vector<char> tempVector = table.getCharsVector();
			exclusionVector.insert(exclusionVector.end(),tempVector.begin(), tempVector.end());

			try
			{
				workContext->previousContext();
				table = *workContext->getDistributionTable();
				root = false;
			}
			 catch (std::exception *e) {
				 delete e;
				table = *this->rootContext;
				root = true;
			}
		}

		//Excluyo caracteres
		if (exclusion) table.removeCharacters(exclusionVector);
		log ("Contexto actual: <" + workContext->getStringContext()+">");
		c = aritmetic.uncompress(table);
	}
	this->estadisticCounter->setOriginalFilesize(aritmetic.getBytesCounter());
	this->estadisticCounter->setFinalFilesize(bytesWrite);


	delete workContext;
	delete currentContext;

}

void PPMC::estadistict(){
}

int PPMC::getOrdenMax(){
	return this->ordenMax;
}

int PPMC::getPresicion(){
	return this->presicion;
}

void PPMC::setIndex(Index* inx){
	Context::setIndex(inx);
}

void PPMC::setRootContext(DistributionTable* dt)
{
	if (dt != NULL) {
		delete this->rootContext;
		this->rootContext = dt;
	}
}

void PPMC::updateContext(Context * currentContext,charDT charUnCompress, unsigned int countESC) {
	Context * updateContext = new Context(0);

	DistributionTable * table;

	*updateContext = *currentContext;
	table = updateContext->getDistributionTable();


	/* Actualizo contextos */
	while(table != this->rootContext)
	{
		if(countESC > 0 && table->count() > 1) {
			countESC--;
			updateContext->updateContext(C_ESC);
		}

		if(table->isCharacterInTable(charUnCompress))
			updateContext->updateContext(charUnCompress);
		else
			updateContext->addCharacter(charUnCompress);

		try
		{
			updateContext->previousContext();
			table = updateContext->getDistributionTable();
		}
		 catch (std::exception *e) {
			delete e;
			table = this->rootContext;
		}
	}

	currentContext->push(charUnCompress);
	delete updateContext;
}


void PPMC::log(charDT c) {
	std::string tmp = "Caracter leido: ";
	if (c == C_EOF)
		tmp.append("EOF");

	else if(c == C_ESC)
		tmp.append("ESCAPE");

	else
		tmp.append(1,(char)c);

	log(tmp);
}

void PPMC::log(std::string message) {
	if(loggear)
		logger->info(message);
}
