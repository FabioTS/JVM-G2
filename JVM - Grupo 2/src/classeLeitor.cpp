#include "classeLeitor.h"

Leitor::Leitor(char *in) {
	if (in) {
		fileName = in;
	}
	status = -1;
}

Leitor::Leitor(std::string in) {
	if (!in.empty()) {
		fileName = new char[in.size() + 1];
		std::copy(in.begin(), in.end(), fileName);
		fileName[in.size()] = 0;
	}
	status = -1;
}

int Leitor::run() {	
	if(load() == 0) {
		show();
	}

	return this->status;
}

int Leitor::load() {
	int checkCP;

	//checa se foi passado o arquivo a ser lido e nao eh nulo
	if (!fileName) {
		cerr << getError(MISSING_ARGUMENT);
		return (status = MISSING_ARGUMENT);
	}

	//checa se o arquivo tem a extensao .class
	if (!validExtension()) {
		cerr << getError(INVALID_EXTENSION);
		return (status = INVALID_EXTENSION);
	}

	fp = fopen(fileName, "rb");

	//checa se conseguiu abrir o arquivo recebido
	if (fp == NULL) {
		cerr << getError(CANT_OPEN);
		return (status = CANT_OPEN);
	}

	//checa se a assinatura do arquivo (cafe babe) esta presente
	if (readU4(fp) != 0xcafebabe) {
		cerr << getError(INVALID_FILE);
		return (status = INVALID_FILE);
	}

	//le a minor version
	minVersion = readU2(fp);

	//le a major version
	majVersion = readU2(fp);
	
	//le o numero de constantes na CP
	lengthCP = readU2(fp);

	//carrega a CP em memoria
	constantPool = (cp_info *) malloc(sizeof(cp_info) * lengthCP);
	checkCP = loadConstantPool(constantPool, lengthCP, fp);

	//checa se todos os elementos foram lidos
	if (checkCP != lengthCP) {
		cerr << getError(UNKNOWN_TYPE);
		return (status = UNKNOWN_TYPE);
	}

	//le as flags de acesso da classe
	accessFlags = readU2(fp);

	//le a classe definida pelo arquivo
	this_class = readU2(fp);

	if (!checkThisClass()) {
		cerr << getError(INVALID_NAME);
		return (status = INVALID_NAME);
	}

	//le a superclasse do arquivo
	super_class = readU2(fp);

	//le a quantidade de interfaces presentes
	interfacesCount = readU2(fp);

	//carrega as interfaces
	interfaces = readInterfaces(fp, interfacesCount);

	//le a quantidade de campos presentes
	fieldsCount = readU2(fp);

	//carrega os campos
	fields = readFields(fp, fieldsCount,constantPool);

	//le a quantidade de metodos presentes
	methodsCount = readU2(fp);

	//carrega os metodos presentes
	methods = readMethods(fp, methodsCount,constantPool);

	//le a quantidade de atributos presentes
	attributesCount = readU2(fp);

	//carrega os atributos presentes
	attributes = readAttributes(fp, constantPool, attributesCount);

	//checa se tem um metodo main nesta classe
	foundMain = findMain();

	//checa se tem um metodo <clinit>
	foundClinit = findClinit();

	//fecha o arquivo com a leitura concluida
	fclose(fp);
	fp = NULL;

	return (status = 0);
}

bool Leitor::show() {
	//checa se o arquivo ja foi lido
	if (status != 0) {
		return false;
	}

	cout << "Versao minor: " << minVersion << endl;
	cout << "Versao major: " << majVersion << endl;

	//mostra a CP ja fazendo a dereferenciacao
	showConstantPool(constantPool, lengthCP);

	//mostra as flags setadas
	showFlags(accessFlags);

	//dereferencia o indice apontado e o mostra
	cout << "this_class: " << dereferenceIndex(constantPool, this_class) << endl;
	
	//dereferencia o indice apontado e o mostra
	cout << "super_class: " << dereferenceIndex(constantPool, super_class) << endl;	

	cout << "Numero de interfaces: " << interfacesCount << endl;

	//mostra as interfaces lidas
	showInterfaces(interfaces, constantPool, interfacesCount);

	cout << "Numero de campos: " << fieldsCount << endl;

	//mostra os campos presentes
	showFields(fields, constantPool, fieldsCount);

	cout << "Numero de metodos: " << methodsCount << endl;

	//mostra os metodos presentes
	showMethods(methods, constantPool, methodsCount);

	cout << "Numero de atributos: " << attributesCount << endl;

	//mostra os metodos presentes
	showAttributes(attributes, constantPool, attributesCount);

	return true;
}

bool Leitor::validExtension () {
	string aux = "", auxFilename(this->fileName);
	int size = auxFilename.size();

	if (size > 7) {
		for (int i = size-6; i < size; i++) {
			aux += auxFilename[i];
		}
	}

	return aux == ".class";
}

bool Leitor::findMain () {
	bool ret = false;

	for (int i = 0; i < methodsCount; i++) {
		int name = methods[i].name_index, desc = methods[i].descriptor_index, flags = methods[i].access_flags;
		
		if ("main" == dereferenceIndex(constantPool, name)) {
			if ("([Ljava/lang/String;)V" == dereferenceIndex(constantPool, desc)) {
				if ((flags & 0x09) == 0x09) {
					mainMethod = i;
					ret = true;
					break;
				}
			}
		}
	}

	return ret;
}

bool Leitor::findClinit() {
	bool ret = false;

	for (int i = 0; i < methodsCount; i++) {
		int name = methods[i].name_index, desc = methods[i].descriptor_index, flags = methods[i].access_flags;
		
		if ("<clinit>" == dereferenceIndex(constantPool, name)) {
			clinit = i;
			ret = true;
			break;
		}
	}

	return ret;
}


