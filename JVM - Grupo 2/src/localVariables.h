/*! \file localVariables.h
	\brief Variáveis Locais

	Armazena variáveis locais ao método corrente
*/

/*! \def LOCALVARIABLES
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/

#ifndef LOCALVARIABLES
#define LOCALVARIABLES

#include <cstdint>
#include <stack>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "baseTypes.h"

//para testar se os enderecos sao de 32 ou 64 bits
#define BITS (sizeof(int*) == 8)

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6

/*! \class LocalVariables
	\brief Classe das variáveis locais

	Responsável por todas as operações que envolvem as variáveis locais.
*/	
class LocalVariables {
private:
	//array para os valores
	uint32_t *elements;
	//array para os tipos
	uint8_t *types;
	//quantidada maxima de slots
	const uint16_t max;
	const uint16_t realMax;
	//indica se os tipos ocupam 2 slots (utilizado para simular arrays)
	const bool dois;
public:
	/*! \fn LocalVariables(uint16_t maxSize)
		\brief Construtor da classe LocalVariables

		\param maxSize Tamanho máximo de variáveis locais que você pode armazenar.
	*/
	LocalVariables(uint16_t);

	/*! \fn LocalVariables(uint16_t maxSize)
		\brief Construtor da classe LocalVariables

		\param maxSize Tamanho máximo de variáveis locais que você pode armazenar.
		|param slots Indica se deve utilizar dois slots para todos os elementos.
	*/
	LocalVariables(uint16_t, bool);
	/*! \fn ~LocalVariables()
		\brief Destrutor4
	*/
	~LocalVariables();

	/*! \fn void printall() const
		\brief Função para exibir os valores
	*/
	void printall() const;

	/*! \fn void set(int index, typedElement x)
		\brief Recebe o elemento tipado e insere no índice passado.

		\param index Indica o índice em que irá se inserir o elemento passado.
		\param x Elemento tipado que será inserido no índice indicado.
	*/
	void set(int, typedElement);

	/*! \fn typedElement get(int index) const
		\brief Pega o elemento na posição passada por index

		\param index Indica o índice em que irá se obter o elemento.
	*/
	typedElement get(int) const;

	/*! \fn int getMax() const
		\brief Função para se saber o tamanho máximo
	*/
	int getMax() const;

	//funcao para permitir o uso da classe como se fosse um array de structs
	/*! \fn const typedElement operator[] (const int index) const
		\brief Função para permitir o uso da classe como se fosse um array de estruturas

		\param index Indica o índice que se deve acessar para obter o elemento tipado
	*/
	const typedElement operator[] (const int) const;

};

#endif