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

         