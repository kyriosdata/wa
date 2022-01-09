#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Realiza busca binária por termo no array fornecido.
 * Retorna -1 se o termo não é encontrado em palavras.
 */
int encontre(char *palavras[], int tamanho, char *termo)
{
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;
    int comparacao = 0;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;
        comparacao = strcmp(termo, palavras[meio]);
        if (comparacao == 0)
        {
            return meio;
        }

        if (comparacao < 0)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    return -1;
}

static char *palavroes[5] = {"do", "make", "shit", "talk", "walk"};

int main(int argc, char *argv[])
{
    int i = 1;
    char *entrada = "talk";

    printf("looking at %s\n", entrada);
    int index = encontre(palavroes, 5, entrada);
    if (index < 0)
    {
        printf("Nao encontrado\n");
    }
    else
    {
        printf("Encontrado em %d\n", index);
    }
    return 0;
}