// Testes automaticos das estruturas do New Cross Burger.
// Compilar: g++ -std=c++11 testes.cpp -o testes
// Executar: ./testes

#include <iostream>
#include "Pedido.h"
#include "Acao.h"
#include "ListaPedidos.h"
#include "FilaPreparo.h"
#include "PilhaAcoes.h"
#include "PilhaRetirada.h"

using namespace std;

int total = 0;
int falhas = 0;

void verificar(bool condicao, string descricao) {
    total++;
    if (condicao) {
        cout << "  [OK]   " << descricao << endl;
    } else {
        falhas++;
        cout << "  [FALHA] " << descricao << endl;
    }
}

Pedido criar(int numero, string cliente) {
    Pedido p(numero, cliente);
    p.adicionarItem("Item", 10.0);
    return p;
}

// Retorna os numeros da lista, da esquerda para a direita, numa string (ex.: "1 2 3")
string paraFrente(ListaPedidos &l) {
    string s = "";
    for (NoLista* n = l.getInicio(); n != nullptr; n = n->proximo) {
        if (s != "") s += " ";
        s += to_string(n->dado.numero);
    }
    return s;
}

string paraTras(ListaPedidos &l) {
    string s = "";
    for (NoLista* n = l.getFim(); n != nullptr; n = n->anterior) {
        if (s != "") s += " ";
        s += to_string(n->dado.numero);
    }
    return s;
}

// ---------------------------------------------------------------
void testarPedido() {
    cout << endl << "== Pedido ==" << endl;
    Pedido p(1, "Ana");
    verificar(p.total == 0, "pedido novo tem total 0");

    p.adicionarItem("X-Burger", 20.0);
    p.adicionarItem("Batata", 10.0);
    verificar(p.qtdItens == 2 && p.total == 30.0, "adicionar 2 itens: total 30");

    p.aplicarDesconto(10);
    verificar(p.total > 26.99 && p.total < 27.01, "desconto de 10% : total 27");
    verificar(!p.aplicarDesconto(101), "desconto 101% e recusado");
    verificar(!p.aplicarDesconto(-1), "desconto negativo e recusado");

    p.aplicarDesconto(0);
    verificar(p.buscarItem("Batata") == 1, "buscarItem encontra Batata na posicao 1");
    verificar(p.buscarItem("Pizza") == -1, "buscarItem retorna -1 se nao existe");

    p.removerItemEm(0);
    verificar(p.qtdItens == 1 && p.itens[0] == "Batata", "remover o primeiro desloca os demais");
    verificar(!p.removerItemEm(5), "remover posicao invalida retorna false");

    p.inserirItemEm(0, "Suco", 5.0);
    verificar(p.itens[0] == "Suco" && p.itens[1] == "Batata", "inserir no inicio desloca para a direita");

    Pedido cheio(2, "Bia");
    bool todosOk = true;
    for (int i = 0; i < MAX_ITENS; i++) {
        if (!cheio.adicionarItem("I", 1.0)) todosOk = false;
    }
    verificar(todosOk && cheio.qtdItens == MAX_ITENS, "aceita ate MAX_ITENS itens");
    verificar(!cheio.adicionarItem("Extra", 1.0), "recusa item alem do limite");
}

