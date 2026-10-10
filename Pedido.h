#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>
#include <iostream>

using namespace std;

const int MAX_ITENS = 20;

struct Pedido {
    int numero;
    string cliente;
    string itens[MAX_ITENS];
    float precos[MAX_ITENS];
    int qtdItens;
    float desconto;   // percentual (0 a 100)
    float total;

    Pedido() {
        numero = 0;
        cliente = "";
        qtdItens = 0;
        desconto = 0.0;
        total = 0.0;
    }

    Pedido(int numero, string cliente) {
        this->numero = numero;
        this->cliente = cliente;
        qtdItens = 0;
        desconto = 0.0;
        total = 0.0;
    }

    void recalcularTotal() {
        float subtotal = 0.0;
        for (int i = 0; i < qtdItens; i++) {
            subtotal += precos[i];
        }
        total = subtotal * (1.0 - desconto / 100.0);
    }

    // Insere na posicao pos (0 a qtdItens). Retorna false se cheio ou posicao invalida.
    bool inserirItemEm(int pos, string nome, float preco) {
        if (qtdItens >= MAX_ITENS || pos < 0 || pos > qtdItens) return false;
        for (int i = qtdItens; i > pos; i--) {
            itens[i] = itens[i - 1];
            precos[i] = precos[i - 1];
        }
        itens[pos] = nome;
        precos[pos] = preco;
        qtdItens++;
        recalcularTotal();
        return true;
    }

    bool adicionarItem(string nome, float preco) {
        return inserirItemEm(qtdItens, nome, preco);
    }

    // Retorna o indice do ultimo item com esse nome, ou -1 se nao existir.
    int buscarItem(string nome) {
        for (int i = qtdItens - 1; i >= 0; i--) {
            if (itens[i] == nome) return i;
        }
        return -1;
    }

    bool removerItemEm(int pos) {
        if (pos < 0 || pos >= qtdItens) return false;
        for (int i = pos; i < qtdItens - 1; i++) {
            itens[i] = itens[i + 1];
            precos[i] = precos[i + 1];
        }
        qtdItens--;
        recalcularTotal();
        return true;
    }

    bool aplicarDesconto(float percentual) {
        if (percentual < 0 || percentual > 100) return false;
        desconto = percentual;
        recalcularTotal();
        return true;
    }

    void exibir() {
        cout << "Pedido #" << numero << " | Cliente: " << cliente << endl;
        for (int i = 0; i < qtdItens; i++) {
            cout << "  - " << itens[i] << " (R$ " << precos[i] << ")" << endl;
        }
        if (desconto > 0) cout << "  Desconto: " << desconto << "%" << endl;
        cout << "  Total: R$ " << total << endl;
    }
};

#endif