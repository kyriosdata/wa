#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int binary_search(char *list_of_words[], int size, char *target){
    int bottom= 0;
    int mid;
    int top = size - 1;
    int comparacao = 0;

    while(bottom <= top){
        mid = (bottom + top)/2;
        comparacao = strcmp(list_of_words[mid], target);
        if (comparacao == 0){
            return mid;
        }
        
        if (comparacao > 0) {
            top    = mid - 1;
        } else {
            bottom = mid + 1;
        }
    }

    return -1;
}

int main(int argc, char* argv[]){
    int i = 1;
    char *input = "talk";

    char *verbs[5] = { "do", "make", "shit", "talk", "walk" };

        printf("looking at %s\n", input);
    int index = binary_search(verbs, 5, input);
    if (index < 0) {
        printf("Nao encontrado\n");
    } else {
        printf("Encontrado em %d\n", index);
    }
    return 0;
}