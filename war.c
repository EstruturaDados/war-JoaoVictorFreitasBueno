#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 100

typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territorio;

void cadastrarTerritorio(Territorio* mapa, int qtd){
    for (int i = 0; i < qtd; i++) {
        printf("\n============================================\n");
        printf("\n     === Cadastro do Territorio %d ===\n", i + 1);
        printf("\n============================================\n\n");
        printf("Nome: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, TAM_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Tropas iniciais: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}

void exibirTerritorios(Territorio* mapa, int qtd){
    printf("\n============================================\n");
    printf("\n   === Estado Atual dos Territórios ===\n");
    printf("\n============================================\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("===========================================================\n");
        printf("|Território %d:\n|\n| Nome = %s \n| Cor = %s \n| Tropas = %d\n",
                i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        printf("===========================================================\n\n");
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0){
        printf("\n[!] Você não pode atacar Territórios da mesma cor!\n");
        return;
    }

    if (atacante->tropas < 2){
        printf("\n[!] O atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nAtaque de %s contra %s\n", atacante->nome, defensor->nome);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if(dadoAtacante > dadoDefensor) {
        printf("Resultado: O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    } else {
        printf("Resultado: O defensor resistiu!\n");
        atacante->tropas--;
    }
}

void liberarMemoria(Territorio* mapa){
    free(mapa);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    srand(time(NULL));

    int qtd, opcao;
    printf("\n\n\n============================================\n\n");
    printf("           BEM VINDO AO JOGO WAR\n");
    printf("\n============================================\n\n");
    printf("Para começar, você precisa cadastrar os territórios.\n");
    printf("Cada território deve ter um nome, uma cor de exército e uma quantidade inicial de tropas.\n");
    printf("Vamos começar!\n\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar();

    Territorio* mapa = (Territorio*)calloc(qtd, sizeof(Territorio));
    if(mapa == NULL){
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    do {
        printf("============================================\n\n");
        printf("              MENU DA GUERRA\n");
        printf("\n============================================\n\n");
        printf("1 - Cadastrar territórios\n");
        printf("2 - Listar todos os territórios\n");
        printf("3 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                cadastrarTerritorio(mapa, qtd);
                break;
            case 2:
                exibirTerritorios(mapa, qtd);
                break;
            case 3: {
                int ataque, defesa;

                exibirTerritorios(mapa, qtd);

                printf("Escolha o índice do território atacante (1-%d): ", qtd);
                scanf("%d", &ataque);
                printf("Escolha o índice do território defensor (1-%d): ", qtd);
                scanf("%d", &defesa);
                getchar();

                if(ataque >= 1 && ataque <= qtd && defesa >= 1 && defesa <= qtd && ataque != defesa){
                    atacar(&mapa[ataque - 1], &mapa[defesa - 1]);
                    exibirTerritorios(mapa, qtd);

                    // Pause para visualizar o resultado
                printf("\nPressione ENTER para continuar...");
                getchar();

                } else {
                    printf("\n[!] Índices inválidos! Tente novamente.\n");
                }
                break;
            }
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while(opcao != 0);

    liberarMemoria(mapa);
        return 0;
}