// ---------------------------------------------------------------
void testarLista() {
    cout << endl << "== Lista duplamente encadeada ==" << endl;
    ListaPedidos l;

    verificar(l.estaVazia() && l.getTamanho() == 0, "lista nova esta vazia");
    verificar(l.buscarPorNumero(1) == nullptr, "buscar em lista vazia retorna nullptr");
    verificar(!l.removerPorNumero(1), "remover de lista vazia retorna false");

    l.inserirNoFim(criar(2, "Bia"));
    verificar(paraFrente(l) == "2" && paraTras(l) == "2", "inserir no fim em lista vazia");

    l.inserirNoFim(criar(3, "Caio"));
    l.inserirNoInicio(criar(1, "Ana"));
    verificar(paraFrente(l) == "1 2 3", "inserir no inicio e no fim: 1 2 3");
    verificar(paraTras(l) == "3 2 1", "percorrer para tras: 3 2 1");

    verificar(l.inserirEmPosicao(2, criar(10, "Dani")), "inserir na posicao 2");
    verificar(paraFrente(l) == "1 2 10 3", "ordem apos inserir no meio: 1 2 10 3");
    verificar(paraTras(l) == "3 10 2 1", "ponteiros anterior corretos apos inserir no meio");

    verificar(l.inserirEmPosicao(0, criar(20, "Edu")) && l.getInicio()->dado.numero == 20,
              "inserirEmPosicao(0) vira o inicio");
    verificar(l.inserirEmPosicao(l.getTamanho(), criar(30, "Fa")) && l.getFim()->dado.numero == 30,
              "inserirEmPosicao(tamanho) vira o fim");
    verificar(!l.inserirEmPosicao(-1, criar(40, "X")), "posicao negativa e recusada");
    verificar(!l.inserirEmPosicao(l.getTamanho() + 1, criar(40, "X")), "posicao maior que o tamanho e recusada");
    verificar(paraFrente(l) == "20 1 2 10 3 30" && l.getTamanho() == 6, "estado: 20 1 2 10 3 30");

    verificar(l.buscarPorNumero(10) != nullptr, "buscar por numero existente");
    verificar(l.buscarPorNumero(999) == nullptr, "buscar por numero inexistente");
    verificar(l.buscarPorCliente("Dani") != nullptr, "buscar por cliente existente");
    verificar(l.buscarPorCliente("Ninguem") == nullptr, "buscar por cliente inexistente");

    // Clientes repetidos
    l.inserirNoFim(criar(31, "Ana"));
    NoLista* a1 = l.buscarPorCliente("Ana");
    NoLista* a2 = l.buscarProximoPorCliente(a1->proximo, "Ana");
    verificar(a1 != nullptr && a1->dado.numero == 1 && a2 != nullptr && a2->dado.numero == 31,
              "busca por cliente repetido encontra os dois pedidos");
    verificar(l.buscarProximoPorCliente(a2->proximo, "Ana") == nullptr, "nao ha um terceiro pedido da Ana");

    // Remocoes
    verificar(l.removerPorNumero(20), "remover o primeiro");
    verificar(paraFrente(l) == "1 2 10 3 30 31" && l.getInicio()->anterior == nullptr,
              "apos remover o primeiro: 1 2 10 3 30 31");
    verificar(l.removerPorNumero(31), "remover o ultimo");
    verificar(paraTras(l) == "30 3 10 2 1" && l.getFim()->proximo == nullptr,
              "apos remover o ultimo: tras = 30 3 10 2 1");
    verificar(l.removerPorNumero(10), "remover do meio");
    verificar(paraFrente(l) == "1 2 3 30" && paraTras(l) == "30 3 2 1",
              "apos remover do meio: frente e tras consistentes");
    verificar(!l.removerPorNumero(10), "remover de novo (inexistente) retorna false");
    verificar(l.getTamanho() == 4, "tamanho 4 apos as remocoes");

    float soma = l.calcularTotalVendido();
    verificar(soma > 39.99 && soma < 40.01, "total vendido = 4 pedidos de R$ 10 = 40");

    // Esvazia a lista
    l.removerPorNumero(1);
    l.removerPorNumero(2);
    l.removerPorNumero(3);
    l.removerPorNumero(30);
    verificar(l.estaVazia() && l.getInicio() == nullptr && l.getFim() == nullptr,
              "esvaziar a lista zera inicio e fim");
    l.inserirNoFim(criar(50, "Ze"));
    verificar(paraFrente(l) == "50", "lista reutilizavel depois de esvaziar");
}

// ---------------------------------------------------------------
void testarFila() {
    cout << endl << "== Fila encadeada (FIFO) ==" << endl;
    FilaPreparo f;
    Pedido p;

    verificar(f.estaVazia(), "fila nova esta vazia");
    verificar(!f.desenfileirar(p), "desenfileirar fila vazia retorna false");
    verificar(!f.peek(p), "peek em fila vazia retorna false");

    f.enfileirar(criar(1, "Ana"));
    f.enfileirar(criar(2, "Bia"));
    f.enfileirar(criar(3, "Caio"));
    verificar(f.getTamanho() == 3, "tamanho 3 apos enfileirar 3");

    verificar(f.peek(p) && p.numero == 1, "peek mostra o primeiro (1)");
    verificar(f.getTamanho() == 3, "peek nao remove");

    verificar(f.desenfileirar(p) && p.numero == 1, "sai o 1");
    verificar(f.desenfileirar(p) && p.numero == 2, "sai o 2");
    verificar(f.desenfileirar(p) && p.numero == 3, "sai o 3 (ordem FIFO)");
    verificar(f.estaVazia(), "fila vazia depois de desenfileirar tudo");

    f.enfileirar(criar(4, "Dani"));
    verificar(f.peek(p) && p.numero == 4, "fila reutilizavel (fim ajustado)");
    f.desenfileirar(p);

    // removerPorNumero
    f.enfileirar(criar(1, "Ana"));
    f.enfileirar(criar(2, "Bia"));
    f.enfileirar(criar(3, "Caio"));
    verificar(f.removerPorNumero(2), "remover do meio da fila");
    verificar(!f.removerPorNumero(2), "remover inexistente retorna false");
    verificar(f.removerPorNumero(3), "remover o ultimo da fila");
    f.enfileirar(criar(5, "Edu"));
    f.desenfileirar(p);
    verificar(p.numero == 1, "apos remocoes sai o 1");
    f.desenfileirar(p);
    verificar(p.numero == 5, "novo enfileirado depois de remover o ultimo entra corretamente");
    verificar(f.estaVazia(), "fila vazia no final");

    f.enfileirar(criar(7, "Fa"));
    verificar(f.removerPorNumero(7) && f.estaVazia(), "remover o unico elemento esvazia a fila");
    f.enfileirar(criar(8, "Gui"));
    verificar(f.peek(p) && p.numero == 8, "fila funciona depois de esvaziar por remocao");
}

