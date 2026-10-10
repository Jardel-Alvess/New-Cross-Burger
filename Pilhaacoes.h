#ifndef PILHAACOES_H
#define PILHAACOES_H

#include "NoPilha.h"
#include <iostream>

using namespace std;

class PilhaAcoes {
private:
    NoPilha* topo;
    int tamanho;

public:
    PilhaAcoes() {
        topo = nullptr;
        tamanho = 0;
    }

    ~PilhaAcoes() {
        limpar();
    }

    PilhaAcoes(const PilhaAcoes&) = delete;
    PilhaAcoes& operator=(const PilhaAcoes&) = delete;

    bool estaVazia() {
        return topo == nullptr;
    }

    int getTamanho() {
        return tamanho;
    }

    void empilhar(Acao a) {
        NoPilha* novo = new NoPilha(a);
        novo->proximo = topo;
        topo = novo;
        tamanho++;
    }

    bool desempilhar(Acao &saida) {
        if (estaVazia()) return false;
        NoPilha* removido = topo;
        saida = removido->dado;
        topo = topo->proximo;
        delete removido;
        tamanho--;
        return true;
    }

    bool peek(Acao &saida) {
        if (estaVazia()) return false;
        saida = topo->dado;
        return true;
    }

    // Util ao iniciar ou fechar um pedido (o historico de desfazer deixa de valer)
    void limpar() {
        Acao descartada;
        while (desempilhar(descartada)) {}
    }
};

#endif