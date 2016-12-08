/*! \file interfaces.h
	\brief Interfaces 

	Contém todas as informações para verificar se os arquivos .class contém interfaces
*/

/*! \def INTERFACES
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/

#ifndef INTERFACES
#define INTERFACES

#include <iostream>
#include "constantPool.h"
#include "baseTypes.h"

/*! \fn unsigned short *readInterfaces (FILE *fp, int length)
	\brief Carrega as interfaces para a memória

	\param fp Ponteiro que aponta para o arquivo .class
	\param length Quantidade de interfaces
*/
unsigned short *readInterfaces (FILE *fp, int length);

/*! \fn void showInterfaces (unsigned short *interfaces, cp_info *cp, int length)
	\brief Mostra todas as interfaces, iterando sobre o vetor de interfaces

	\param interfaces Vetor de interfaces
	\param cp Ponteiro que aponta para a pool de constants
	\param length Tamanho do vetor de interfaces
*/
void showInterfaces (unsigned short *interfaces, cp_info *cp, int length);

/*! \fn showInterface (unsigned short interface, cp_info *cp)
	\brief Mostra uma interface específica 

	\param interface Índice do pool de constante
	\param cp Ponteiro que aponta para a pool de constants
*/
void showInterface (unsigned short interface, cp_info *cp);

/*! \fn showInterface (unsigned short interface, cp_info *cp, int index)
	\brief Mostra uma interface específica junto com o index da interface no vetor de interfaces

	\param interface Índice do pool de constant
	\param cp Ponteiro que aponta para a pool de constants
	\param index Índice da interface que se deseja mostra no vetor de interfaces
*/
void showInterface (unsigned short interface, cp_info *cp, int index);


#endif