#include "frame.h"

FrameStack::FrameStack (Leitor *l) {
	frame *aux = (frame*) malloc(sizeof(frame));
	
	aux->m = l->getMain();
	aux->cp = l->getCP();
	aux->operandos = new PilhaOperandos(aux->m.attributes->info->code.max_stack);
	aux->locals = new LocalVariables(aux->m.attributes->info->code.max_locals);
	startPC(aux);

	threads.push(aux);

	//atualiza os ponteiros da pilha de operandos e vetor de variaveis
	//locais utilizados nas operacoes para o metodo corrente
	Operacoes::setFrame(threads.top());
	Operacoes::setThreads(&threads);
	Operacoes::setFrameStack(this);

	//inclui uma referencia para a pilha de frames na area de metodos
	//para ser possivel a inclusao do <clinit> quando necessario
	MethodArea::setFrameStack(this);

	//seta o nop como instrucao padrao
	opcode = 0;
}

void FrameStack::execute() {
	while (nextInstruction()) {
		//chama a funcao do vetor de funcoes
		//cout << "Opcode: " << opcode << "\tMnemonico: " << getMnemonic(opcode) << flush << endl;
		Operacoes::run(opcode);
		//threads.top()->operandos->printALL();
		//getchar();
	}
}

bool FrameStack::nextInstruction() {
	//checa se a pilha esta vazia
	if (threads.empty()) {
		return false;
	}

	//checa se nao esgotamos as operacoes do metodo corrente
	if ((threads.top()->pc - threads.top()->m.attributes->info->code.code) < threads.top()->m.attributes->info->code.code_length) {
		//pega o proximo opcode a ser executado
		opcode = *threads.top()->pc;
		//anda com pc em uma instrucao
		//caso existam argumentos, a funcao chamada os utilizara
		//e anda com pc as posicoes correspondentes
		threads.top()->pc++;
		return true;
	}

	//retira do topo caso nao tenham mais instrucoes no metodo corrente
	this->pop();

	//checa se apos o pop ainda restam elementos
	if (threads.empty()) {
		return false;
	}

	return true;
}

void FrameStack::pop() {
	if (!threads.empty()) {
		delete threads.top()->operandos;
		delete threads.top()->locals;
		threads.pop();
	}
	if (threads.empty()) {
		Operacoes::setFrame(nullptr);
		Operacoes::setThreads(nullptr);
		exit(0);
	}
	Operacoes::setFrame(threads.top());
	Operacoes::setThreads(&threads);
}

void FrameStack::startPC(frame *f) {
	//colocar o PC na posicao inicial do metodo no topo
	f->pc = f->m.attributes->info->code.code;
}

void FrameStack::addFrame(method_info m, cp_info *cp) {
	frame *aux = (frame*) malloc(sizeof(frame));

	aux->m = m;
	aux->cp = cp;
	aux->operandos = new PilhaOperandos(aux->m.attributes->info->code.max_stack);
	aux->locals = new LocalVariables(aux->m.attributes->info->code.max_locals);
	startPC(aux);
	
	//atualiza os ponteiros da pilha de operandos e vetor de variaveis
	//locais utilizados nas operacoes para o metodo corrente
	Operacoes::setFrame(aux);
	Operacoes::setThreads(&threads);
	Operacoes::setFrameStack(this);

	//inclui uma referencia para a pilha de frames na area de metodos
	//para ser possivel a inclusao do <clinit> quando necessario
	MethodArea::setFrameStack(this);
	threads.push(aux);
}

void FrameStack::addFrame(method_info *m, cp_info *cp) {
	this->addFrame(*m, cp);
}

void FrameStack::setArguments(std::vector<typedElement> param) {
	for (int i = 0, j=0; i < param.size(); i++, j++) {
		threads.top()->locals->set(j, param[i]);
		
		//testa se o i-esimo argumento ocupou dois slots
		if (threads.top()->locals->get(j).type == TYPE_LONG || threads.top()->locals->get(j).type == TYPE_DOUBLE || (threads.top()->locals->get(j).type == TYPE_REFERENCE && BITS)) {
			j++;
		}
	}
}
