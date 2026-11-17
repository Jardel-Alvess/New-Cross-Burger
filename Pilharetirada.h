#ifndef PILHARETIRADA_H
#define PILHARETIRADA_H

// Define o tipo de nó da pilha e os dados do pedido.
#include "NoPilha.h"
// Permite exibir informações no console.
#include <iostream>

// Evita a necessidade de prefixar elementos da biblioteca padrão com std::.
using namespace std;

// Pilha de pedidos aguardando retirada, organizada pelo princípio LIFO.
class PilhaRetirada {
private:
    // Ponteiro para o nó que está no topo da pilha.
    NoPilhaPedido* topo;
    // Quantidade de pedidos armazenados na pilha.
    int tamanho;

public:
    // Inicializa uma pilha vazia.
    PilhaRetirada() {
        topo = nullptr;
        tamanho = 0;
    }

    // Remove todos os nós restantes antes de destruir a pilha.
    ~PilhaRetirada() {
        Pedido descartado;
        while (desempilhar(descartado)) {}
    }

    // Impede cópias rasas que poderiam causar uso inválido dos nós.
    PilhaRetirada(const PilhaRetirada&) = delete;
    PilhaRetirada& operator=(const PilhaRetirada&) = delete;

    // Informa se não há pedidos armazenados.
    bool estaVazia() {
        return topo == nullptr;
    }

    // Retorna a quantidade atual de pedidos.
    int getTamanho() {
        return tamanho;
    }

    // Adiciona um pedido ao topo da pilha.
    // ponteiros para pedidos são armazenados em ordem inversa à que foram recebidos, permitindo que o último pedido seja retirado primeiro.
    void empilhar(Pedido p) {
        NoPilhaPedido* novo = new NoPilhaPedido(p);
        novo->proximo = topo;
        topo = novo;
        tamanho++;
    }

    // Remove o pedido do topo e o copia para saida; retorna false se vazia.
    // O pedido removido deve ser processado pelo programa para indicar que foi retirado.
    bool desempilhar(Pedido &saida) {
        if (estaVazia()) return false;
        NoPilhaPedido* removido = topo;
        saida = removido->dado;
        topo = topo->proximo;
        delete removido;
        tamanho--;
        return true;
    }

    // Copia o pedido do topo para saida sem removê-lo.
    // funcionará para exibir o pedido que será retirado, sem alterar a pilha.
    bool peek(Pedido &saida) {
        if (estaVazia()) return false;
        saida = topo->dado;
        return true;
    }

    // Exibe os pedidos do topo até a base da pilha.
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