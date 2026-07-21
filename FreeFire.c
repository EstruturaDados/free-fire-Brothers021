/*- - - - - - -  MOCHILA DE LOOT - - - VETOR VS LISTA ENCADEADA - - - - -
Objetivo: cadastrar, remover, listar e buscar itens usando uma struct.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

Item mochila[MAX_ITENS];
int totalItens = 0;
int vetorOrdenado = 0;
No *inicioLista = NULL;

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void inserirItemVetor(void) {
    Item novoItem;

    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel cadastrar mais itens.\n");
        return;
    }

    printf("\n--- Cadastro de novo item ---\n");
    printf("Nome do item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBufferEntrada();

    mochila[totalItens] = novoItem;
    totalItens++;
    vetorOrdenado = 0;

    printf("\nItem cadastrado com sucesso!\n");
}

void removerItemVetor(void) {
    char nomeRemover[30];
    int pos = -1;

    if (totalItens == 0) {
        printf("\nA mochila esta vazia. Nada para remover.\n");
        return;
    }

    printf("\nDigite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\nItem nao encontrado. Nada foi removido.\n");
        return;
    }

    for (int i = pos; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;
    vetorOrdenado = 0;
    printf("\nItem removido com sucesso!\n");
}

void listarItensVetor(void) {
    printf("\n--- Itens na mochila (%d/%d) ---\n", totalItens, MAX_ITENS);

    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %-15s Tipo: %-10s Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

int buscarItemVetor(char nomeBuscando[]) {
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscando) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarVetorPorNome(void) {
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - 1 - i; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    vetorOrdenado = 1;
    printf("\nVetor ordenado por nome!\n");
}

int buscaBinariaVetor(char nomeBuscando[]) {
    int inicio = 0;
    int fim = totalItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(mochila[meio].nome, nomeBuscando);

        if (resultado == 0) {
            return meio;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

void menuVetor(void) {
    int opcao;

    do {
        printf("\n--- MOCHILA (VETOR) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (sequencial)\n");
        printf("5 - Ordenar itens por nome\n");
        printf("6 - Buscar item (binaria)\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirItemVetor();
                listarItensVetor();
                break;
            case 2:
                removerItemVetor();
                listarItensVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4: {
                char nome[30];
                printf("Nome do item: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int pos = buscarItemVetor(nome);
                if (pos != -1) {
                    printf("Encontrado: %s | %s | %d\n",
                           mochila[pos].nome,
                           mochila[pos].tipo,
                           mochila[pos].quantidade);
                } else {
                    printf("Item nao encontrado.\n");
                }
                break;
            }
            case 5:
                ordenarVetorPorNome();
                listarItensVetor();
                break;
            case 6: {
                if (!vetorOrdenado) {
                    printf("Ordene o vetor antes!\n");
                    break;
                }

                char nome[30];
                printf("Nome do item: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int pos = buscaBinariaVetor(nome);
                if (pos != -1) {
                    printf("Encontrado: %s | %s | %d\n",
                           mochila[pos].nome,
                           mochila[pos].tipo,
                           mochila[pos].quantidade);
                } else {
                    printf("Item nao encontrado.\n");
                }
                break;
            }
            case 0:
                printf("Voltando ao menu principal.\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);
}

void inserirItemLista(void) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Sem memoria!\n");
        return;
    }

    printf("\n--- Cadastro de novo item ---\n");
    printf("Nome do item: ");
    fgets(novoNo->dados.nome, sizeof(novoNo->dados.nome), stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(novoNo->dados.tipo, sizeof(novoNo->dados.tipo), stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limparBufferEntrada();

    novoNo->proximo = inicioLista;
    inicioLista = novoNo;

    printf("Item cadastrado com sucesso!\n");
}

void removerItemLista(void) {
    char nomeRemover[30];
    No *anterior = NULL;
    No *atual = inicioLista;

    if (inicioLista == NULL) {
        printf("\nA lista esta vazia. Nada para remover.\n");
        return;
    }

    printf("\nDigite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    while (atual != NULL && strcmp(atual->dados.nome, nomeRemover) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nItem nao encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        inicioLista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("\nItem removido com sucesso!\n");
}

void listarLista(void) {
    No *atual = inicioLista;
    int pos = 1;

    printf("\n--- Itens da lista ---\n");

    if (inicioLista == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("[%d] Nome: %-15s Tipo: %-10s Quantidade: %d\n",
               pos,
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
        pos++;
    }
}

No *buscarItemLista(char nomeBuscando[]) {
    No *atual = inicioLista;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBuscando) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

void menuLista(void) {
    int opcao;

    do {
        printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirItemLista();
                listarLista();
                break;
            case 2:
                removerItemLista();
                listarLista();
                break;
            case 3:
                listarLista();
                break;
            case 4: {
                char nome[30];
                printf("Nome do item: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                No *encontrado = buscarItemLista(nome);
                if (encontrado != NULL) {
                    printf("Encontrado: %s | %s | %d\n",
                           encontrado->dados.nome,
                           encontrado->dados.tipo,
                           encontrado->dados.quantidade);
                } else {
                    printf("Item nao encontrado.\n");
                }
                break;
            }
            case 0:
                printf("Voltando ao menu principal.\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);
}

int main(void) {
    int opcao;

    do {
        printf("\n--- MOCHILA DE LOOT ---\n");
        printf("1 - Usar mochila com VETOR\n");
        printf("2 - Usar mochila com Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
