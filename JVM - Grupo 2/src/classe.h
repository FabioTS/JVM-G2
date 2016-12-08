/*! \file classe.h
	\brief Arquivo que define as Classes

	Definir as classes estaticas e classes instancias que serão utilizadas pela área de métodos .
*/

/*! \def CLASSE_CLASSE
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/


#ifndef CLASSE_CLASSE
#define CLASSE_CLASSE

class ClasseEstatica;
class ClasseInstancia;

#include "classeLeitor.h"
#include "heap.h"
#include <map>

using namespace std;

/*! \class ClasseEstatica
	\brief Contém fields estáticos que são compartilhados por todas as instâncias.

	Responsável por todas as operações que gerenciam as classes estáticas.
*/	
class ClasseEstatica {
private:
	map<string, typedElement*> staticFields;
	Leitor *classe;
public:
	/*! \fn ClasseEstatica(Leitor* classeLida)
		\brief Construtor da ClasseEstatica.

		\param classeLida Informações do .class já carregadas em memória.
	*/
	ClasseEstatica(Leitor*);
	/*! \fn typedElement getField(string s)
		\brief Retorna um field estático de uma classe.

		\param s Nome da classe.
	*/
	typedElement getField(string);
	/*! \fn bool setField(string s, typedElement e)
		\brief Define um field estático.

		\param s Nome da classe.
		\param e Valor que você quer que seja definido.
	*/
	bool setField(string, typedElement);
	/*! \fn bool setFinals(string s, typedElement e)
		\brief Possibilita definir campos marcados como final durante a execução de construtores.

		\param s Nome da classe.
		\param e Valor que você quer que seja definido.
	*/
	bool setFinals(string, typedElement);
	/*! \fn ClasseInstancia *getInstance()
		\brief Retorna uma instância de uma classe.
	*/
	ClasseInstancia *getInstance();
	/*! \fn Leitor *getDef()
		\brief Retorna as informações do .class.
	*/
	Leitor *getDef();
};

/*! \class ClasseInstancia
	\brief Instanciação da classe.

	Responsável por todas as operações que gerenciam as classes instancia.
*/	
class ClasseInstancia {
private:
	map<string, typedElement*> localFields;
	ClasseEstatica *classe;
public:
	/*! \fn ClasseInstancia(ClasseEstatica* c)
		\brief Construtor da classe Instancia

		\param c Referência para a classe estática.
	*/

	ClasseInstancia(ClasseEstatica*);
	/*! \fn ClasseEstatica *getStatic()
		\brief Retorna a referência da classe estática.
	*/

	ClasseEstatica *getStatic();
	/*! \fn typedElement getField(string s)
		\brief Retorna um field instanciado.

		\param s Nome da classe.
	*/
	typedElement getField(string);
	/*! \fn bool setField(string s, typedElement e)
		\brief Define um field de uma classe instanciada.

		\param s Nome da classe.
		\param e Valor que deseja-se que seja definido.
	*/
	bool setField(string, typedElement);
	/*! \fn bool setFinals(string s, typedElement e)
		\brief Possibilita definir campos marcados como final durante a execução de construtores.

		\param s Nome da classe.
		\param e Valor que deseja-se que seja definido.
	*/
	bool setFinals(string, typedElement);
	/*! \fn void show()
		\brief Mostra todas as classes instanciadas.
	*/
	void show();
};

#endif