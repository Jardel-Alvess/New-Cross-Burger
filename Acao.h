#ifndef ACAO_H
#define ACAO_H

#include <string>

using namespace std;

struct Acao {
    string tipo;
    string descricao;

    Acao() {
        tipo = "";
        descricao = "";
    }

    Acao(string tipo, string descricao) {
        this->tipo = tipo;
        this->descricao = descricao;
    }
};

#endif