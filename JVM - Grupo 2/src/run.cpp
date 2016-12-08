/* leitor.cpp
Autores (Authors): Caio Batista
Data de Criação (Date Created): 09/11/16 (November 9th, 2016)
Data da Última Modificação (Date Last Modified): 09/11/16 (November 9th, 2016)
Descrição: Um leitor de arquivos .class.
Description: A .class files loader.*/

//#include "leitor.h"
#include "classeLeitor.h"
#include "frame.h"
#include "methodArea.h"

int main (int argc, char *argv[]) {
	//checa se foi passado o arquivo a ser analisado
	if (argc != 3) {
		cerr << "ERRO: devem ser passados 2 argumentos pela linha de comando!" << endl;
		cerr << "Formato de execucao: [programa] [modo (E/I)] [arquivo.class]" << endl;
		return MISSING_ARGUMENT;
	}

	//checa qual o modo selecionado pelo usuario
	if (argv[1][0] == 'e' || argv[1][0] == 'E') {
		
		Leitor l(argv[2]);
		l.run();
	  
	} else if (argv[1][0] == 'i' || argv[1][0] == 'I') {

		cout << "Modo Interpretador:" << endl << endl;
		Leitor *l = new Leitor(argv[2]);
		l->load();

		//aborta a execucao caso nao encontre um método para comecar ou algum erro durante a leitura
		if (!l->hasMain()) {
			cerr << "ERRO: Nao foi encontrado um metodo main.\n";
			return MISSING_MAIN;
		} else if (l->getStatus()) {
			return l->getStatus();
		}

		//adiciona a classe lida a area de metodos
		MethodArea::path = string(l->getPath());
		MethodArea::addClass(l);

		//interpretar as informacoes comecando a executar as operacoes nos frames
		FrameStack frames(l);
	  	frames.execute();
	} else {
		cerr << "ERRO: Modo indefinido! Deve ser escolhido modo exibidor(E) ou interpretador(I).\nFormato de execucao: [programa] [modo (E/I)] [arquivo.class]\n";
	}

	return 0;

}