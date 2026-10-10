#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>
#include "Sistema.h"

using namespace std;

string lerTexto(string mensagem) {
    cout << mensagem;
    string s;
    if (!getline(cin, s)) {
        cout << endl << "Entrada encerrada. Saindo..." << endl;
        exit(0);
    }
    return s;
}

int lerInt(string mensagem) {
    while (true) {
        string s = lerTexto(mensagem);
        try {
            size_t usados;
            int v = stoi(s, &usados);
            if (usados == s.size()) return v;
        } catch (...) {}
        cout << "Valor invalido, digite um numero inteiro." << endl;
    }
}

float lerFloat(string mensagem) {
    while (true) {
        string s = lerTexto(mensagem);
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == ',') s[i] = '.';   // aceita virgula decimal
        }
        try {
            size_t usados;
            float v = stof(s, &usados);
            if (usados == s.size() && isfinite(v)) return v;
        } catch (...) {}
        cout << "Valor invalido, digite um numero (ex.: 12.50)." << endl;
    }
}

void exibirMenu() {
    cout << endl;
    cout << "========== NEW CROSS BURGER ==========" << endl;
    cout << " PEDIDO EM CONSTRUCAO" << endl;
    cout << "  1. Novo pedido" << endl;
    cout << "  2. Adicionar item" << endl;
    cout << "  3. Remover item" << endl;
    cout << "  4. Aplicar desconto" << endl;
    cout << "  5. Desfazer ultima acao" << endl;
    cout << "  6. Ver pedido atual" << endl;
    cout << "  7. Fechar pedido" << endl;
    cout << "  8. Descartar pedido" << endl;
    cout << " COZINHA" << endl;
    cout << "  9. Chamar cozinha (proximo da fila)" << endl;
    cout << " 10. Marcar pedido como pronto" << endl;
    cout << " 11. Retirar pedido pronto" << endl;
    cout << " 12. Ver fila de preparo" << endl;
    cout << " 13. Ver bancada" << endl;
    cout << " 21. Ver proximo da fila (peek)" << endl;
    cout << " 22. Ver topo da bancada (peek)" << endl;
    cout << " HISTORICO" << endl;
    cout << " 14. Iniciar consulta (primeiro pedido)" << endl;
    cout << " 15. Proximo pedido" << endl;
    cout << " 16. Pedido anterior" << endl;
    cout << " 17. Buscar por numero" << endl;
    cout << " 18. Buscar por cliente" << endl;
    cout << " 19. Cancelar pedido do historico" << endl;
    cout << " 20. Relatorio do dia" << endl;
    cout << " 23. Historico de tras para frente" << endl;
    cout << "  0. Sair" << endl;
}

int main() {
    cout << fixed << setprecision(2);

    Sistema sistema;
    int opcao = -1;

    while (opcao != 0) {
        exibirMenu();
        opcao = lerInt("Opcao: ");
        cout << endl;

        switch (opcao) {
            case 1:  sistema.novoPedido(lerTexto("Cliente: ")); break;
            case 2: {
                string nome = lerTexto("Item: ");
                float preco = lerFloat("Preco: R$ ");
                sistema.adicionarItem(nome, preco);
                break;
            }
            case 3:  sistema.removerItem(lerTexto("Item a remover: ")); break;
            case 4:  sistema.aplicarDesconto(lerFloat("Desconto (%): ")); break;
            case 5:  sistema.desfazer(); break;
            case 6:  sistema.exibirPedidoAtual(); break;
            case 7:  sistema.fecharPedido(); break;
            case 8:  sistema.descartarPedidoAtual(); break;
            case 9:  sistema.chamarCozinha(); break;
            case 10: sistema.marcarPronto(); break;
            case 11: sistema.retirarPedido(); break;
            case 12: sistema.exibirFila(); break;
            case 13: sistema.exibirBancada(); break;
            case 14: sistema.iniciarConsulta(); break;
            case 15: sistema.proximoPedido(); break;
            case 16: sistema.pedidoAnterior(); break;
            case 17: sistema.buscarPorNumero(lerInt("Numero do pedido: ")); break;
            case 18: sistema.buscarPorCliente(lerTexto("Cliente: ")); break;
            case 19: sistema.cancelarPedidoHistorico(lerInt("Numero do pedido: ")); break;
            case 20: sistema.relatorioDoDia(); break;
            case 21: sistema.verProximoDaFila(); break;
            case 22: sistema.verTopoBancada(); break;
            case 23: sistema.historicoDeTrasParaFrente(); break;
            case 0:  cout << "Encerrando..." << endl; break;
            default: cout << "Opcao invalida." << endl;
        }
    }
    return 0;
}