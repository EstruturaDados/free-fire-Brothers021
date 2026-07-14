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
} Item;

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
void inserirItem();
void removerItem();
void listarItens();
int buscarItem(char nomeBuscando[]); //retorna a POSIÇÃO do item no vetor (ou -1 se não achar)

void limparBufferEntrada(void);

/*_-_-_-_-_-_FUNÇÃO PRINCIPAL (main)_-_-_-_-_-_
Aqui fica o "coração" do programa: um menu que repete(loop)
até o jogador escolher sair (opção 0)*/

int main() {
    int opcao;

    do
    { // menu orientativo: mensagens claras para o jogador saber o que fazer.
       printf("\n_-_-_ MOCHILA DE LOOT_-_-_");
       printf("1 - Cadastrar item\n");
       printf("2 - Remover item\n");
       printf("3 - Listar itens\n");
       printf("4 - Buscar item\n");
       printf("0 - Sair\n");
       printf("Escolha uma opcao: "); 

       //Lê a opção escolhida. Scanf com %d lê apenas o número inteiro.
       scanf("%d", opcao);
       limparBufferEntrada(); //essencial antes de usar o fgets() depois de scanf().

       //switch: direciona o fluxo para a função certa, conforme a escolha. 
       switch (opcao)
       {
       case 1:
            inserirItem();
            listarItens(); // requisito: listar após cada operação.
        break;
       case 2:
            removerItem();
            listarItens();
            break;
        case 3:
            listarItens();
            break;
        case 4: {
            char nomeBuscando[30];
            printf("Digite o nome do item a bsucar: ");
            fgets(nomeBuscando, sizeof(nomeBuscando), stdin);
            nomeBuscando[strcspn(nomeBuscando, "\n")] = '\0'; // remove o '\n' que "fgets" deixa
            
            int pos = buscarItem(nomeBuscando);
            if (pos != -1)
            {
                printf("\nItem encontrado!\n");
                printf("Nome: %s | Tipo; %s | Quantidade: %d\n", mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);

            } else {
                printf("\nItem \"%s\" nao encontrado na mochila.\n", nomeBuscando);
            }
            break;
       }
        case 0: 
            printf("Encerrando o sistema. Boa sorte na partida!\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente,\n");
        }

    } while (opcao != 0); // repete o menu até o jogador digitar "0"
    
    return 0;
}

/*_-_-_-_-_-_ limparBufferEntrada_-_-_-_-_-_
     _-_-uma pequena explicação para que serve_-_- 
Quando usamos "scanf(%d)" para ler um número, o ENTER que o usuário aperta fica "sobrando"
em vez de esperar o usuário digitar algo novo. Essa função "limpa" isso,
lendo e descartando os caracteres até encontrar a quebra de linha.*/

void limparBufferEntrada(void); {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
}
/*
 _-_-_-_-_-_INSERIR ITENS_-_-_-_-_-_
 cadastrar um novo item na mochila, se ainda houver espaço.*/

 void inserirItem(void) {
    //Regra: não deixe passar de MAX_ITENS (10)
    if (totalItens >= MAX_ITENS)
    {
        printf("\nMochila cheia! Nao e possivel cadastrar mais itens.\n");
        return; //sai da função imediatamente
    }
// toalItens funciona como "próxima posição livre" no vetor.
// Ex: se totalItens = 0

    Item novoItem;

    printf("\n _-_-Cadastro de novo item _-_-\n");

    printf("Nome do item: ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0'; // tira o "\n" final do fgets

    printf("Tipo do item (arma, municao, cura, ferramenta...): ");
    fgets(novoItem.tipo,sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo,"\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBufferEntrada(); // limpa o ENTER de novo, pois usamos o "scanf" aqui

//Vamos guardar o item montado na próxima posição livre do vetor.
    mochila[totalItens] = novoItem;
    totalItens++; //avança o contador: agora há mais um item ocupado

    printf("\nItem \"%s\" cadastrado com sucesso!\n", novoItem.nome);
 }
