#ifndef FUNCOES_H
#include <stdio.h>
struct pessoa
{
    char nome[50];
    char idade[3];
    char senha[20];
};
struct pirata
{
    char navio[50];
    int ano;
   
};
//mostra a matriz incial
void mostrarMatriz(int colunas, int **matriz, int linhas);
//mostra o Menu
int mostrarMenu();
//mostra as informações do jogo
int mostrarInfo(FILE *fileInfo);
//mostra as opções do jogo
int MostrarOpcoes();
//realiza o ataque ao navio
int atacar(int *pbarcos, int *pvida, int **matriz, int **matrizRecebida);
//libera a memoria das duas matrizes alocadas
void liberarMemoria(int **matriz, int **matriz2, int linhas);
//mostra as regras do jogo que estão em um arquivo
int regras(FILE *fileRegras);
//logica do jogo que roda até o usuario vencer ou a vida atingir 0 - perder;
int logicaJogo(int *pbarcos, int *pdica, int *pvida, int colunas, int linhas, int **matriz, int **matrizRecebida);
//verificacao relacionada a senha
int verificar(const char *str1, const char *str2);
//funcao para remocao
void remover(char *str);
//seleciona a matriz e carrega ela de acordo com a matriz escolhida, fazendo com que as bombas = 2; barcos = 1; agua = 0;
int matrizSelecionada(int **matriz);
void jogarJogo();



#endif