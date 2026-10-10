# New Cross Burger

Projeto da disciplina de Estrutura de Dados Lineares (EDL - TADS4M), IFRN Campus Nova Cruz.

Sistema de gerenciamento de pedidos em linha de comando, com estruturas encadeadas implementadas manualmente (sem colecoes prontas da linguagem).

## Estruturas utilizadas

| Estrutura | Arquivo | Uso |
|---|---|---|
| Lista duplamente encadeada | `ListaPedidos.h` | Historico de pedidos do dia |
| Fila encadeada simples | `FilaPreparo.h` | Fila de preparo da cozinha (FIFO) |
| Pilha encadeada simples | `PilhaAcoes.h` | Pilha de desfazer (undo) |
| Pilha encadeada simples | `PilhaRetirada.h` | Pedidos prontos na bancada (LIFO) |

Os nos ficam em `NoLista.h`, `NoFila.h` e `NoPilha.h`. A logica dos requisitos (RF01 a RF11) fica em `Sistema.h` e o menu em `main.cpp`.

## Como compilar e executar

```bash
g++ -std=c++11 main.cpp -o newcross
./newcross
```

## Decisoes de projeto

- Numero do pedido gerado automaticamente (1, 2, 3...), garantindo unicidade.
- Itens do pedido em array fixo (maximo de 20 itens por pedido).
- Desconto em percentual; o total e sempre recalculado a partir dos itens.
- Um pedido em construcao por vez; so e possivel fechar pedido com ao menos 1 item.
- Cancelar um pedido do historico tambem o remove da fila de preparo ou cancela o preparo em andamento. Pedido ja na bancada permanece nela, para nao quebrar a regra LIFO da pilha.