// ---------------------------------------------------------------
void testarPilhaAcoes() {
    cout << endl << "== Pilha de acoes (desfazer) ==" << endl;
    PilhaAcoes pilha;
    Acao a;

    verificar(pilha.estaVazia(), "pilha nova esta vazia");
    verificar(!pilha.desempilhar(a), "desempilhar pilha vazia retorna false");
    verificar(!pilha.peek(a), "peek em pilha vazia retorna false");

    pilha.empilhar(Acao("ADICIONAR", "X-Burger", 20.0, 0, 0.0, "a1"));
    pilha.empilhar(Acao("REMOVER", "Batata", 10.0, 1, 0.0, "a2"));
    pilha.empilhar(Acao("DESCONTO", "", 0.0, -1, 5.0, "a3"));
    verificar(pilha.getTamanho() == 3, "tamanho 3 apos empilhar 3");

    verificar(pilha.peek(a) && a.descricao == "a3" && a.descontoAnterior == 5.0, "peek mostra o topo (a3)");
    verificar(pilha.getTamanho() == 3, "peek nao remove");

    verificar(pilha.desempilhar(a) && a.descricao == "a3", "sai a3 primeiro (LIFO)");
    verificar(pilha.desempilhar(a) && a.descricao == "a2" && a.nomeItem == "Batata", "sai a2");
    verificar(pilha.desempilhar(a) && a.descricao == "a1", "sai a1");
    verificar(pilha.estaVazia(), "pilha vazia no final");

    pilha.empilhar(Acao("ADICIONAR", "Y", 1.0, 0, 0.0, "b1"));
    pilha.empilhar(Acao("ADICIONAR", "Z", 1.0, 1, 0.0, "b2"));
    pilha.limpar();
    verificar(pilha.estaVazia() && pilha.getTamanho() == 0, "limpar esvazia a pilha");
}

// ---------------------------------------------------------------
void testarPilhaRetirada() {
    cout << endl << "== Pilha de retirada (bancada) ==" << endl;
    PilhaRetirada pilha;
    Pedido p;

    verificar(pilha.estaVazia(), "bancada nova esta vazia");
    verificar(!pilha.desempilhar(p), "desempilhar bancada vazia retorna false");
    verificar(!pilha.peek(p), "peek em bancada vazia retorna false");

    pilha.empilhar(criar(1, "Ana"));
    pilha.empilhar(criar(2, "Bia"));
    pilha.empilhar(criar(3, "Caio"));

    verificar(pilha.peek(p) && p.numero == 3, "peek mostra o topo (3)");
    verificar(pilha.desempilhar(p) && p.numero == 3, "sai o 3 primeiro (LIFO)");
    verificar(pilha.desempilhar(p) && p.numero == 2, "sai o 2");
    verificar(pilha.desempilhar(p) && p.numero == 1, "sai o 1");
    verificar(pilha.estaVazia(), "bancada vazia no final");
}

// ---------------------------------------------------------------
int main() {
    cout << "===== TESTES NEW CROSS BURGER =====" << endl;

    testarPedido();
    testarLista();
    testarFila();
    testarPilhaAcoes();
    testarPilhaRetirada();

    cout << endl << "===================================" << endl;
    cout << total - falhas << " de " << total << " testes passaram." << endl;
    if (falhas == 0) {
        cout << "Tudo certo!" << endl;
    } else {
        cout << falhas << " teste(s) falharam." << endl;
    }
    return falhas == 0 ? 0 : 1;
}