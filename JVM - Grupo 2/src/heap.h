/*! \file heap.h
	\brief Arquivo que define o Heap

	Controlar os endereços de memória alocados.
*/

/*! \def HEAP
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/


#ifndef HEAP
#define HEAP

#include "classe.h"
#include <vector>

/*! \class Heap
	\brief Classe do heap

	Controlar os endereços de memórias alocados.
*/	
class Heap {
private:
	static vector<ClasseInstancia*> objetos;
public:
	/*! \fn static void addObject(ClasseInstancia* ci)
		\brief Pega o objeto que foi criado e coloca o endereço no vetor de classes instanciadas.

		\param ci Referência para o objeto instanciado.
	*/
	static void addObject(ClasseInstancia*);
};

#endif