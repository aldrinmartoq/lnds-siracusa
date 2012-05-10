// siracusa-optm-1.c -- 1ª versión optimizada en C de siracusa-performante.c
// se usan operaciones bit a bit
// por @aldrinmartoq
// 
// Ejemplo compilación clang y ejecución:
// $ clang -O4 siracusa-optm-1.c -o siracusa
// $ time ./siracusa 10000000
// 8400511
// 
// real 0m1.680s
// user 0m1.671s
// sys  0m0.007s

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

typedef unsigned long long NUMERO;
#define MAX 1000000
NUMERO saltos[MAX];

NUMERO siracusa(NUMERO i) {
    NUMERO b;
    if (i < MAX && saltos[i] != 0) return saltos[i];
    b = siracusa((i & 1) ? ((i<<1)|1) + i : i >> 1) + 1;
    if (i < MAX) saltos[i] = b;
    return b;
}

int main(int argc, char **argv) {
    NUMERO i, max = 0, index = 1;
    bzero(saltos, MAX);
    saltos[1] = 3;
    saltos[2] = 1;
    saltos[3] = 7;
    saltos[4] = 2;
    for (i = 1; i < atol(argv[1]); i++) {
        NUMERO resultado = siracusa(i);
        if (resultado > max) {
            max = resultado;
            index = i;
        }
    }
    printf("%llu\n", index);
}