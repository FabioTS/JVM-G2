/*! \file classFlags.h
	\brief Classes das Flags

	Flags das classes (public, final, super, interface e abstract)
*/

/*! \def FLAGS
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/

#ifndef FLAGS
#define FLAGS

#include <iostream>
#include "baseTypes.h"

using namespace std;


const string flagNames[] = {"ACC_PUBLIC", "ACC_FINAL", "ACC_SUPER", "ACC_INTERFACE", "ACC_ABSTRACT"};

/*! \fn void showFlags (U2 flags)
	\brief Função para mostrar as flags de acesso ao usuário

	\param flags O valor em hexadecimal das flags.
*/
void showFlags (U2 flags);

#endif