#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include "Pedido.h"
#include "Acao.h"
#include "ListaPedidos.h"
#include "FilaPreparo.h"
#include "PilhaAcoes.h"
#include "PilhaRetirada.h"

using namespace std;

class Sistema {
private:
    ListaPedidos historico;
    FilaPreparo filaPreparo;
    PilhaAcoes pilhaDesfazer;
    PilhaRetirada pilhaRetirada;

    Pedido pedidoAtual;
    bool emConstrucao;

    Pedido emPreparo;
    bool cozinhando;

    NoLista* cursor;
    int proximoNumero;

public:
    Sistema() {
        emConstrucao = false;
        cozinhando = false;
        cursor = nullptr;
        proximoNumero = 1;
    }

    bool temPedidoEmConstrucao() {
        return emConstrucao;
    }

    // ---------- RF01 ----------
    bool novoPedido(string cliente) {
        if (emConstrucao) {
            cout << "Ja existe um pedido em construcao. Feche ou descarte antes." << endl;
            return false;
        }
        if (cliente == "") {
            cout << "O nome do cliente nao pode ser vazio." << endl;
            return false;
        }
        pedidoAtual = Pedido(proximoNumero++, cliente);
        pilhaDesfazer.limpar();
        emConstrucao = true;
        cout << "Pedido #" << pedidoAtual.numero << " criado para " << cliente << "." << endl;
        return true;
    }

    void exibirPedidoAtual() {
        if (!emConstrucao) {
            cout << "Nenhum pedido em construcao." << endl;
            return;
        }
        pedidoAtual.exibir();
    }

    // ---------- RF02 ----------
    bool adicionarItem(string nome, float preco) {
        if (!emConstrucao) {
            cout << "Nenhum pedido em construcao." << endl;
            return false;
        }
        if (nome == "" || preco < 0) {
            cout << "Item ou preco invalido." << endl;
            return false;
        }
        int pos = pedidoAtual.qtdItens;
        if (!pedidoAtual.adicionarItem(nome, preco)) {
            cout << "Pedido cheio (maximo de " << MAX_ITENS << " itens)." << endl;
            return false;
        }
        pilhaDesfazer.empilhar(Acao("ADICIONAR", nome, preco, pos, 0.0,
                                    "Adicionou " + nome));
        cout << "Item adicionado." << endl;
        return true;
    }

    bool removerItem(string nome) {
        if (!emConstrucao) {
            cout << "Nenhum pedido em construcao." << endl;
            return false;
        }
        int pos = pedidoAtual.buscarItem(nome);
        if (pos == -1) {
            cout << "Item nao encontrado no pedido." << endl;
            return false;
        }
        float preco = pedidoAtual.precos[pos];
        pedidoAtual.removerItemEm(pos);
        pilhaDesfazer.empilhar(Acao("REMOVER", nome, preco, pos, 0.0,
                                    "Removeu " + nome));
        cout << "Item removido." << endl;
        return true;
    }

    bool aplicarDesconto(float percentual) {
        if (!emConstrucao) {
            cout << "Nenhum pedido em construcao." << endl;
            return false;
        }
        float anterior = pedidoAtual.desconto;
        if (!pedidoAtual.aplicarDesconto(percentual)) {
            cout << "Desconto invalido (use de 0 a 100)." << endl;
            return false;
        }
        pilhaDesfazer.empilhar(Acao("DESCONTO", "", 0.0, -1, anterior,
                                    "Aplicou desconto"));
        cout << "Desconto aplicado." << endl;
        return true;
    }

    // ---------- RF03 ----------
    bool desfazer() {
        if (!emConstrucao) {
            cout << "Nenhum pedido em construcao." << endl;
            return false;
        }
        Acao a;
        if (!pilhaDesfazer.desempilhar(a)) {
            cout << "Nada para desfazer." << endl;
            return false;
        }
        if (a.tipo == "ADICIONAR") {
            pedidoAtual.removerItemEm(a.posicao);
        } else if (a.tipo == "REMOVER") {
            pedidoAtual.inserirItemEm(a.posicao, a.nomeItem, a.preco);
        } else if (a.tipo == "DESCONTO") {
            pedidoAtual.aplicarDesconto(a.descontoAnterior);
        }
        cout << "Desfeito: " << a.descricao << endl;
        return true;
    }

    // ---------- RF04 ----------
    bool fecharPedido() {
        if (!emConstrucao) {
            cout << "Nenhum pedido em construcao." << endl;
            return false;
        }
        if (pedidoAtual.qtdItens == 0) {
            cout << "Nao e possivel fechar um pedido sem itens." << endl;
            return false;
        }
        filaPreparo.enfileirar(pedidoAtual);
        historico.inserirNoFim(pedidoAtual);
        pilhaDesfazer.limpar();
        emConstrucao = false;
        cout << "Pedido #" << pedidoAtual.numero << " fechado e enviado para a cozinha." << endl;
        return true;
    }

    bool descartarPedidoAtual() {
        if (!emConstrucao) {
            cout << "Nenhum pedido em construcao." << endl;
            return false;
        }
        pilhaDesfazer.limpar();
        emConstrucao = false;
        cout << "Pedido descartado." << endl;
        return true;
    }

