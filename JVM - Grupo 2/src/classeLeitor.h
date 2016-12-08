/*! \file classeLeitor.h
	\brief Leitor e exibidor

	Tem todas as informações do .class e realiza a leitura, podendo exibilas ou não.
*/

/*! \def CLASSE_LEITOR
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/
#ifndef CLASSE_LEITOR
#define CLASSE_LEITOR

class Leitor;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string>
#include "baseTypes.h"
#include "constantPool.h"
#include "classFlags.h"
#include "fields.h"
#include "attributes.h"
#include "interfaces.h"
#include "methods.h"
#include "methodArea.h"

//defines para os tipos de erro possiveis
#define MISSING_ARGUMENT 1
#define CANT_OPEN 2
#define INVALID_FILE 3
#define UNKNOWN_TYPE 4
#define INVALID_NAME 5
#define INVALID_EXTENSION 6
#define MISSING_MAIN 7

/*! \class Leitor
	\brief Todas funções de leitura/exibição

	Contém todas as funções para realizar a leitura e exibição as informações relativas ao .class.
*/
class Leitor {
public:
	/*! \fn Leitor(char *in)
		\brief Construtor do Leitor.

		\param in Caminho do arquivo .class.
	*/
	Leitor(char *in);

	/*! \fn Leitor(char *in)
		\brief Construtor do Leitor.

		\param in Caminho do arquivo .class.
	*/
	Leitor(std::string in);

	/*! \fn int run()
		\brief Carrega as informações do .class e as mostra
	*/
	int run();

	/*! \fn int load()
		\brief Carrega as informações do .class
	*/
	int load();

	/*! \fn bool show()
		\brief Exibe as informações do .class
	*/
	bool show();

	/*! \fn bool validExtension ()
		\brief Verifica se a extensão é de fato .class
	*/
	bool validExtension ();

	/*! \fn bool hasMain()
		\brief Verifica se o .class tem de fato uma main()
	*/
	bool hasMain();

	/*! \fn method_info getMain()
		\brief Retorna o método que é o main
	*/
	method_info getMain();

	/*! \fn bool hasClinit()
		\brief Verifica se o .class tem um metodo <clinit>
	*/
	bool hasClinit();

	/*! \fn method_info getClinit()
		\brief Retorna o método que é o <clinit>
	*/
	method_info getClinit();

	/*! \fn bool checkThisClass ()
		\brief Verifica se o nome da classe definida bate com o nome da classe sem a extensão
	*/
	bool checkThisClass ();


	/*! \fn int getStatus()
		\brief Retorna o Status da leitura, informando ao método chamador o que aconteceu
	*/
	int getStatus();

	/*! \fn cp_info *getCP()
		\brief Retorna uma referência para a constant pool.
	*/
	cp_info *getCP() const;

	/*! \fn U2 getLengthCP()
		\brief Pega o tamanho da Constant Pool do .class.
	*/
	U2 getLengthCP();

	/*! \fn char *getPath()
		\brief Pega o caminho até o diretório em que o arquivo .class
	*/
	char *getPath();

	/*! \fn method_info *getMethods()
		\brief Pega todos os métodos do .class
	*/
	method_info *getMethods();

	/*! \fn U2 getMethodsCount()
		\brief Pega todos os métodos do .class
	*/
	U2 getMethodsCount();

	/*! \fn U2 getThis_class()
		\brief Retorna um índice do constant pool que aponta pra string com o nome da classe.
	*/
	U2 getThis_class();

	/*! \fn U2 getSuper_class()
		\brief Retorna um índice do constant pool que aponta pra string com o nome da super classe.
	*/
	U2 getSuper_class();

	/*! \fn U2 getFieldsCount()
		\brief Retorna o número de campos do arquivo .class
	*/
	U2 getFieldsCount();

	/*! \fn U2 getFields()
		\brief Pega todos os campos do .class
	*/
	field_info *getFields();


	/*! \fn U2 getField()
		\brief Pega um campo do .class

		\param field_name Nome da field desejada
	*/
	field_info *getField(string field_name);


	/*! \fn U2 getMethod(ClasseInstancia* i, string name, string descriptor)
		\brief Retorna method_info o leitor contenha o metodo com o nome e descritor especificados

		\param name Nome do metodo a ser procurado
		\param descriptor Descritor do metodo a ser procurado
	*/
	method_info* getMethod(string name, string descriptor);


	/*! \fn U2 getClassThatHasSerachedMethod(string name, string descriptor)
		\brief Retorna o ponteiro para o leitor da classe que contem o metodo encontrado em getMethod

		\param name Nome do metodo a ser procurado
		\param descriptor Descritor do metodo a ser procurado
	*/
	Leitor* getClassThatHasSerachedMethod(string name, string descriptor);

private:
	/*! \fn bool findMain()
		\brief Descobre qual dos métodos do arquivo .class é o main
	*/
	bool findMain();

	/*! \fn bool findMain()
		\brief Descobre qual dos métodos do arquivo .class é o <clinit>, caso ele exista
	*/
	bool findClinit();

	/*! \fn string getError(int)
		\brief Retorna a string que contém a mensagem de erro correspondente ao índice que recebe como parâmetro
	
		\param error Índice que localiza a string que contém a mensagem de error
	*/
	string getError(int);

	int status, mainMethod, clinit;
	bool foundMain, foundClinit;
	char *fileName;
	U2 minVersion, majVersion, lengthCP;
	U2 this_class, super_class, interfacesCount, fieldsCount;
	U2 methodsCount, accessFlags, attributesCount;
	U2 *interfaces;
	cp_info *constantPool;
	field_info *fields;
	method_info *methods;
	attribute_info *attributes;
	FILE *fp;
};

#endif