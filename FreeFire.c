/*- - - - - - -  MOCHILA DE LOOT 1°PARTE - - - - - - - - -
° Objetivo: Cadastra, remover, listar e buscar itens usando STRUCT e um VETOR(lista sequencial). */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_ITENS 10 // const: capacidade máxima da mochila
                     // usar "#define" em vez de 10 espalahado pelo código
                     // deixa fácil mudar esse limite depois.

/* _-_-_-_-_-_ STRUCT item _-_-_-_-_-_
Uma struct agrupa vários dados relacionadosem um único "tipo".
Aqui, cada item tem nome, tipo (arma, munição, cura...) e quantidade,
Isso é melhro do que ter 3 vetores separados (nome[], tipos[], quantidade[])
Porque mantém os dados de UM item sempre juntos. 
*/            
typedef struct 
{
    char nome[30]; // nome do item, ex: "Rifle de assalto"
    char tipo[20]; // categoria, ex: "arma", "munição", "cura"
    int quantidade; // quantos desse item o jogador tem.
}; Item;

/*
_-_-_-_-_-_ VARIÁVEIS GLOBAIS DA MOCHILA _-_-_-_-_-_
mochila[]: vetor(lista sequencial) que guarda até MAX_ITENS structs Itens. 
totalitens: quantos itens estão realmente ocupados no vetor agora.

Por que globais?: Para simplificar o exemplo didático e permitir 
que todas as funções acessam a mesma mochila sem precisar passar
o vetor inteiro como parâmetro toda hora. (Em projetos futuros e maiores
devemos usar parâmetros e ponteiros).*/

Item mochila[MAX_ITENS];
int totalItens = 0;

/*
_-_-_-_-_-_ PROTÓTIPOS DAS FUNÇÕES _-_-_-_-_-_

Declarar os protótipos no topo permite que o main() (que fica
antes delas no arquivo) saiba que essas funções existem.*/
void inserirItem(void);
void removerItem(void);
void listarItens(void);
int buscarItem(char nomeBuscando[]); //retorna a POSIÇÃO do item no vetor (ou -1 se não achar)

void limparBufferEntrada(void)

         