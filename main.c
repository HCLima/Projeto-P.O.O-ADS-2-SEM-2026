#include "jogo.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Jogo *jogos[MAX_JOGOS];
    int opcao;

    inicializarVetor(jogos, MAX_JOGOS);
    carregarDados(jogos, MAX_JOGOS);

    do {
        printf("\n=================================\n");
        printf(" Catalogo de Jogos Digitais\n");
        printf("=================================\n");
        printf("1. Cadastrar jogo\n");
        printf("2. Listar todos os jogos\n");
        printf("3. Buscar jogo por codigo\n");
        printf("4. Relatorio estatistico\n");
        printf("5. Salvar e sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            printf("Opcao invalida.\n");
            opcao = 0;
        } else {
            limparBufferEntrada();
        }

        switch (opcao) {
            case 1:
                cadastrarJogo(jogos, MAX_JOGOS);
                break;

            case 2:
                listarJogos(jogos, MAX_JOGOS);
                break;

            case 3: {
                int codigo;
                Jogo *jogo;

                printf("\nInforme o codigo do jogo: ");
                if (scanf("%d", &codigo) != 1) {
                    limparBufferEntrada();
                    printf("Codigo invalido.\n");
                    break;
                }
                limparBufferEntrada();

                jogo = buscarJogo(jogos, MAX_JOGOS, codigo);
                if (jogo == NULL) {
                    printf("Jogo nao encontrado.\n");
                } else {
                    printf("\n=== Dados do jogo ===\n");
                    printf("Codigo: %d\n", jogo->codigo);
                    printf("Titulo: %s\n", jogo->titulo);
                    printf("Desenvolvedora: %s\n", jogo->desenvolvedora);
                    printf("Preco: R$ %.2f\n", jogo->preco);
                    printf("Horas jogadas: %.1f\n", jogo->horas_jogadas);
                }
                break;
            }

            case 4:
                mostrarRelatorio(jogos, MAX_JOGOS);
                break;

            case 5:
                if (!salvarDados(jogos, MAX_JOGOS)) {
                    printf("Os dados nao puderam ser salvos.\n");
                }
                liberarDados(jogos, MAX_JOGOS);
                printf("Encerrando o programa...\n");
                break;

            default:
                if (opcao != 0) {
                    printf("Opcao inexistente. Tente novamente.\n");
                }
                break;
        }
    } while (opcao != 5);

    return 0;
}
