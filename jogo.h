#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>

#define MAX_JOGOS 100
#define ARQUIVO_DADOS "dados.txt"
#define TAM_TEXTO 100

typedef struct {
    int codigo;
    char titulo[TAM_TEXTO];
    char desenvolvedora[TAM_TEXTO];
    double preco;
    double horas_jogadas;
} Jogo;

void inicializarVetor(Jogo *vetor[], int capacidade);

int localizarEspacoLivre(Jogo *vetor[], int capacidade);
int localizarPorCodigo(Jogo *vetor[], int capacidade, int codigo);

int cadastrarJogo(Jogo *vetor[], int capacidade);
void listarJogos(Jogo *vetor[], int capacidade);
Jogo *buscarJogo(Jogo *vetor[], int capacidade, int codigo);
void mostrarRelatorio(Jogo *vetor[], int capacidade);

int carregarDados(Jogo *vetor[], int capacidade);
int salvarDados(Jogo *vetor[], int capacidade);
void liberarDados(Jogo *vetor[], int capacidade);

void limparBufferEntrada(void);

#endif
