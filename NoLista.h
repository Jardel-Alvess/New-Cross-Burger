#ifndef NOLISTA_H
#define NOLISTA_H

#include "Pedido.h"

struct NoLista {
    Pedido dado;
    NoLista* anterior;
    NoLista* proximo;

    NoLista(Pedido dado) {
        this->dado = dado;
        anterior = nullptr;
        proximo = nullptr;
    }
};

#endif