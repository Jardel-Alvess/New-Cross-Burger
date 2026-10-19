#ifndef PILHAACOES_H
#define PILHAACOES_H

// Define a estrutura de pilha usada para armazenar acoes.
#include "NoPilha.h"
#include <iostream>

using namespace std;

// Pilha de acoes com operacoes para inserir, remover, consultar e limpar.
class PilhaAcoes {
private:
    // Ponteiro para o elemento no topo e quantidade de elementos armazenados.
    NoPilha* topo;
    int tamanho;

public:
    // Inicializa a pilha vazia.
    PilhaAcoes() {
        topo = nullptr;
        tamanho = 0;
    }

    // Libera todos os nos restantes ao destruir a pilha.
    ~PilhaAcoes() {
        limpar();
    }

    // Impede copias rasas que poderiam causar acesso invalido aos nos.
    PilhaAcoes(const PilhaAcoes&) = delete;
    PilhaAcoes& operator=(const PilhaAcoes&) = delete;

    // Informa se nao ha elementos na pilha.
    bool estaVazia() {
        return topo == nullptr;
    }

    // Retorna o numero de elementos armazenados.
    int getTamanho() {
        return tamanho;
    }

    // Adiciona uma nova acao no topo da pilha.
    // Acoes sao armazenadas em ordem inversa a que foram realizadas, para permitir desfazer.
    void empilhar(Acao a) {
        NoPilha* novo = new NoPilha(a);
        novo->proximo = topo;
        topo = novo;
        tamanho++;
    }

    // Remove a acao do topo e a copia para saida; retorna false se vazia.
    // A acao removida deve ser processada pelo programa para desfazer a operacao correspondente.
    bool desempilhar(Acao &saida) {
        if (estaVazia()) return false;
        NoPilha* removido = topo;
        saida = removido->dado;
        topo = topo->proximo;
        delete removido;
        tamanho--;
        return true;
    }

    // Copia a acao do topo para saida sem remove-la; retorna false se vazia.
    // Será util para exibir a acao que sera desfeita, sem alterar a pilha.
    bool peek(Acao &saida) {
        if (estaVazia()) return false;
        saida = topo->dado;
        return true;
    }

    // Util ao iniciar ou fechar um pedido (o historico de desfazer deixa de valer)
    // Remove todos os elementos da pilha.
    void limpar() {
        Acao descartada;
        while (desempilhar(descartada)) {}
    }
};

#endif