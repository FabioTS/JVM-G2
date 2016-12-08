#include "pilhaOperandos.h"

PilhaOperandos::PilhaOperandos (int maxSize) : max(2*maxSize), realMax(maxSize) {
	typePushed = false;
}

//retorna o tipo do valor que esta no topo
uint8_t PilhaOperandos::top_type() {
	return ((!this->empty()) ? (this->tipos.top()) : (-1));
}

//retorna no tipo da union element o valor que esta no topo da pilha
element PilhaOperandos::top_value() {
	element ret;

	//caso a pilha esteja vazia, retorna um elemento vazio
	if (this->empty()) {
		return ret;
	}	

	//pega o primeiro slot da pilha
	ret.i = this->elementos.top();

	//checa se e necessario juntas o segundo slot tambem 
	if (this->tipos.top() == TYPE_LONG || this->tipos.top() == TYPE_DOUBLE || (this->tipos.top() == TYPE_REFERENCE && bits64)) {
		uint32_t aux = ret.i;
		this->elementos.pop();
		ret.l = long((long(ret.i)<<32) + this->elementos.top());
		this->elementos.push(aux);
	}	

	return ret;
}

//retorna o valor que esta no topo de o desempilha
element PilhaOperandos::pop() {
	element ret;
	//caso a pilha esteja vazia, retorna um elemento vazio
	if (this->empty()) {
		return ret;
	}

	ret = this->top_value();

	//faz o pop em um slot
	this->elementos.pop();

	//checa se e necessario fazer o pop para mais um slot
	if (this->tipos.top() == TYPE_LONG || this->tipos.top() == TYPE_DOUBLE || (this->tipos.top() == TYPE_REFERENCE && bits64)) {
		this->elementos.pop();
	}

	//tira o tipo do elemento que foi desempilhado da pilha de tipos
	this->tipos.pop();
	this->tiposReais.pop();

	return ret;
}

typedElement PilhaOperandos::popTyped() {
	typedElement ret;
	ret.type = this->tipos.top();
	ret.realType = this->tiposReais.top();
	ret.value = this->pop();

	return ret;
}

std::string PilhaOperandos::getString () {
	std::stringstream ret;

	switch (this->top_type()) {
		case TYPE_INT:
			ret << "(int) " << int(this->top_value().i);
			break;
		case TYPE_LONG:
			ret << "(long) " << long(this->top_value().l);
			break;
		case TYPE_FLOAT:
			ret << "(float) " << this->top_value().f;
			break;
		case TYPE_DOUBLE:
			ret << "(double) " << this->top_value().d;
			break;
		case TYPE_BOOL:
			ret << "(bool) " << (int) this->top_value().b;
			break;
		case TYPE_REFERENCE:
			ret << "(reference) " << this->top_value().pi;
			break;
	}

	return ret.str();
}

//acrescenta um int ao topo da pilha
void PilhaOperandos::push(int x) {
	//caso ja tenha atingido o tamanho maximo, nao empilha nada
	if (this->size() == max) {
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}
	this->tipos.push(TYPE_INT);
	if (!typePushed)
		this->tiposReais.push(RT_INT);
	this->elementos.push(x);

	typePushed = false;
}

//acrescenta um float ao topo da pilha
void PilhaOperandos::push(float x) {
	//caso ja tenha atingido o tamanho maximo, nao empilha nada
	if (this->size() == max) {
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.f = x;
	this->tipos.push(TYPE_FLOAT);
	if (!typePushed)
		this->tiposReais.push(RT_FLOAT);
	this->elementos.push(aux.i);

	typePushed = false;
}

//acrescenta um long ao topo da pilha, utilizando 2 slots
void PilhaOperandos::push(long x) {
	//caso nao tenha 2 slots disponiveis, nao empilha nada
	if (this->size()+1 >= max) {
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	this->tipos.push(TYPE_LONG);
	if (!typePushed)
		this->tiposReais.push(RT_LONG);
	this->elementos.push(x);
	x >>= 32;
	this->elementos.push(x);

	typePushed = false;
}

//acrescenta um double ao topo da pilha, utilizando 2 slots
void PilhaOperandos::push(double x) {
	//caso nao tenha 2 slots disponiveis, nao empilha nada
	if (this->size()+1 >= max) {
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.d = x;
	this->tipos.push(TYPE_DOUBLE);
	if (!typePushed)
		this->tiposReais.push(RT_DOUBLE);
	this->elementos.push(aux.i);
	aux.l >>= 32;
	this->elementos.push(aux.i);

	typePushed = false;
}

//acrescenta um int ao topo da pilha
void PilhaOperandos::push(bool x) {
	//caso ja tenha atingido o tamanho maximo, nao empilha nada
	if (this->size() == max) {
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}	

	element aux;
	aux.b = x;
	this->tipos.push(TYPE_BOOL);
	if (!typePushed)
		this->tiposReais.push(RT_BOOL);
	this->elementos.push(aux.i);

	typePushed = false;
}

//acrescenta um int ao topo da pilha
void PilhaOperandos::push(int *x) {
	//caso nao tenha a quantidade necessaria de slots disponiveis, nao empilha nada
	if (this->size()+bits64 >= max) {
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}	

	element aux;
	aux.pi = x;
	this->tipos.push(TYPE_REFERENCE);
	if (!typePushed)
		this->tiposReais.push(RT_REFERENCE);	
	this->elementos.push(aux.i);
	if (bits64) {
		aux.l >>= 32;
		this->elementos.push(aux.i);
	}

	typePushed = false;
}

//recebe um elemento tipado e chama a funcao adequada para tratar o tipo
void PilhaOperandos::push(typedElement te) {
	this->tiposReais.push(te.realType);
	typePushed = true;
	this->push(te.value, te.type);
}

//checa o tipo do elemento que deve ser adicionado e chama a funcao adequada
void PilhaOperandos::push(element x, uint8_t tipo) {
	switch (tipo) {
		case TYPE_DOUBLE:
			this->push(x.d);
			break;
		case TYPE_LONG:
			this->push(long(x.l));
			break;
		case TYPE_FLOAT:
			this->push(x.f);
			break;
		case TYPE_INT:
			this->push(int(x.i));
			break;
		case TYPE_REFERENCE:
			this->push((int*)(x.pi));
			break;
		case TYPE_BOOL:
			this->push(x.b);
			break;
		default:
			break;
	}
}

//retorna o tamanho da pilha
int PilhaOperandos::size() {
	return this->elementos.size();
}

int PilhaOperandos::getMaxSize() {
	return this->realMax;
}

//retorna 1 se a pilha esta vazia e 0 caso nao esteja
bool PilhaOperandos::empty() {
	return this->elementos.empty();
}

void PilhaOperandos::printALL() {
	PilhaOperandos aux(this->max);

	while (!this->empty()) {
		cout << this->getString() << endl;
		aux.push(this->popTyped());
	}

	while (!aux.empty()) {
		this->push(aux.popTyped());
	}
}