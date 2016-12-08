/*! \file baseTypes.h
	\brief Tipos Base 

	Tipos básicos utilizados para implementarmos a JVM.
*/

/*! \def BASE
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/
#ifndef BASE
#define BASE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

#define Float_NaN 0x7f800001
#define Float_PlusInfinity 0x7f800000
#define Float_MinusInfinity 0xff800000
#define Double_NaN 0x7ff0000000000001L 
#define Double_PlusInfinity 0x7ff0000000000000L
#define Double_MinusInfinity 0xfff0000000000000L

#define RT_BYTE 1
#define RT_BOOL 2
#define RT_CHAR 3
#define RT_SHORT 4
#define RT_INT 5
#define RT_FLOAT 6
#define RT_DOUBLE 7
#define RT_REFERENCE 8
#define RT_LONG 9

typedef uint8_t U1;
typedef uint16_t U2;
typedef uint32_t U4;

/*! \union ClassLoaderType
	\brief Estrutura de armazenamento

	Union responsável por armazenar todos os tamanhos de variável que serão lidos.
*/	
typedef union {
	U1 *array; //ponteiro para uma string
	U1 u1; //8 bytes
	U2 u2; //16 bytes
	U4 u4; //32 bytes
} ClassLoaderType;

/*! \union element_u
	\brief Generalização das funções de retorno/entrada

	Union responsável por generalizar as funções de retorno e também, uma das de entrada.
*/	
typedef union element_u {
	double d;
	float f;
	uint32_t i;
	int32_t is;
	uint64_t l;
	int64_t ls;
	uint16_t s;
	int16_t ss;
	uint8_t b;
	int8_t bs;
	int* pi;
} element;

typedef struct {
	int* dims;
	int* array; 
} n_array;


/*! \struct typedElement_s
	\brief Agregador de tipo e informação

	Estrutura responsável por juntar o tipo com a informação de dado elemento.
*/	
typedef struct typedElement_s {
	element value;
	uint8_t type;
	uint8_t realType;
} typedElement;

/*! \fn U1 readU1 (FILE *fp)
	\brief Função para ler 1 byte do arquivo

	\param fp Ponteiro para o arquivo .class.
*/
U1 readU1 (FILE *fp);

/*! \fn U2 readU2 (FILE *fp)
	\brief Função para ler 2 bytes do arquivo

	\param fp Ponteiro para o arquivo .class.
*/
U2 readU2 (FILE *fp);

/*! \fn U4 readU4 (FILE *fp)
	\brief Função para ler 4 bytes do arquivo

	\param fp Ponteiro para o arquivo .class.
*/
U4 readU4 (FILE *fp);

/*! \fn U1 * readUTF8 (FILE* fp, int size)
	\brief Função para ler os bytes de uma string UTF-8

	\param fp Ponteiro para o arquivo .class.
	\param size Tamanho do que vai ser alocado.
*/
U1 * readUTF8 (FILE* fp, int size);

/*! \fn string showUTF8 (unsigned char * s, int size)
	\brief Função para montar e mostrar a string UTF-8

	\param s Ponteiro para o começo de uma string Unicode.
	\param size Tamanho do que vai ser mostrado na tela.
*/
string showUTF8 (unsigned char * s, int size);

/*! \fn int checkFloat(float)
	\brief Função para checar infinito e Not a Number em floats

	\param float Número à ser checado pela função
*/
int checkFloat(float);

/*! \fn int checkDouble(double)
	\brief Função para checar infinito e Not a Number em doubles

	\param double Número à ser checado pela função
*/
int checkDouble(double);

/*! \fn string float_to_string(float)
	\brief Função para converter um float em uma string

	\param float Número à ser convertido pela função

*/
string float_to_string(float);

/*! \fn string double_to_string(double)
	\brief Função para converter um double em uma string

	\param double Número à ser convertido pela função
*/
string double_to_string(double);

/*! \fn float u4_to_float (ClassLoaderType in)
	\brief Função para converter 4 bytes em um float

	\param in Quatro bytes à ser convertido pela função
*/
float u4_to_float (ClassLoaderType in);

/*! \fn long u4_to_long (ClassLoaderType high, ClassLoaderType low)
	\brief Função para converter 8 bytes em um long

	\param high Quatro bytes mais significativos à serem convertidos pela função
	\param low Quatro bytes menos significativos à serem convertidos pela função
*/
long u4_to_long (ClassLoaderType high, ClassLoaderType low);


/*! \fn double u4_to_double (ClassLoaderType high, ClassLoaderType low)
	\brief Função para converter 8 bytes em um double

	\param high Quatro bytes mais significativos à serem convertidos pela função
	\param low Quatro bytes menos significativos à serem convertidos pela função
*/
double u4_to_double (ClassLoaderType high, ClassLoaderType low);


#endif