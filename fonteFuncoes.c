#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void mostrarMatriz(int colunas, int **matriz, int linhas)
{
    // Matriz mostrada para o usuário, a matriz referente a ela estará na matrizPrincipal
    printf("\n    0  1  2  3  4 \n");
    printf(" +---------------+ \n");
    for (int i = 0; i < linhas; i++)
    {
        printf("%d| ", i);
        for (int j = 0; j < colunas; j++)
        {
            if (matriz[i][j] == 0)
            {
                printf(" ~ ");
            }
            else if (matriz[i][j] == 1)
            {
                printf(" X ");
            }
            else if(matriz[i][j] == 2)
            {
                printf(" * ");
            }
        }
        printf(" \n +---------------+ \n");
    }
}

int mostrarMenu(){
    //mostra o menu abrindo o arquivo e mostrando o conteudo do arquivo que tem 3 opcoes
   FILE *fileMenu = fopen("menu.txt", "r");
    char mensagem[100] = " ";
   

    while(fgets(mensagem, 100, fileMenu) != NULL){
        printf(mensagem);
    }
    printf("\n");
    fclose(fileMenu);
    return 0;
}

int mostrarInfo(FILE *fileInfo){
//mostra as opcoes para acessar o sistema
char mensagem[100];
    if(fileInfo == NULL){
        printf("ERRo não consegui ler as informacoes de entrada do arquivo info.txt");
        return -1;
    }
   

    while(fgets(mensagem, 100, fileInfo) != NULL){
        printf(mensagem);
    }
    printf("\n");
    fclose(fileInfo);
    return 0;
}
int MostrarOpcoes()
{
 //utiliza a funcao para mostrar as opcoes e obtem a resposta do usuario;
    int opcao = 0;
   mostrarMenu();

    scanf("%d", &opcao);
    if (opcao < 1 || opcao > 3)
    {
        printf("Opcao nao eh valida");
        return 0;
    }
    else
        return opcao;
}

