#ifndef FILAPREPARO_H
#define FILAPREPARO_H

#include "NoFila.h"
#include <iostream>

using namespace std;

class FilaPreparo {
private:
    NoFila* inicio;
    NoFila* fim;
    int tamanho;

public:
    FilaPreparo() {
        inicio = nullptr;
        fim = nullptr;
        tamanho = 0;
    }

    ~FilaPreparo() {
        Pedido descartado;
        while (desenfileirar(descartado)) {}
    }

    // Evita copia acidental (dois objetos apontando para os mesmos nos)
    FilaPreparo(const FilaPreparo&) = delete;
    FilaPreparo& operator=(const FilaPreparo&) = delete;

    bool estaVazia() {
        return inicio == nullptr;
    }

    int getTamanho() {
        return tamanho;
    }

    void enfileirar(Pedido p) {
        NoFila* novo = new NoFila(p);
        if (estaVazia()) {
            inicio = novo;
        } else {
            fim->proximo = novo;
        }
        fim = novo;
        tamanho++;
    }

    bool desenfileirar(Pedido &saida) {
        if (estaVazia()) return false;
        NoFila* removido = inicio;
        saida = removido->dado;
        inicio = inicio->proximo;
        if (inicio == nullptr) fim = nullptr;
        delete removido;
        tamanho--;
        return true;
    }

    bool peek(Pedido &saida) {
        if (estaVazia()) return false;
        saida = inicio->dado;
        return true;
    }

    // Remove um pedido especifico da fila (cancelamento). Retorna false se nao estiver na fila.
    bool removerPorNumero(int numero) {
        NoFila* anterior = nullptr;
        NoFila* atual = inicio;

        while (atual != nullptr && atual->dado.numero != numero) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == nullptr) return false;

        if (anterior == nullptr) {
            inicio = atual->proximo;      // era o primeiro da fila
        } else {
            anterior->proximo = atual->proximo;
        }
        if (atual == fim) {
            fim = anterior;               // era o ultimo (vira nullptr se a fila esvaziou)
        }

        delete atual;
        tamanho--;
        return true;
    }

    void exibir() {
        if (estaVazia()) {
            cout << "Fila de preparo vazia." << endl;
            return;
        }
        NoFila* atual = inicio;
        int pos = 1;
        while (atual != nullptr) {
            cout << pos++ << ". Pedido #" << atual->dado.numero
                 << " - " << atual->dado.cliente << endl;
            atual = atual->proximo;
        }
    }
};

#endif