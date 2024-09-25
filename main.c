#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main()
{
    //variaveis usadas no sistema
    int a = 0;
    FILE *fileInfo = fopen("info.txt", "r"), *fp, *f;
    struct pessoa p;
    
      char inputSenha[20];
      

      
    do
    {
    
        mostrarInfo(fileInfo);

        scanf("%d", &a);
          if(a == 2)
    {
        printf("\nUsername: ");
        scanf(" %s", p.nome);
        fp = fopen(p.nome, "w");

        if (fp == NULL)
        {
            printf("Erro ao criar conta.\n");
            return 1;
        }

        fprintf(fp, "Nome: %s\n", p.nome);
        printf("\nIdade: ");
        scanf("%s", p.idade);
        fprintf(fp, "Idade: %s\n", p.idade);

        

        printf("\nSenha: ");
        scanf(" %s", p.senha);
        fprintf(fp, "Senha: %s\n", p.senha);

        fclose(fp);

        printf("\nConta criada, %s! Aparte 1 para entrar na sua nova conta:  \n", p.nome);
	mostrarInfo(fileInfo);
    }
    } while (a != 1 && a != 3);

    if (a == 1)
    {
       //inserção de dados do usuário e verificacao

        printf("Username: ");
        scanf("%s", p.nome);

        f = fopen(p.nome, "r");
        if (f == NULL)
        {
            printf("Conta nao encontrada.\n");
            return 1;
        }

        while (fgets(p.senha, sizeof(p.senha), f) != NULL)
        {
            if (strstr(p.senha, "Senha:"))
            {
                remover(p.senha);
                break;
            }
        }

        fclose(f);

      
        printf("Senha: ");
        scanf("%s", inputSenha);
    //verificacao relacionada a senha
        if (verificar(p.senha + 7, inputSenha) == 0)
        {

            jogarJogo();
    	    return 0;
        }
        else
        {
            printf("Senha incorreta!\n");
        }

        return 0;
    }
  

    return 0;
}