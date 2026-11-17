#ifndef NOLISTA_H
#define NOLISTA_H

// Inclui a definição da estrutura Pedido, usada como dado do nó.
#include "Pedido.h"

// Representa um nó de uma lista duplamente encadeada de pedidos.
struct NoLista {
    // Pedido armazenado neste nó.
    Pedido dado;
    // Ponteiro para o nó anterior na lista.
    NoLista* anterior;
    // Ponteiro para o próximo nó na lista.
    NoLista* proximo;

    // Inicializa o nó com um pedido e sem vizinhos associados.
    NoLista(Pedido dado) {
        this->dado = dado;
        anterior = nullptr;
        proximo = nullptr;
    }
};

#endif