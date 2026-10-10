#ifndef PILHARETIRADA_H
#define PILHARETIRADA_H

#include "NoPilha.h"
#include <iostream>

using namespace std;

class PilhaRetirada {
private:
    NoPilhaPedido* topo;
    int tamanho;

public:
    PilhaRetirada() {
        topo = nullptr;
        tamanho = 0;
    }

    ~PilhaRetirada() {
        Pedido descartado;
        while (desempilhar(descartado)) {}
    }

    PilhaRetirada(const PilhaRetirada&) = delete;
    PilhaRetirada& operator=(const PilhaRetirada&) = delete;

    bool estaVazia() {
        return topo == nullptr;
    }

    int getTamanho() {
        return tamanho;
    }

    void empilhar(Pedido p) {
        NoPilhaPedido* novo = new NoPilhaPedido(p);
        novo->proximo = topo;
        topo = novo;
        tamanho++;
    }

    bool desempilhar(Pedido &saida) {
        if (estaVazia()) return false;
        NoPilhaPedido* removido = topo;
        saida = removido->dado;
        topo = topo->proximo;
        delete removido;
        tamanho--;
        return true;
    }

    bool peek(Pedido &saida) {
        if (estaVazia()) return false;
        saida = topo->dado;
        return true;
    }

    void exibir() {
        if (estaVazia()) {
            cout << "Bancada vazia." << endl;
            return;
        }
        NoPilhaPedido* atual = topo;
        cout << "(topo)" << endl;
        while (atual != nullptr) {
            cout << "Pedido #" << atual->dado.numero
                 << " - " << atual->dado.cliente << endl;
            atual = atual->proximo;
        }
    }
};

#endif