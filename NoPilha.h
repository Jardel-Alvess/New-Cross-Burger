#ifndef NOPILHA_H
#define NOPILHA_H

// Inclui as definicoes de Acao e Pedido, usadas como dados dos nos.
#include "Acao.h"
#include "Pedido.h"

// No da pilha de desfazer (guarda Acao)
struct NoPilha {
    // Acao armazenada neste no.
    Acao dado;
    // Endereco do proximo no da pilha; nullptr indica o fim.
    NoPilha* proximo;

    // Cria o no com a acao informada e sem proximo elemento.
    NoPilha(Acao dado) {
        this->dado = dado;
        proximo = nullptr;
    }
};

// No da pilha de retirada (guarda Pedido)
struct NoPilhaPedido {
    // Pedido armazenado neste no.
    Pedido dado;
    // Endereco do proximo no da pilha; nullptr indica o fim.
    NoPilhaPedido* proximo;

    // Cria o no com o pedido informado e sem proximo elemento.
    NoPilhaPedido(Pedido dado) {
        this->dado = dado;
        proximo = nullptr;
    }
};

#endif