bool Leitor::hasMain () {
	return foundMain;
}

bool Leitor::hasClinit () {
	return foundClinit;
}

method_info Leitor::getMain() {
	if (foundMain) {
		return methods[mainMethod];
	} else {
		throw runtime_error("Nao foi encontrado um metodo main!");
	}
}

method_info Leitor::getClinit() {
	return methods[clinit];
}

bool Leitor::checkThisClass () {
	int auxPos;
	
	string auxFilename(this->fileName);
	string auxClass = dereferenceIndex(this->constantPool, this->this_class);
	//retira a extensao
	auxFilename = auxFilename.substr(0, auxFilename.size()-6);
	
	//retira os nomes das pastas no windows 
	auxPos = auxFilename.find("\\");
	while(auxPos >= 0 && auxPos <= auxFilename.size()) {
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//retira os nomes das pastas no linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && auxPos <= auxFilename.size()) {
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}
	//retira os nomes das pastas no windows 
	auxPos = auxClass.find("\\");
	while(auxPos >= 0 && auxPos <= auxClass.size()) {
		auxClass = auxClass.substr(auxPos+1);
		auxPos = auxClass.find("\\");
	}

	//retira os nomes das pastas no linux
	auxPos = auxClass.find("/");
	while(auxPos >= 0 && auxPos <= auxClass.size()) {
		auxClass = auxClass.substr(auxPos+1);
		auxPos = auxClass.find("/");
	}

	return (auxClass == auxFilename);
}

int Leitor::getStatus () {
	return status;
}

string Leitor::getError (int error) {
	string ret = "";
	switch (error) {
		case MISSING_ARGUMENT:
				ret = "ERRO: Argumento passado invalido!\n";
				break;
			case CANT_OPEN:
				ret = "ERRO: nao foi possivel abrir o arquivo \"" + string(fileName) + "\"!\n";
				break;
			case INVALID_FILE:
				ret = "ERRO: Arquivo invalido!\nAssinatura \"cafe babe\" nao encontrada.\n";
				break;
			case UNKNOWN_TYPE:
				ret = "ERRO: Tipo nao reconhecido para o pool de constantes!\nNao foi possivel carregar todo o PC.";
				break;
			case INVALID_NAME:
				ret = "ERRO: O nome da classe definida nao bate com o do arquivo!\n";
				break;
			case INVALID_EXTENSION:
				ret = "ERRO: O arquivo deve ter a extensao .class!\n";
				break;
			default:
				break;
	}
	return ret;
}

cp_info* Leitor::getCP () const {
	return constantPool;
}

U2 Leitor::getLengthCP () {
	return lengthCP;
}

char *Leitor::getPath () {
	string path= "", auxFilename(this->fileName);
	char *ret;
	int auxPos;

	//navega nas pastas no windows 
	auxPos = path.find("\\");
	while(auxPos >= 0 && auxPos <= path.size()) {
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//navega nas pastas no linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && auxPos <= auxFilename.size()) {
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	//copia o resultado para o local do retorno
	ret = (char *) malloc(sizeof(char) * (path.size() + 1));
	for (int i = 0; i < path.size(); i++) {
		ret[i] = path[i];
	}
	ret[path.size()] = '\0';

	return ret;
}

method_info *Leitor::getMethods() {
	return methods;
}

U2 Leitor::getMethodsCount() {
	return methodsCount;
}

U2 Leitor::getThis_class() {
	return this_class;
}

U2 Leitor::getSuper_class() {
	return super_class;
}

U2 Leitor::getFieldsCount() {
	return fieldsCount;
}

field_info *Leitor::getFields() {
	return fields;
}

field_info* Leitor::getField(string field_name) {

	for(int i = 0; i < getFieldsCount(); i++) {
		if(dereferenceIndex(constantPool, fields[i].name_index) == field_name )
		{
			return fields+i; 
		}
	}
	return NULL;

}

method_info* Leitor::getMethod(string name, string descriptor)
{
	method_info method;

	for(int i = 0; i < this->methodsCount; i++)
	{
		//cout << "E1" << flush << endl;
		method = this->methods[i];
		//cout << "E2" << flush << endl;
		string method_name = dereferenceIndex(this->constantPool, method.name_index);
		string method_desc = dereferenceIndex(this->constantPool, method.descriptor_index);

		if(descriptor == method_desc && name == method_name) 
		{
			//cout << "ERETURN" << flush << endl;
			return methods+i;
		}
	}

	if(getSuper_class() == 0) 
	{
		//cout << "ENULL" << flush << endl;
		return NULL;
	}
	else {

		//cout << "EREC" << flush << endl;
		//cout << "SUPERCLASS " << getSuper_class() << flush << endl;
		ClasseEstatica* a = MethodArea::getClass(dereferenceIndex(this->constantPool, getSuper_class()));
		//cout << "EREC1" << flush << endl;
		Leitor* l = a->getDef();
		//cout << "EREC2" << flush << endl;
		
		return l->getMethod(name, descriptor);
	}
}

Leitor* Leitor::getClassThatHasSerachedMethod(string name, string descriptor)
{
	method_info* method;

	for(int i = 0; i < this->methodsCount; i++)
	{
		method = (this->methods)+i;

		string method_name = dereferenceIndex(this->constantPool, method->name_index);
		string method_desc = dereferenceIndex(this->constantPool, method->descriptor_index);

		if(descriptor == method_desc && name == method_name) 
		{
			return this;
		}
	}

	if(getSuper_class() == 0) 
	{
		return NULL;
	}
	else {
		Leitor* l = MethodArea::getClass(dereferenceIndex(this->constantPool, getSuper_class()))->getDef();
		return l->getClassThatHasSerachedMethod(name, descriptor);
	}
}