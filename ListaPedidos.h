#ifndef LISTAPEDIDOS_H
#define LISTAPEDIDOS_H

#include "NoLista.h"
#include <iostream>

using namespace std;

class ListaPedidos {
private:
    NoLista* inicio;
    NoLista* fim;
    int tamanho;

public:
    ListaPedidos() {
        inicio = nullptr;
        fim = nullptr;
        tamanho = 0;
    }

    ~ListaPedidos() {
        NoLista* atual = inicio;
        while (atual != nullptr) {
            NoLista* proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
    }

    // Evita copia acidental (dois objetos apontando para os mesmos nos)
    ListaPedidos(const ListaPedidos&) = delete;
    ListaPedidos& operator=(const ListaPedidos&) = delete;

    bool estaVazia() {
        return inicio == nullptr;
    }

    int getTamanho() {
        return tamanho;
    }

    NoLista* getInicio() {
        return inicio;
    }

    NoLista* getFim() {
        return fim;
    }

    // ---------- Insercoes ----------

    void inserirNoInicio(Pedido p) {
        NoLista* novo = new NoLista(p);
        if (estaVazia()) {
            inicio = novo;
            fim = novo;
        } else {
            novo->proximo = inicio;
            inicio->anterior = novo;
            inicio = novo;
        }
        tamanho++;
    }

    void inserirNoFim(Pedido p) {
        NoLista* novo = new NoLista(p);
        if (estaVazia()) {
            inicio = novo;
            fim = novo;
        } else {
            novo->anterior = fim;
            fim->proximo = novo;
            fim = novo;
        }
        tamanho++;
    }

    // Posicao de 0 a tamanho. Retorna false se invalida.
    bool inserirEmPosicao(int pos, Pedido p) {
        if (pos < 0 || pos > tamanho) return false;
        if (pos == 0) {
            inserirNoInicio(p);
            return true;
        }
        if (pos == tamanho) {
            inserirNoFim(p);
            return true;
        }

        NoLista* atual = inicio;
        for (int i = 0; i < pos; i++) {
            atual = atual->proximo;
        }
        // atual e o no que ocupa hoje a posicao pos; o novo entra antes dele
        NoLista* novo = new NoLista(p);
        novo->anterior = atual->anterior;
        novo->proximo = atual;
        atual->anterior->proximo = novo;
        atual->anterior = novo;
        tamanho++;
        return true;
    }

    // ---------- Buscas ----------

    NoLista* buscarPorNumero(int numero) {
        NoLista* atual = inicio;
        while (atual != nullptr) {
            if (atual->dado.numero == numero) return atual;
            atual = atual->proximo;
        }
        return nullptr;
    }

    // Primeiro pedido do cliente (a partir do inicio da lista)
    NoLista* buscarPorCliente(string cliente) {
        return buscarProximoPorCliente(inicio, cliente);
    }

    // Procura a partir do no "de" (inclusive). Para continuar uma busca:
    // buscarProximoPorCliente(achado->proximo, cliente)
    NoLista* buscarProximoPorCliente(NoLista* de, string cliente) {
        NoLista* atual = de;
        while (atual != nullptr) {
            if (atual->dado.cliente == cliente) return atual;
            atual = atual->proximo;
        }
        return nullptr;
    }

    // ---------- Remocao ----------

    // Remove o pedido com esse numero (inicio, meio ou fim). Retorna false se nao existir.
    bool removerPorNumero(int numero) {
        NoLista* alvo = buscarPorNumero(numero);
        if (alvo == nullptr) return false;

        if (alvo->anterior != nullptr) {
            alvo->anterior->proximo = alvo->proximo;
        } else {
            inicio = alvo->proximo;   // alvo era o primeiro
        }

        if (alvo->proximo != nullptr) {
            alvo->proximo->anterior = alvo->anterior;
        } else {
            fim = alvo->anterior;     // alvo era o ultimo
        }

        delete alvo;
        tamanho--;
        return true;
    }

    // ---------- Percursos ----------

    void percorrerParaFrente() {
        if (estaVazia()) {
            cout << "Historico vazio." << endl;
            return;
        }
        NoLista* atual = inicio;
        while (atual != nullptr) {
            atual->dado.exibir();
            cout << "-----" << endl;
            atual = atual->proximo;
        }
    }

    void percorrerParaTras() {
        if (estaVazia()) {
            cout << "Historico vazio." << endl;
            return;
        }
        NoLista* atual = fim;
        while (atual != nullptr) {
            atual->dado.exibir();
            cout << "-----" << endl;
            atual = atual->anterior;
        }
    }

    // ---------- Relatorio (RF11) ----------

    float calcularTotalVendido() {
        float soma = 0.0;
        NoLista* atual = inicio;
        while (atual != nullptr) {
            soma += atual->dado.total;
            atual = atual->proximo;
        }
        return soma;
    }
};

#endif