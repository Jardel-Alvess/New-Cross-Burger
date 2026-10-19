#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>
#include <iostream>

using namespace std;

// Quantidade maxima de itens que um pedido pode armazenar.
const int MAX_ITENS = 20;

// Representa um pedido de um cliente e os itens comprados.
struct Pedido {
    // Identificacao do pedido e nome do cliente.
    int numero;
    string cliente;
    // Nomes e precos dos itens ficam associados pelo mesmo indice.
    string itens[MAX_ITENS];
    float precos[MAX_ITENS];
    // Quantidade de itens e valores usados no calculo do pedido.
    int qtdItens;
    float desconto;   // percentual (0 a 100)
    float total;

    // Inicializa um pedido vazio com valores padrao.
    Pedido() {
        numero = 0;
        cliente = "";
        qtdItens = 0;
        desconto = 0.0;
        total = 0.0;
    }

    // Inicializa um pedido vazio com numero e cliente informados.
    Pedido(int numero, string cliente) {
        this->numero = numero;
        this->cliente = cliente;
        qtdItens = 0;
        desconto = 0.0;
        total = 0.0;
    }

    // Soma os precos dos itens e aplica o desconto ao subtotal.
    //recalcula sempre que um item for adicionado, removido ou o desconto for alterado.
    void recalcularTotal() {
        float subtotal = 0.0;
        for (int i = 0; i < qtdItens; i++) {
            subtotal += precos[i];
        }
        total = subtotal * (1.0 - desconto / 100.0);
    }

    // Insere na posicao pos (0 a qtdItens), deslocando os itens seguintes.
    // Retorna false se o pedido estiver cheio ou a posicao for invalida.
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

    // Adiciona um item ao final do pedido.
    bool adicionarItem(string nome, float preco) {
        return inserirItemEm(qtdItens, nome, preco);
    }

    // Busca de tras para frente e retorna o ultimo indice com esse nome,
    // ou -1 se o item nao existir.
    int buscarItem(string nome) {
        for (int i = qtdItens - 1; i >= 0; i--) {
            if (itens[i] == nome) return i;
        }
        return -1;
    }

    // Remove o item da posicao informada e desloca os seguintes.
    // retorna false se a posicao for invalida.
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

    // Define um desconto valido (de 0 a 100 por cento) e atualiza o total.
    bool aplicarDesconto(float percentual) {
        if (percentual < 0 || percentual > 100) return false;
        desconto = percentual;
        recalcularTotal();
        return true;
    }

    // Exibe os dados do pedido, seus itens, desconto e total.
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