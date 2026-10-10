#ifndef ACAO_H
#define ACAO_H

#include <string>

using namespace std;

struct Acao {
    string tipo;            // "ADICIONAR", "REMOVER" ou "DESCONTO"
    string nomeItem;        // usado em ADICIONAR e REMOVER
    float preco;            // usado em ADICIONAR e REMOVER
    int posicao;            // posicao do item no array
    float descontoAnterior; // usado em DESCONTO
    string descricao;       // texto para exibir ao usuario

    Acao() {
        tipo = "";
        nomeItem = "";
        preco = 0.0;
        posicao = -1;
        descontoAnterior = 0.0;
        descricao = "";
    }

    Acao(string tipo, string nomeItem, float preco, int posicao,
         float descontoAnterior, string descricao) {
        this->tipo = tipo;
        this->nomeItem = nomeItem;
        this->preco = preco;
        this->posicao = posicao;
        this->descontoAnterior = descontoAnterior;
        this->descricao = descricao;
    }
};

#endif