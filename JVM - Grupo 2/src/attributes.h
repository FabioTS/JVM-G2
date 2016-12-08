/*! \file attributes.h
	\brief Atributos 

	Atributos dos métodos e dos campos	
*/

/*! \def ATTRIBUTE
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/
#ifndef ATTRIBUTE
#define ATTRIBUTE

#include <iostream>
#include <stdlib.h>
#include <string>
#include "constantPool.h"

using namespace std;
/*!
	Protótipo da struct attribute_info
*/
struct attribute_info;

/*! \struct constantvalue_attribute
	\brief Estrutura de armazenamento.

	Struct responsável por armazenar atributos do tipo CONSTANTVALUE
*/
typedef struct {
	unsigned short constantvalue_index;
} constantvalue_attribute;

/*! \struct t_exception_table
	\brief Componente de outra struct

	Struct de Exception que faz parte da struct code_attribute
*/	
typedef struct {
	unsigned short start_pc;
	unsigned short end_pc;
	unsigned short handler_pc;
	unsigned short catch_type;
} t_exception_table;

/*! \struct code_attribute
	\brief Componente de outra struct

	Struct responsável por armazenar atributos do tipo CODE
*/	
typedef struct {
	unsigned short max_stack;
	unsigned short max_locals;
	unsigned int code_length;
	unsigned char* code;
	unsigned short exception_table_length;
	t_exception_table** exception_table;
	unsigned short attribute_count;
	attribute_info* attributes;
} code_attribute;

/*! \struct code_attribute
	\brief Componente de outra struct

	Struct responsável por armazenar atributos do tipo EXCEPTION
*/	
typedef struct {
	unsigned short number_of_exceptions;
	unsigned short* exception_index_table;
} exception_attribute;

/*! \union t_info
	\brief Representação de diferentes atributos

	Union responsável por representar os diferentes campos dos atributos
*/	
typedef union {
	constantvalue_attribute constantvalue;
	code_attribute code;
	exception_attribute exception;
} t_info;

/*! \struct attribute_info
	\brief Estrutura de armazenamento

	Struct responsável por armazentar os atributos
*/	
struct attribute_info {
	unsigned short name_index;
	unsigned int length;

	t_info* info;
};

/*! \fn t_exception_table* readExceptionHandler(FILE* fp)
	\brief Função para ler o tratador da exceção

	\param fp Ponteiro para o arquivo .class.
*/
t_exception_table* readExceptionHandler(FILE* fp);

/*! \fn t_info* readAttributeInfo(FILE* fp, cp_info *cp, unsigned short index, unsigned short length)
	\brief Lê as informações do atributo

	\param fp Ponteiro para o arquivo .class.
	\param cp Ponteiro para a constant pool.
	\param index Aponta para um elemento da constant pool.
	\param length Tamanho em bytes do atributo que vai ser lido.
*/
t_info* readAttributeInfo(FILE* fp, cp_info *cp, unsigned short index, unsigned short length);

/*! \fn attribute_info readAttribute (FILE* fp, cp_info *cp)
	\brief Lê o atributo

	\param fp Ponteiro para o arquivo .class.
	\param cp Ponteiro para a constant pool.
*/
attribute_info readAttribute (FILE* fp, cp_info *cp);

/*! \fn attribute_info* readAttributes(FILE* fp, cp_info *cp, int length)
	\brief Lê o atributo

	\param fp Ponteiro para o arquivo .class.
	\param cp Ponteiro para a constant pool.
	\param length Número de atributos.
*/
attribute_info* readAttributes(FILE* fp, cp_info *cp, int length);

/*! \fn void showAttribute (attribute_info a, cp_info *cp)
	\brief Função para mostra ao usuário um atributo

	\param a Estrutura que contém as informações do tipo atributo.
	\param cp Ponteiro para a constant pool.

*/
void showAttribute (attribute_info a, cp_info *cp);

/*! \fn void showAttributes(attribute_info* attributes, cp_info* cp, int length)
	\brief Função que chama showAttribute length vezes

	\param attributes Ponteiro para a estrutura que contém as informações do tipo atributo.
	\param cp Ponteiro para a constant pool.
	\param length Número de vezes que a função showAttribute será chamada.
*/
void showAttributes(attribute_info* attributes, cp_info* cp, int length);

/*! \fn string getMnemonic(int opcode)
	\brief Dado o opcode ele retorna o nome da operação

	\param opcode Opcode correspondente a uma função da JVM.
*/
string getMnemonic(int opcode);

/*! \fn uint32_t getNBytesValue(uint8_t n, unsigned char* code, int* index)
	\brief Função que retorna um valor composto por n bytes
	
	\param n Número de bytes que deseja-se ler.
	\param code Ponteiro de bytes que são os códigos e seus argumentos.
	\param index Índice que aponta para o endereço em que se deseja ler o parâmetro do opcode.
*/
uint32_t getNBytesValue(uint8_t n, unsigned char* code, int* index);

/*! \fn void getOpcodeParams(unsigned char* code, int* index)
	\brief Função que mostra na tela os parâmetros dos opcodes
	
	\param code Ponteiro de bytes que são os códigos e seus argumentos.
	\param index ìndice que aponta para o endereço em que se deseja ler o parÂmetro do opcode.
*/
void getOpcodeParams(unsigned char* code, int* index);

#endif