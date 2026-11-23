#include "jogo.h"

#include <stdlib.h>
#include <string.h>

static void removerNovaLinha(char *texto) {
    size_t tamanho = strlen(texto);
    if (tamanho > 0 && texto[tamanho - 1] == '\n') {
        texto[tamanho - 1] = '\0';
    }
}

static int lerLinha(char *texto, size_t tamanho) {
    if (fgets(texto, (int)tamanho, stdin) == NULL) {
        return 0;
    }
    removerNovaLinha(texto);
    return 1;
}

void limparBufferEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

void inicializarVetor(Jogo *vetor[], int capacidade) {
    int i;
    for (i = 0; i < capacidade; i++) {
        vetor[i] = NULL;
    }
}

int localizarEspacoLivre(Jogo *vetor[], int capacidade) {
    int i;
    for (i = 0; i < capacidade; i++) {
        if (vetor[i] == NULL) {
            return i;
        }
    }
    return -1;
}

int localizarPorCodigo(Jogo *vetor[], int capacidade, int codigo) {
    int i;
    for (i = 0; i < capacidade; i++) {
        if (vetor[i] != NULL && vetor[i]->codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int cadastrarJogo(Jogo *vetor[], int capacidade) {
    Jogo novo;
    Jogo *ponteiro;
    int indice;

    printf("\nCodigo do jogo: ");
    if (scanf("%d", &novo.codigo) != 1) {
        limparBufferEntrada();
        printf("Codigo invalido.\n");
        return 0;
    }
    limparBufferEntrada();

    if (novo.codigo <= 0) {
        printf("O codigo deve ser um numero positivo.\n");
        return 0;
    }
    if (localizarPorCodigo(vetor, capacidade, novo.codigo) != -1) {
        printf("Ja existe um jogo com esse codigo.\n");
        return 0;
    }

    printf("Titulo: ");
    if (!lerLinha(novo.titulo, sizeof(novo.titulo)) || novo.titulo[0] == '\0') {
        printf("Titulo invalido.\n");
        return 0;
    }

    printf("Desenvolvedora: ");
    if (!lerLinha(novo.desenvolvedora, sizeof(novo.desenvolvedora)) ||
        novo.desenvolvedora[0] == '\0') {
        printf("Desenvolvedora invalida.\n");
        return 0;
    }

    printf("Preco: ");
    if (scanf("%lf", &novo.preco) != 1 || novo.preco < 0.0) {
        limparBufferEntrada();
        printf("Preco invalido.\n");
        return 0;
    }
    limparBufferEntrada();

    printf("Horas jogadas: ");
    if (scanf("%lf", &novo.horas_jogadas) != 1 || novo.horas_jogadas < 0.0) {
        limparBufferEntrada();
        printf("Horas jogadas invalidas.\n");
        return 0;
    }
    limparBufferEntrada();

    indice = localizarEspacoLivre(vetor, capacidade);
    if (indice == -1) {
        printf("Capacidade maxima atingida (%d jogos).\n", capacidade);
        return 0;
    }

    ponteiro = (Jogo *)malloc(sizeof(Jogo));
    if (ponteiro == NULL) {
        printf("Erro: memoria insuficiente para cadastrar o jogo.\n");
        return 0;
    }

    *ponteiro = novo;
    vetor[indice] = ponteiro;
    printf("Jogo cadastrado com sucesso!\n");
    return 1;
}

void listarJogos(Jogo *vetor[], int capacidade) {
    int i;
    int quantidade = 0;

    printf("\n=== Catalogo de Jogos ===\n");
    for (i = 0; i < capacidade; i++) {
        if (vetor[i] != NULL) {
            quantidade++;
            printf("Codigo: %d\n", vetor[i]->codigo);
            printf("Titulo: %s\n", vetor[i]->titulo);
            printf("Desenvolvedora: %s\n", vetor[i]->desenvolvedora);
            printf("Preco: R$ %.2f\n", vetor[i]->preco);
            printf("Horas jogadas: %.1f\n", vetor[i]->horas_jogadas);
            printf("-----------------------------\n");
        }
    }

    if (quantidade == 0) {
        printf("Nenhum jogo cadastrado.\n");
    }
}

Jogo *buscarJogo(Jogo *vetor[], int capacidade, int codigo) {
    int indice = localizarPorCodigo(vetor, capacidade, codigo);
    if (indice == -1) {
        return NULL;
    }
    return vetor[indice];
}

void mostrarRelatorio(Jogo *vetor[], int capacidade) {
    int i;
    int quantidade = 0;
    double soma_precos = 0.0;
    Jogo *mais_jogado = NULL;

    for (i = 0; i < capacidade; i++) {
        if (vetor[i] != NULL) {
            quantidade++;
            soma_precos += vetor[i]->preco;
            if (mais_jogado == NULL ||
                vetor[i]->horas_jogadas > mais_jogado->horas_jogadas) {
                mais_jogado = vetor[i];
            }
        }
    }

    printf("\n=== Relatorio do Catalogo ===\n");
    if (quantidade == 0) {
        printf("Nenhum jogo cadastrado para gerar estatisticas.\n");
        return;
    }

    printf("Quantidade de jogos: %d\n", quantidade);
    printf("Media de preco: R$ %.2f\n", soma_precos / quantidade);
    printf("Jogo com maior tempo jogado:\n");
    printf("Codigo: %d\n", mais_jogado->codigo);
    printf("Titulo: %s\n", mais_jogado->titulo);
    printf("Horas jogadas: %.1f\n", mais_jogado->horas_jogadas);
}

int carregarDados(Jogo *vetor[], int capacidade) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "r");
    char linha[3 * TAM_TEXTO];
    int quantidade = 0;

    if (arquivo == NULL) {
        printf("Arquivo \"%s\" nao encontrado. Iniciando catalogo vazio.\n",
               ARQUIVO_DADOS);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Jogo temporario;
        int resultado;

        resultado = sscanf(linha, "%d|%99[^|]|%99[^|]|%lf|%lf",
                           &temporario.codigo,
                           temporario.titulo,
                           temporario.desenvolvedora,
                           &temporario.preco,
                           &temporario.horas_jogadas);

        if (resultado == 5 && temporario.codigo > 0 &&
            localizarPorCodigo(vetor, capacidade, temporario.codigo) == -1) {
            int indice = localizarEspacoLivre(vetor, capacidade);
            if (indice != -1) {
                Jogo *novo = (Jogo *)malloc(sizeof(Jogo));
                if (novo == NULL) {
                    printf("Erro ao alocar memoria ao carregar os dados.\n");
                    break;
                }
                *novo = temporario;
                vetor[indice] = novo;
                quantidade++;
            } else {
                break;
            }
        }
    }

    fclose(arquivo);
    printf("Leitura concluida: %d jogo(s) carregado(s).\n", quantidade);
    return quantidade;
}

int salvarDados(Jogo *vetor[], int capacidade) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "w");
    int quantidade = 0;
    int i;

    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir \"%s\" para gravacao.\n",
               ARQUIVO_DADOS);
        return 0;
    }

    for (i = 0; i < capacidade; i++) {
        if (vetor[i] != NULL) {
            if (fprintf(arquivo, "%d|%s|%s|%.2f|%.1f\n",
                        vetor[i]->codigo,
                        vetor[i]->titulo,
                        vetor[i]->desenvolvedora,
                        vetor[i]->preco,
                        vetor[i]->horas_jogadas) < 0) {
                fclose(arquivo);
                printf("Erro ao gravar os dados no arquivo.\n");
                return 0;
            }
            quantidade++;
        }
    }

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar o arquivo de dados.\n");
        return 0;
    }

    printf("Dados salvos em \"%s\": %d registro(s).\n",
           ARQUIVO_DADOS, quantidade);
    return 1;
}

void liberarDados(Jogo *vetor[], int capacidade) {
    int i;
    for (i = 0; i < capacidade; i++) {
        if (vetor[i] != NULL) {
            free(vetor[i]);
            vetor[i] = NULL;
        }
    }
}
