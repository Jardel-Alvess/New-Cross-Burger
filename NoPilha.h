#ifndef NOPILHA_H
#define NOPILHA_H

#include "Acao.h"
#include "Pedido.h"

// No da pilha de desfazer (guarda Acao)
struct NoPilha {
    Acao dado;
    NoPilha* proximo;

    NoPilha(Acao dado) {
        this->dado = dado;
        proximo = nullptr;
    }
};

// No da pilha de retirada (guarda Pedido)
struct NoPilhaPedido {
    Pedido dado;
    NoPilhaPedido* proximo;

    NoPilhaPedido(Pedido dado) {
        this->dado = dado;
        proximo = nullptr;
    }
};

#endif