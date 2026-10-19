#ifndef NOFILA_H
#define NOFILA_H

// Importa a definição do tipo Pedido.
#include "Pedido.h"

// Define um elemento (nó) da fila de pedidos.
struct NoFila {
    // Pedido guardado neste nó.
    Pedido dado;
    // Endereço do próximo nó; nullptr indica que não há próximo elemento.
    NoFila* proximo;

    // Cria o nó com o pedido informado e o deixa sem sucessor.
    NoFila(Pedido dado) {
        this->dado = dado;
        proximo = nullptr;
    }
};

#endif