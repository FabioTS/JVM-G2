/*! \file pilhaOperandos.h
	\brief Pilha de Operandos

	Pilha responsável por armazenar os operandos presentes na JVM.	
*/

/*! \def PILHAOPERANDOS
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/

#ifndef PILHAOPERANDOS
#define PILHAOPERANDOS

#include <stack>
#include <cstdint>
#include <string>
#include <sstream>
#include <stdbool.h>
#include "baseTypes.h"

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6


/*! \class PilhaOperandos
	\brief Classe da pilha de operandos

	Responsável por manipular a pilha de operandos.
*/	
class PilhaOperandos {
private:
	//pilha para os valores armazenados
	std::stack<uint32_t> elementos;
	//pilha para os tipos dos valores armazenados
	std::stack<uint8_t> tipos;
	//pilha para os tipos dos valores armazenados
	std::stack<uint8_t> tiposReais;
	bool typePushed;
	//variavel para saber se o sistema tem 64 bits
	static const bool bits64 = (sizeof(int*) == 8);
	//variavel para saber o tamanho maximo da pilha
	const int realMax;
public:
	/*! \fn PilhaOperandos(int maxSize)
		\brief Construtor

		\param maxSize Indica tamanho máximo da pilha de operandos.
	*/
	PilhaOperandos(int);

	/*! \fn uint8_t top_type()
		\brief Recupera o tipo do topo da pilha de operandos.
	*/
	uint8_t top_type();

	/*! \fn element top_value()
		\brief Recupera o valor do topo da pilha de operandos.
	*/
	element top_value();

	/*! \fn element pop()
		\brief Desempilha o operando do topo.
	*/
	element pop();

	/*! \fn element pop()
		\brief Desempilha o operando do topo já retornando seus tipos juntamente.
	*/
	typedElement popTyped();

	/*! \fn std::string getString()
		\brief Funcao para receber o topo formatado em uma string.
	*/
	std::string getString();
	
	/*! \fn void push(int x)
		\brief Função que empilha um valor x do tipo inteiro

		\param x Valor a ser empilhado na pilha.
	*/
	void push(int);

	/*! \fn void push(long x)
		\brief Função que empilha um valor x do tipo long

		\param x Valor a ser empilhado na pilha.
	*/
	void push(long);

	/*! \fn void push(float x)
		\brief Função que empilha um valor x do tipo float

		\param x Valor a ser empilhado na pilha.
	*/
	void push(float);

	/*! \fn void push(double x)
		\brief Função que empilha um valor x do tipo double

		\param x Valor a ser empilhado na pilha.
	*/
	void push(double);

	/*! \fn void push(bool x)
		\brief Função que empilha um valor x do tipo booleano.

		\param x Valor a ser empilhado na pilha.
	*/
	void push(bool);

	/*! \fn void push(int *x)
		\brief Função que empilha um valor x do tipo referência de inteiro.

		\param x Referência a ser empilhado na pilha.
	*/
	void push(int*);

	/*! \fn void push(typedElement te)
		\brief Função que empilha um elemento tipado, chamando a função adequada.

		\param x Elemento tipado a ser empilhado na pilha.
	*/
	void push(typedElement);

	/*! \fn void push(element x, uint8_t tipo)
		\brief Função checa o tipo do elemento que deve ser adicionado e chama a função adequada

		\param x Elemento tipado a ser empilhado na pilha
		\param tipo Tipo do elemento passado
	*/
	void push(element, uint8_t);

	/*! \fn int size()
		\brief Função que verifica o tamanho da pilha de operandos
	*/
	int size();

	/*! \fn int getMaxSize()
		\brief Função que retorna o tamanho máximo da pilha de operandos
	*/
	int getMaxSize();

	/*! \fn bool empty()
		\brief Função que retorna se a pilha encontra-se vazia ou não
	*/
	bool empty();

	void printALL();
	const int max;
};

#endif