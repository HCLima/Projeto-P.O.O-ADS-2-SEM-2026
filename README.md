# Catalogo de Jogos Digitais

Projeto pratico em C desenvolvido como aplicacao de console usando o paradigma TAD, vetor de ponteiros alocado dinamicamente e persistencia em arquivo texto.

## Identificacao

- Integrante 1: **Henrique Cruz de Lima** - RA: **1630482611023**

## Motivo da escolha do tema

O tema "Catalogo de Jogos Digitais" foi escolhido por permitir relacionar dados inteiros, textos e valores decimais em uma base simples de consultar e manter.
O projeto cadastra codigo, titulo, desenvolvedora, preco e horas jogadas.

## Modelagem e arquitetura

Os dados foram modelados pela struct `Jogo`, definida em `jogo.h`. O vetor `Jogo *jogos[MAX_JOGOS]` inicia com todas as posicoes em `NULL`. Cada registro existente recebe memoria com `malloc` e pode ser recuperado por codigo.

A divisao do projeto ficou organizada da seguinte forma:

- `jogo.h`: constantes, tipo `Jogo` e prototipos das operacoes.
- `jogo.c`: cadastro, busca, listagem, relatorio, persistencia e liberacao de memoria.
- `main.c`: menu principal com `do...while` e `switch-case`.
- `dados.txt`: persistencia automatica dos registros.
- `README.md`: identificacao e documentacao.

Ao iniciar, o programa tenta abrir `dados.txt` no modo leitura. Ao terminar pela opcao 5, os dados sao gravados no modo escrita e todos os ponteiros alocados sao liberados com `free`.

## Compilacao

No terminal, entre na pasta do projeto e execute:

```sh
gcc -Wall -Wextra -pedantic -std=c11 main.c jogo.c -o catalogo_jogos
```

## Execucao

Linux, macOS ou terminal compativel:

```sh
./catalogo_jogos
```

No Windows com terminal MSYS2/MinGW:

```sh
catalogo_jogos.exe
```
