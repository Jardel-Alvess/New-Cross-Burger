#ifndef FILAPREPARO_H
#define FILAPREPARO_H

#include "NoFila.h"
#include <iostream>

using namespace std;

// Representa a fila de pedidos que estao sendo preparados.
// A fila guarda os pedidos em ordem de chegada e permite
// inserir, remover, consultar e exibir os itens na fila.
class FilaPreparo {
private:
    NoFila* inicio; // Primeiro elemento da fila.
    NoFila* fim;    // Ultimo elemento da fila.
    int tamanho;   // Quantidade de pedidos na fila.

public:
    // Inicializa a fila vazia.
    FilaPreparo() {
        inicio = nullptr;
        fim = nullptr;
        tamanho = 0;
    }

    // Libera todos os nos da fila ao destruir o objeto.
    ~FilaPreparo() {
        Pedido descartado;
        while (desenfileirar(descartado)) {}
    }

    // Evita copia acidental (dois objetos apontando para os mesmos nos)
    FilaPreparo(const FilaPreparo&) = delete;
    FilaPreparo& operator=(const FilaPreparo&) = delete;

    // Retorna true se a fila estiver vazia.
    bool estaVazia() {
        return inicio == nullptr;
    }

    // Retorna o numero de pedidos atualmente armazenados.
    int getTamanho() {
        return tamanho;
    }

    // Insere um novo pedido no final da fila.
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

    // Remove o pedido do inicio da fila e retorna o valor em saida.
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

    // Consulta o proximo pedido sem removelo da fila.
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

    // Exibe todos os pedidos da fila em ordem de atendimento.
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