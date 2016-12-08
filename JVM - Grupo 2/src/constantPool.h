/*! \file constantPool.h
	\brief Pool de Constantes

	Possui todas as constantes definidas na classe.
*/

/*! \def CONSTANTPOOL
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/

#ifndef CONSTANTPOOL
#define CONSTANTPOOL

#include "baseTypes.h"

using namespace std;

//defines para os tipos possiveis do pool de constantes
#define INVALID 99 //para indicar que eh um slot para guardar a segunda parte de um long ou double
#define UTF8 1
#define INTEGER 3
#define FLOAT 4
#define LONG 5
#define DOUBLE 6
#define CLASS 7
#define STRING 8
#define FIELD_REF 9
#define METHOD_REF 10
#define INTERFACE_REF 11
#define NAME_AND_TYPE 12

//arrays para facilitar a formatacao dos dados
const string typeNames[] = {"UTF-8", "-", "Integer", "Float", "Long", "Double", "Class", "String", "Field", "Method", "Interface", "Name and Type"};

/*! \struct cp_info
	\brief Estrutura de armazenamento

	Estrutura responsável pelo armazenamento da pool de constantes.
*/	
typedef struct {
	U1 tag;
	ClassLoaderType *info;
} cp_info;

/*! \fn int loadConstantPool (cp_info *constantPool, int lengthCP, FILE* fp)
		\brief Carregar as informações do pool de constantes na memória

		\param constantPool Ponteiro referente à estrutura responsável pelo armazenamento da pool de constantes
		\param lengthCP O número de elementos na pool de constantes menos 1
		\param fp Ponteiro que referencia o arquivo .class 
*/
int loadConstantPool (cp_info *constantPool, int lengthCP, FILE* fp);

/*! \fn string dereferenceIndex (cp_info *cp, U2 index)
		\brief Função recursiva para dereferenciar o índice e mostrar a informação que será usada.

		\param cp Ponteiro referente à estrutura responsável pelo armazenamento da pool de constantes
		\param index Índice pra um elemento da constante pool
*/
string dereferenceIndex (cp_info *cp, U2 index);

/*! \fn void showConstantPool (cp_info *constantPool, int lengthCP)
		\brief Função responsável por mostrar todas informações da pool de constantes.

		\param constantPool Ponteiro referente à estrutura responsável pelo armazenamento da pool de constantes
		\param lengthCP O número de elementos na pool de constantes menos 1
*/
void showConstantPool (cp_info *constantPool, int lengthCP);

#endif