    // ---------- RF05 ----------
    bool chamarCozinha() {
        if (cozinhando) {
            cout << "A cozinha ainda esta preparando o pedido #" << emPreparo.numero
                 << ". Marque como pronto primeiro." << endl;
            return false;
        }
        if (!filaPreparo.desenfileirar(emPreparo)) {
            cout << "Fila de preparo vazia." << endl;
            return false;
        }
        cozinhando = true;
        cout << "Cozinha iniciou o pedido #" << emPreparo.numero << "." << endl;
        return true;
    }

    // ---------- RF06 ----------
    bool marcarPronto() {
        if (!cozinhando) {
            cout << "Nenhum pedido em preparo. Chame a cozinha primeiro." << endl;
            return false;
        }
        pilhaRetirada.empilhar(emPreparo);
        cozinhando = false;
        cout << "Pedido #" << emPreparo.numero << " pronto e colocado na bancada." << endl;
        return true;
    }

    // ---------- RF07 ----------
    bool retirarPedido() {
        Pedido p;
        if (!pilhaRetirada.desempilhar(p)) {
            cout << "Bancada vazia." << endl;
            return false;
        }
        cout << "Pedido retirado:" << endl;
        p.exibir();
        return true;
    }

    void exibirFila() {
        if (cozinhando) {
            cout << "Em preparo: Pedido #" << emPreparo.numero
                 << " - " << emPreparo.cliente << endl;
        }
        filaPreparo.exibir();
    }

    void exibirBancada() {
        pilhaRetirada.exibir();
    }

    void verProximoDaFila() {
        Pedido p;
        if (!filaPreparo.peek(p)) {
            cout << "Fila de preparo vazia." << endl;
            return;
        }
        cout << "Proximo a ser preparado:" << endl;
        p.exibir();
    }

    void verTopoBancada() {
        Pedido p;
        if (!pilhaRetirada.peek(p)) {
            cout << "Bancada vazia." << endl;
            return;
        }
        cout << "Proximo a ser retirado (topo):" << endl;
        p.exibir();
    }

    // ---------- RF08 ----------
    bool iniciarConsulta() {
        if (historico.estaVazia()) {
            cout << "Historico vazio." << endl;
            return false;
        }
        cursor = historico.getInicio();
        cursor->dado.exibir();
        return true;
    }

    bool proximoPedido() {
        if (historico.estaVazia()) {
            cout << "Historico vazio." << endl;
            return false;
        }
        if (cursor == nullptr) return iniciarConsulta();
        if (cursor->proximo == nullptr) {
            cout << "Voce ja esta no ultimo pedido." << endl;
            return false;
        }
        cursor = cursor->proximo;
        cursor->dado.exibir();
        return true;
    }

    bool pedidoAnterior() {
        if (historico.estaVazia()) {
            cout << "Historico vazio." << endl;
            return false;
        }
        if (cursor == nullptr) return iniciarConsulta();
        if (cursor->anterior == nullptr) {
            cout << "Voce ja esta no primeiro pedido." << endl;
            return false;
        }
        cursor = cursor->anterior;
        cursor->dado.exibir();
        return true;
    }

    void historicoDeTrasParaFrente() {
        historico.percorrerParaTras();
    }

    // ---------- RF09 ----------
    bool buscarPorNumero(int numero) {
        NoLista* no = historico.buscarPorNumero(numero);
        if (no == nullptr) {
            cout << "Pedido #" << numero << " nao encontrado." << endl;
            return false;
        }
        no->dado.exibir();
        return true;
    }

    bool buscarPorCliente(string cliente) {
        NoLista* no = historico.buscarPorCliente(cliente);
        if (no == nullptr) {
            cout << "Nenhum pedido encontrado para " << cliente << "." << endl;
            return false;
        }
        while (no != nullptr) {
            no->dado.exibir();
            cout << "-----" << endl;
            no = historico.buscarProximoPorCliente(no->proximo, cliente);
        }
        return true;
    }

    // ---------- RF10 ----------
    bool cancelarPedidoHistorico(int numero) {
        NoLista* alvo = historico.buscarPorNumero(numero);
        if (alvo == nullptr) {
            cout << "Pedido #" << numero << " nao encontrado." << endl;
            return false;
        }
        // Reposiciona o cursor antes de liberar o no
        if (cursor == alvo) {
            cursor = (alvo->proximo != nullptr) ? alvo->proximo : alvo->anterior;
        }
        historico.removerPorNumero(numero);

        // Mantem as estruturas consistentes: o pedido cancelado nao pode ser preparado
        if (filaPreparo.removerPorNumero(numero)) {
            cout << "Pedido #" << numero << " tambem foi removido da fila de preparo." << endl;
        } else if (cozinhando && emPreparo.numero == numero) {
            cozinhando = false;
            cout << "Preparo do pedido #" << numero << " cancelado na cozinha." << endl;
        }

        cout << "Pedido #" << numero << " removido do historico." << endl;
        return true;
    }

    // ---------- RF11 ----------
    void relatorioDoDia() {
        cout << "===== RELATORIO DO DIA =====" << endl;
        if (historico.estaVazia()) {
            cout << "Nenhum pedido registrado." << endl;
        } else {
            historico.percorrerParaFrente();
        }
        cout << "Quantidade de pedidos: " << historico.getTamanho() << endl;
        cout << "Total vendido: R$ " << historico.calcularTotalVendido() << endl;
    }
};

#endif