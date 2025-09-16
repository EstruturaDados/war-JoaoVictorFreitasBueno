#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================== DEFINIÇÕES ==================

// Número máximo de territórios que podem ser cadastrados
#define MAX_territorioS 5
// Tamanho máximo das strings para nome e cor
#define TAM_STRING 100

// ================== ESTRUTURA ==================

// Estrutura que representa um território
struct territorio {
    char nome[TAM_STRING];  // Nome do território
    char cor[TAM_STRING];   // Cor do reinado
    int tropas;             // Quantidade de tropas
};

// ================== FUNÇÕES ==================

// Função para limpar o buffer do teclado
// Necessária para evitar que o '\n' do scanf atrapalhe o fgets
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ================== FUNÇÃO PRINCIPAL ==================
int main() {
    struct territorio Mundo[MAX_territorioS]; // Vetor para armazenar os territórios
    int totalterritorios = 0;                 // Contador de territórios cadastrados
    int opcao;                                // Opção do menu

    do {
        // ================== MENU ==================
        printf("============================================\n\n");
        printf("           MENU DA GUERRA\n");
        printf("\n============================================\n\n");

        printf("1 - Cadastrar territorio\n");
        printf("2 - Listagem de todos os territorios\n");
        printf("0 - Sair\n");
        printf("\n---------------------------------------------------\n");

        printf("Digite uma Opção e Aperte ENTER: ");
        scanf("%d", &opcao);
        limparBuffer(); // limpa o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                // ================== CASO 1: CADASTRAR ==================
                
                // Checa se já atingiu o limite de territórios
                if (totalterritorios >= MAX_territorioS) {
                    printf("\nTodos os territorios já foram preenchidos!\n");
                    printf("Aperte ENTER para continuar...");
                    getchar();
                    break;
                }

                // Loop obrigatório até preencher todos os territórios restantes
                while (totalterritorios < MAX_territorioS) {
                    // Informações de qual território está sendo cadastrado
                    printf("\n======================================\n");
                    printf("Cadastrando território %d de %d\n", totalterritorios + 1, MAX_territorioS);
                    printf("======================================\n");

                    // ================== ENTRADA DE DADOS ==================
                    printf("- Digite o nome do territorio: ");
                    fgets(Mundo[totalterritorios].nome, TAM_STRING, stdin);

                    printf("- Qual a cor do Reinado: ");
                    fgets(Mundo[totalterritorios].cor, TAM_STRING, stdin);

                    // Remover '\n' do final das strings
                    Mundo[totalterritorios].nome[strcspn(Mundo[totalterritorios].nome, "\n")] = 0;
                    Mundo[totalterritorios].cor[strcspn(Mundo[totalterritorios].cor, "\n")] = 0;

                    printf("- Digite a Quantidade de Tropas: ");
                    scanf("%d", &Mundo[totalterritorios].tropas);
                    limparBuffer(); // Limpa o buffer novamente

                    totalterritorios++; // Atualiza contador de territórios cadastrados

                    printf("\nTerritório cadastrado com sucesso!\n");
                }

                printf("\nTodos os territorios foram preenchidos!\n");
                printf("Aperte ENTER para continuar...");
                getchar();
                break;

            case 2:
                // ================== CASO 2: LISTAR ==================
                printf("=== Lista de territorios Cadastrados ===\n\n");

                if (totalterritorios == 0) {
                    printf("Nenhum territorio encontrado!\n");
                } else {
                    // Percorre o vetor e imprime cada território
                    for (int i = 0; i < totalterritorios; i++) {
                        printf("=================================\n");
                        printf("Caracteristicas do Território: %d\n", i + 1);
                        printf("Nome: %s\n", Mundo[i].nome);
                        printf("Cor do Reinado: %s\n", Mundo[i].cor);
                        printf("Quantidade de Tropas: %d\n", Mundo[i].tropas);
                    }
                    printf("=================================\n");
                }

                printf("Pressione ENTER para continuar...");
                getchar();
                break;

            case 0:
                // ================== CASO 0: SAIR ==================
                printf("Saindo do sistema...\n");
                break;

            default:
                // ================== CASO INVÁLIDO ==================
                printf("Opção Inválida! Tente Novamente.\n");
                break;
        }

    } while (opcao != 0); // Repete o menu enquanto não escolher sair

    return 0;
}