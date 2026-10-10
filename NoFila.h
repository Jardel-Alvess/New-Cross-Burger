#ifndef NOFILA_H
#define NOFILA_H

#include "Pedido.h"

struct NoFila {
    Pedido dado;
    NoFila* proximo;

    NoFila(Pedido dado) {
        this->dado = dado;
        proximo = nullptr;
    }
};

#endif