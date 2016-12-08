/*! \file frame.h
	\brief Método 

	Contém todas as informações necessárias para a execução de um método.
*/

/*! \def FRAME 
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/
#ifndef FRAME
#define FRAME

class FrameStack;

#include "classeLeitor.h"
#include "pilhaOperandos.h"
#include "localVariables.h"
#include "baseTypes.h"
#include "operacoes.h" //tem que terminar o vetor de funcoes pra poder incluir aqui
#include "attributes.h"
#include "methodArea.h"

/*! \struct frame_s
	\brief Estrutura de armazenamento

	Estrutura responsável que contém todas as informações para que seja possível a execução de um método.
*/	
typedef struct frame_s {
	unsigned char *pc;
	cp_info *cp;	
	PilhaOperandos *operandos;
	LocalVariables *locals;
	method_info m;
} frame;


/*! \class FrameStack
	\brief Classe da pilha de Frames

	Responsável por todas as operações de pilha que envolvam o frame.
*/	
class FrameStack {
private:
	std::stack<frame*> threads;
	/*! \fn bool nextInstruction()
		\brief Incrementa PC, se não puder incrementar mais, desempilha o método corrente

	*/
	bool nextInstruction();
	/*! \var int opcode
		\brief Contêm o opcode que corresponde a uma instrução.
	*/
	int opcode;

	/*! \fn void startPC(frame *f)
		\brief Coloca o PC em sua posição inicial

		\param f Estrutura que contêm todas as informações para a execução de um método.
	*/
	void startPC(frame*);
public:
	/*! \fn FrameStack (Leitor l)
		\brief Construtor da pilha dos frames

		\param l O que foi lido do arquivo .class passados por linha de comando
	*/
	FrameStack (Leitor*);

	/*! \fn void setArguments(std::vector<typedElement> param);
		\brief Adiciona um frame no topo da pilha
		|param param Vetor com os argumentos a serem copiados no vetor de variaveis locais
	*/
	void setArguments(std::vector<typedElement>);

	/*! \fn void execute();
		\brief Executa o método corrente e os métodos chamados
	*/
	void execute();

	/*! \fn void addFrame(method_info m, cp_info *cp);
		\brief Adiciona um frame no topo da pilha
		|param m O metodo para o qual será criado o frame
		|param cp Um ponteiro para a constant pool da classe do metodo
	*/
	void addFrame(method_info, cp_info*);

	/*! \fn void addFrame(method_info m, cp_info *cp);
		\brief Adiciona um frame no topo da pilha
		|param m Ponteiro para o metodo para o qual será criado o frame
		|param cp Um ponteiro para a constant pool da classe do metodo
	*/
	void addFrame(method_info*, cp_info*);

	/*! \fn void pop()
		\brief Desempilha o método corrente.

	*/
	void pop();
};

#endif