int atacar(int *pbarcos, int *pvida, int **matriz, int **matrizRecebida)
{

//realiza o ataque a alguma coordenada do mapa
    int x, y = 0;
    printf("Digite as coordenadas");
    scanf("%d%d", &x, &y);

    //caso a coodernada seja inválida
    if (x < 0 || x > 4 || y < 0 || y > 4)
    {
        printf("Coordenadas invalidas... Digite coordenadas validas para X e Y, nao se esqueca que as coordenadas como A, B, C sao equivalentes a 1, 2 e 3 respectivamente!");
        return 0;
    }
    if (matrizRecebida[x][y] == 1)
    {
        //se for um barco ele ganha 2 vidas e acrescenta o número de barcos acertados para que se possa saber quando o usuario ganhou o jogo
        printf("Voce acertou um barco, muito bem! ");
        printf("MAIS 2 VIDAS");
        matriz[x][y] = 1;
        *pvida += 3;
        (*pbarcos)++;
         printf(", QUANTIDADE DE BARCOS %d --",  *pbarcos);
        printf("voce tem %d vidas restantes", *pvida);
    }else if(matrizRecebida[x][y] == 2){
                //se for uma bomba ele perde 2 vidas 
        printf("\nVoce acertou uma bomba!\n");
          matriz[x][y] = 2;
          *pvida -= 2;
     printf("voce tem %d vidas restantes", *pvida);
          
    }
    else
    {
        printf("Voce errou!");
        *pvida -= 1;
        printf("voce tem %d vidas restantes", *pvida);
    }
    return 0;
}
void liberarMemoria(int **matriz, int **matriz2, int linhas)
{//libera a memoria das duas matrizes alocadas
    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
        free(matriz2[i]);

    }
    free(matriz);
    free(matriz2);
}
int regras(FILE *fileRegras )
{


char mensagem[100];
    if(fileRegras == NULL){
        printf("ERRo");
      return 0;
    }
   

    while(fgets(mensagem, 100, fileRegras) != NULL){
        printf(mensagem);
    }
    printf("\n");
    fclose(fileRegras);
    return 0;


}
int logicaJogo(int *pbarcos, int *pdica, int *pvida, int colunas, int linhas, int **matriz, int **matrizRecebida)
{
//logica do jogo que roda até o usuario vencer ou a vida atingir 0 = perder;
    while (*pvida > 0)
    {
        if(*pbarcos == 5){
            printf("Parabens voce ganhou o jogo!!");
            return 0;
        }
        mostrarMatriz(colunas, matriz, linhas);
        int opcao;
        opcao = MostrarOpcoes();
        //captura a opcao do usuario e verifica qual é a proxima atitude do usuario
        switch (opcao)
        {
        case 1:
            atacar(pbarcos, pvida, matriz, matrizRecebida);
            break;

        case 2:
       
            //Mostra a quantidade de dicas e quando ele gasta uma mostra a quantidade de barcos e a quantidade de bombas em uma determinada linha
            if(*pdica > 0){
                 (*pdica)--;
            printf("\n agora voce tem %d dicas\n", *pdica);
            int linhaDica = 0, qtdBarco = 0, qtdBomba = 0;
            printf("Digite uma linha");
            scanf("%d", &linhaDica);
            if (linhaDica < 0 || linhaDica > 4)
            {
                printf("Linha invalida");
                // return 0;
                // acrescentar quando mudar para funcao independente
            }
            else
            {
                for (int colunasAux = 0; colunasAux < colunas; colunasAux++)
                {
                    if (matrizRecebida[linhaDica][colunasAux] == 1)
                    {
                        qtdBarco++;
                    }
                    else if (matrizRecebida[linhaDica][colunasAux] == 2)
                    {
                        qtdBomba++;
                    }
                }
                printf("Existem %d barcos nessa linha, e a quantidade de bombas eh de %d", qtdBarco, qtdBomba);
            }
//caso ele não tenha mais dicas
            } else{
                printf("voce nao tem mais dicas!");
            }
           
            break;

        case 3:
        //encerra o jogo e libera a memoria
            printf("Jogo encerrado");
            liberarMemoria(matriz, matrizRecebida, linhas);
            return 0;
            break;
     //encerra o jogo e libera a memoria
        default:
            liberarMemoria(matriz, matrizRecebida, linhas);
            printf("Error");
            system("pause");
            break;
        }
    }
    return 0;
}
//verificacao relacionada a senha - DADOS DO USUARIO
int verificar(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return (*str1) - (*str2);
}
//funcao para remocao - DADOS DO USUARIO
void remover(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}
//seleciona a matriz e carrega ela de acordo com a matriz escolhida, fazendo com que as bombas = 2; barcos = 1; agua = 0;
int matrizSelecionada(int **matriz){
     int k = 0, opcao;
     char mensagem[25];
     printf("\n");
  printf("Coloque o mapa que deseja comecar, 1 - Facil, 2 - Medio, 3 - Dificil \n");
    scanf("%d", &opcao);
     FILE *fileMapa;
     //solicita o mapa
    switch (opcao)
    {
    case 1:
    //facil
         fileMapa = fopen("world1.txt", "r");
        break;
        case 2:
        //medio
           fileMapa = fopen("world2.txt", "r");
        break;
        case 3:
        //dificil
            fileMapa = fopen("world3.txt", "r");
        break;
    
    default:
    printf("Mapa inválido!");
        break;
    }
    if(fileMapa == NULL){
        printf("ERRo não foi possível achar o MENU DO JOGO");
        return -1;
    }
    //pega a primeira linha e coloca em mensagem
   fgets(mensagem, sizeof(mensagem), fileMapa);
   //percorre mensagem e coloca em uma matriz[5][5]
   for(int i =0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(mensagem[k] == '1'){
                matriz[i][j] = 1;
            }else if(mensagem[k] == '2'){
                matriz[i][j] = 2;
            }else{
                matriz[i][j] = 0;
            }
            k++;
            if(k >= 25){
                break;
            }
        }
          if(k >= 25){
                break;
            }
    }
 //fecha o arquivo aberto
    fclose(fileMapa);
    return 0;


}



// Função principal do jogo
void jogarJogo() {

    int **matrizCriar, linhas = 5, colunas = 5, vida = 7, dicas = 3, barcos = 0, *pbarcos = &barcos, **matriz, *pvida = &vida, *pdica = &dicas;
    struct pessoa p;

    printf("Bem vindo, %s!\n", p.nome);

    printf("Você já foi pirata e sabe navegar?");

    FILE *fileRegras = fopen("mensagens.txt", "r"); // Substitua "regras.txt" pelo nome do seu arquivo de regras
    if (fileRegras == NULL) {
        printf("Erro ao abrir o arquivo de regras.\n");
        return;
    }

    regras(fileRegras);

    fclose(fileRegras);
    //aloca a matriz
    matrizCriar = (int **) malloc(5 * sizeof(int *));
    for(int i = 0; i< 5; i++){
        matrizCriar[i] = (int *) malloc(5 * sizeof(int));
    }
    matrizSelecionada(matrizCriar);


    // Aloca a matriz inicial
    matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++)
        {
            matriz[i][j] = 0;
        }
    }
    if (matriz == NULL)
    {
        printf("Erro");
        exit(0);
    }

    logicaJogo(pbarcos, pdica, pvida, colunas, linhas, matriz, matrizCriar);
}