#include "methodArea.h"

map<string, ClasseEstatica*> MethodArea::classes;
string MethodArea::path = "";
FrameStack *MethodArea::fs = nullptr;


ClasseEstatica *MethodArea::getClass(string s) {
    
    for (map<string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++) {
       if (i->first == s) {
            return i->second;
        }
    }
    return nullptr;
}

bool MethodArea::addClass(string s) {
    //checa se já foi carregada
    for (map<string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++) {
       if (i->first == s) {
            return false;
       }
    }

    Leitor *l = new Leitor(string(path+s));


    //checa se tem o .class no fim da string
    if (!l->validExtension()) {
        delete l;
        l = new Leitor(string(path+s+".class"));
    }

    //checa se ocorreu algum erro durante a leitura
    if (l->load()) {
        return false;
    }

    //adiciona no map, sem a adicao da extensao .class na string caso tenha sido necessaria
    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(pair<string, ClasseEstatica*>(s, add));

    //checa se tem um metodo <clinit> na classe para ser adicionado ao topo da pilha de frames
    if (l->hasClinit()) {
        fs->addFrame(l->getClinit(), l->getCP());
    }

    return true;
}

bool MethodArea::addClass(Leitor *l) {
    //carrega a classe em memoria caso nao tenha sido ainda
    if (l->getStatus() == -1) {
        l->load();
    }

    switch (l->getStatus()) {
        case 0:
            break;
        default:
            return false;
    }
    
    //adiciona no map, sem a adicao da extensao .class na string caso tenha sido necessaria
    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(pair<string, ClasseEstatica*>(dereferenceIndex(l->getCP(), l->getThis_class()), add));

    //checa se tem um metodo <clinit> na classe para ser adicionado ao topo da pilha de frames
    if (l->hasClinit()) {
        fs->addFrame(l->getClinit(), l->getCP());
    }

    return true;
}

void MethodArea::setFrameStack(FrameStack *newFS) {
    fs = newFS;
}