/*! \file methodArea.h
	\brief Área de Métodos

	Ela gerencia a leitura e instanciação de classes
*/

/*! \def METHOD_AREA
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/

#ifndef METHOD_AREA
#define METHOD_AREA

class MethodArea;

#include "classeLeitor.h"
#include "baseTypes.h"
#include "constantPool.h"
#include "frame.h"
#include "classe.h"
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;
/*! \class MethodArea
	\brief Classe da área de métodos

	Responsável por todas as operações que gerenciam os métodos.
*/	
class MethodArea {
private:
	static map<string, ClasseEstatica*> classes;
	static FrameStack *fs;
public:
	static string path;
	/*! \fn static ClasseEstatica *getClass(string s)
		\brief Retorna a referência pra classe estática.

		\param s Nome da classe.
	*/
	static ClasseEstatica *getClass(string);
	/*! \fn static bool addClass(string s)
		\brief Carrega em memória uma classe.

		\param s Nome da classe.
	*/
    static bool addClass(string);
    /*! \fn bool addClass(Leitor* l)
		\brief Carrega em memória uma classe.

		\param l Informações do .class em memória.
	*/
    static bool addClass(Leitor*);
    /*! \fn static void setFrameStack(FrameStack* newFS)
		\brief Atualiza a referência do framestack para o framestack corrente.

		\param newFS Framestack corrente.
	*/
    static void setFrameStack(FrameStack*);
};

#endif