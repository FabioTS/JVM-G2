all: run

clean:
	rm *.o

run: attributes.o heap.o baseTypes.o classFlags.o constantPool.o fields.o interfaces.o methods.o classeLeitor.o frame.o operacoes.o pilhaOperandos.o localVariables.o methodArea.o classe.o operacoes.o
	g++ run.cpp heap.o classe.o classeLeitor.o attributes.o baseTypes.o classFlags.o constantPool.o fields.o interfaces.o methods.o frame.o operacoes.o pilhaOperandos.o localVariables.o methodArea.o -Wall -std=c++11 -o run

heap.o: heap.h heap.cpp
	g++ heap.cpp -c -std=c++11

classe.o: classe.h classe.cpp
	g++ classe.cpp -c -std=c++11

attributes.o: attributes.h attributes.cpp
	g++ attributes.cpp -c -std=c++11

baseTypes.o: baseTypes.h baseTypes.cpp
	g++ baseTypes.cpp -c -std=c++11

classFlags.o: classFlags.h classFlags.cpp
	g++ classFlags.cpp -c -std=c++11

constantPool.o: constantPool.h constantPool.cpp
	g++ constantPool.cpp -c -std=c++11

fields.o: fields.h fields.cpp
	g++ fields.cpp -c -std=c++11

interfaces.o: interfaces.h interfaces.cpp
	g++ interfaces.cpp -c -std=c++11

methods.o: methods.h methods.cpp
	g++ methods.cpp -c -std=c++11

leitor.o: leitor.h leitor.cpp
	g++ leitor.cpp -c -std=c++11

classeLeitor.o: classeLeitor.h classeLeitor.cpp
	g++ classeLeitor.cpp -c -std=c++11

pilhaOperandos.o: pilhaOperandos.h pilhaOperandos.cpp
	g++ pilhaOperandos.cpp -c -std=c++11

localVariables.o: localVariables.h localVariables.cpp
	g++ localVariables.cpp -c -std=c++11

operacoes.o: operacoes.h operacoes.cpp
	g++ operacoes.cpp -c -std=c++11

frame.o: frame.h frame.cpp
	g++ frame.cpp -c -std=c++11

methodArea.o: methodArea.h methodArea.cpp
	g++ methodArea.cpp -c -std=c++11