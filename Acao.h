#ifndef ACAO_H // Proteção contra inclusões múltiplas deste cabeçalho.
#define ACAO_H  // Define o nome do cabeçalho para evitar múltiplas inclusões.

// Fornece o tipo string usado para armazenar textos.
#include <string>

// Permite escrever string sem o prefixo std::.
using namespace std;

// Representa uma ação realizada, com os dados necessários para registrá-la.
struct Acao {
    string tipo;            // "ADICIONAR", "REMOVER" ou "DESCONTO"
    string nomeItem;        // usado em ADICIONAR e REMOVER
    float preco;            // usado em ADICIONAR e REMOVER
    int posicao;            // posicao do item no array
    float descontoAnterior; // usado em DESCONTO / qual era o desconto antes da ação
    string descricao;       // texto para exibir ao usuario

    // Inicializa a ação com valores padrão, indicando que ainda não há dados.
    Acao() {
        tipo = "";
        nomeItem = "";
        preco = 0.0;
        posicao = -1;
        descontoAnterior = 0.0;
        descricao = "";
    }

    // Inicializa a ação com os valores informados pelos parâmetros.
    // o uso de "this->" é necessário para diferenciar os atributos da struct dos parâmetros do construtor.
    Acao(string tipo, string nomeItem, float preco, int posicao,
         float descontoAnterior, string descricao) {
        this->tipo = tipo;   
        this->nomeItem = nomeItem;
        this->preco = preco;
        this->posicao = posicao;
        this->descontoAnterior = descontoAnterior;
        this->descricao = descricao;
    }
};

// Encerra a proteção contra inclusões múltiplas deste cabeçalho.
#endif