#include "constantPool.h"

int loadConstantPool (cp_info *constantPool, int lengthCP, FILE* fp) {
	int i;
	for (i = 1; i < lengthCP; i++) {
		//carrega a tag
		constantPool[i].tag = readU1(fp);
		
		//checa se o tipo lido e conhecido
		if (!(constantPool[i].tag >= 0) && !(constantPool[i].tag <= 12) && !(constantPool[i].tag != 2))
			//caso nao seja encerra a execucao da funcao
			return i;
			
		//switch para ler os parametros do campo info de acordo com o tipo indicado pela tag lida acima
		switch (constantPool[i].tag) {
			case UTF8: //tem um campo u2 e um array de u1 como info
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
				constantPool[i].info[0].u2 = readU2(fp);
				constantPool[i].info[1].array = readUTF8(fp, constantPool[i].info[0].u2);
				break;
			case INTEGER: //tem apenas um campo u4 em info
			case FLOAT:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
				constantPool[i].info[0].u4 = readU4(fp);
				break;
			case LONG: //tem dois campos u4 em info
			case DOUBLE:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
				constantPool[i].info[0].u4 = readU4(fp);
				constantPool[++i].tag = INVALID; //indica no proximo espaco que ele deve ser ignorado
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
				constantPool[i].info[0].u4 = readU4(fp);
				break;
			case CLASS: //tem apenas um campo u2 em info
			case STRING:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
				constantPool[i].info[0].u2 = readU2(fp);
				break;
			case FIELD_REF: //tipos que tem dois campos u2 de info
			case METHOD_REF:
			case INTERFACE_REF:
			case NAME_AND_TYPE:
				constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
				constantPool[i].info[0].u2 = readU2(fp);
				constantPool[i].info[1].u2 = readU2(fp);
				break;
		}
	}
	//retorna i para indicar quantos elementos foram lidos
	return i;
}

string dereferenceIndex (cp_info *cp, U2 index) {
	switch (cp[index].tag) {
		case UTF8: //caso trivial, ja e uma string
			return showUTF8(cp[index].info[1].array, cp[index].info[0].u2);
		case CLASS: //tipos que contem somente um campo de informacao
		case STRING:
			return dereferenceIndex(cp, cp[index].info[0].u2);
		case NAME_AND_TYPE: //tipo que contem 2 campos separados por ':'
			return (dereferenceIndex(cp, cp[index].info[0].u2) + ":" + dereferenceIndex(cp, cp[index].info[1].u2));
		case METHOD_REF: //tipos que contem 2 campos separados por '.'
		case INTERFACE_REF:
		case FIELD_REF:
			return (dereferenceIndex(cp, cp[index].info[0].u2) + "." + dereferenceIndex(cp, cp[index].info[1].u2));
	}
	return "";
}

void showConstantPool (cp_info *constantPool, int lengthCP) {
	int index;
	cout << "Pool de Constantes:" << endl;
	
	for (int i = 1; i < lengthCP; i++) {	
		cout << "\t#" << i << " = ";
		cout << typeNames[constantPool[i].tag-1];
		switch (constantPool[i].tag) {
			case UTF8: //tem um campo u2 e um array de u1 como info
				cout << "\t" << showUTF8(constantPool[i].info[1].array, constantPool[i].info[0].u2);
				break;
			case INTEGER: //tem apenas um campo u4 em info
				cout << "\t" << constantPool[i].info[0].u4;
				break;
			case FLOAT: //tem apenas um campo u4 em info que deve ser convertido para float
				cout << "\t" << u4_to_float(constantPool[i].info[0]) << "f";
				break;
			case LONG: //tem dois campos u4 em info que devem ser convertidos em um long
				cout << "\t" << u4_to_long(constantPool[i].info[0], constantPool[i+1].info[0]) << "l";
				i++; //para ignorar o proximo slot
				break;
			case DOUBLE: //tem dois campos u4 em infoque devem ser convertidos em um double
				cout << "\t" << u4_to_double(constantPool[i].info[0], constantPool[i+1].info[0]) << "d";
				i++; //para ignorar o proximo slot
				break;
			case CLASS: //tem apenas um campo u2 em info
			case STRING:
				cout << " " << constantPool[i].info[0].u2 << "\t\t// " << dereferenceIndex(constantPool, i);
				break;
			case NAME_AND_TYPE: //tipo que tem dois campos u2 de info e usam o ':' para separar eles
				cout << " " << constantPool[i].info[0].u2 << ":" << constantPool[i].info[1].u2;
				cout << "\t\t// " << dereferenceIndex(constantPool, i);
				break;
			case METHOD_REF: //tipos que tem dois campos u2 de info e usam o '.' para separar eles
			case INTERFACE_REF:
			case FIELD_REF:
				cout << " " << constantPool[i].info[0].u2 << "." << constantPool[i].info[1].u2;
				cout << "\t\t// " << dereferenceIndex(constantPool, i);
				break;
		}
		cout << endl;
	}
}