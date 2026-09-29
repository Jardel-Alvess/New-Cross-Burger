#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>

using namespace std;

struct Pedido {
    int numero;
    string cliente;

    // Por enquanto vamos manter os itens como uma string.
    // Na próxima etapa podemos definir uma forma adequada
    // de armazenar vários itens sem utilizar coleções prontas.
    string itens;

    float total;

    Pedido() {
        numero = 0;
        cliente = "";
        itens = "";
        total = 0.0;
    }

    Pedido(int numero, string cliente, string itens, float total) {
        this->numero = numero;
        this->cliente = cliente;
        this->itens = itens;
        this->total = total;
    }
};

#endif