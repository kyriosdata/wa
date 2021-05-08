#include <emscripten.h>
#include <stdio.h>

int main() {
    printf("Main!\n");
    int valorInt = emscripten_run_script_int("getNum()");
    printf("Valor obtido de código em JavaScript: %d\n", valorInt);
    return -95;
}

int numero() {
    return 234;
}

int quadrado(int x) {
    return x * x;
}