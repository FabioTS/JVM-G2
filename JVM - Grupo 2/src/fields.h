/*! \file fields.h
	\brief Campos de classe

	Campos utilizados nos arquivos com formato .class
*/

/*! \def FIELDS 
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/
#ifndef FIELDS
#define FIELDS

#include "baseTypes.h"
#include "constantPool.h"
#include "attributes.h"

using namespace std;

/*! \struct field_info
	\brief Estrutura de armazenamento.

	Struct responsável por armazenar os campos declarados
*/
typedef struct {
	unsigned char accessFlags;
	unsigned char name_index;
	unsigned char descriptor_index;
	unsigned char attributes_count;
	attribute_info *attributes;
} field_info;

/*! \fn string getFieldFlags(unsigned short flags)
	\brief Função para mostrar as flags dos campos

	\param flags Flags em valor hexadecimal que serão convertidas para string.
*/
string getFieldFlags (unsigned short flags);

/*! \fn field_info readField (FILE* fp, cp_info *cp)
	\brief Função para ler um campo

	\param fp Ponteiro para o arquivo .class.
	\param cp Ponteiro para a constant pool.
*/
field_info readField (FILE* fp, cp_info *cp);


/*! \fn field_info *readFields (FILE* fp, int length,cp_info *cp)
	\brief Função que aloca o espaço para field_info e chama a função readField length vezes

	\param fp Ponteiro para o arquivo .class.
	\param length Define quantidade de vezes que readField é chamada.
	\param cp Ponteiro para a constant pool.
*/
field_info *readFields (FILE* fp, int length,cp_info *cp);


/*! \fn void showField (field_info f, cp_info *cp)
	\brief Função para mostrar ao usuário um campo com índice no array.

	\param f Struct que contém as informações dos campos.
	\param index Indicar qual índice do vetor contém o field.
	\param cp Ponteiro para a constant pool.
*/
void showField (field_info f, cp_info *cp, int index);

/*! \fn void showFields (field_info *f, cp_info *cp, int length)
	\brief Função responsável por invocar showField length vezes

	\param f Struct que contém as informações dos campos.
	\param cp Ponteiro para a constant pool.
	\param length Define quantidade de vezes que showField será chamada.
*/
void showFields (field_info *f, cp_info *cp, int length);

#endif