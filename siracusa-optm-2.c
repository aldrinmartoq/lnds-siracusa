// siracusa-optm-2.c -- 2ª versión optimizada en C de siracusa-performante.c
// hacemos caché sólo de los números impares
// por @aldrinmartoq
// 
// 
// Ejemplo compilación clang y ejecución:
// $ clang -O4 siracusa-optm-2.c -o siracusa
// $ time ./siracusa 10000000
// 8400511
// 
// real 0m1.384s
// user 0m1.375s
// sys  0m0.006s

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

typedef unsigned long long NUMERO;
#define MAX 1000000
NUMERO cache[MAX];

NUMERO siracusa(NUMERO n) {
    /* impar */
    if (n % 2 != 0) {
        /* buscar en caché */
        NUMERO k = n / 2;
        if (k < MAX && cache[k] != 0) {
            return cache[k];
        }

        /* no está, calcular a mano */
        NUMERO l = siracusa(n * 3 + 1) + 1;

        /* agregar al caché */
        if (k < MAX) {
            cache[k] = l;
        }

        return l;
    }

    /* par, dividir por 2 */
    NUMERO l = 0;
    while (n % 2 == 0) {
        l++;
        n = n / 2;
    }
    
    /* caso idiota n == 1, ya llegamos */
    if (n == 1) {
        return l;
    }
    
    /* retornar siracusa de impar != 1 */
    return siracusa(n) + l;
}

int main(int argc, char **argv) {
    NUMERO i, max = 0, index;
    bzero(cache, MAX);
    cache[0] = 3;
    for (i = 1; i <= atol(argv[1]); i++) {
        NUMERO resultado = siracusa(i);
        if (resultado > max) {
            max = resultado;
            index = i;
        }
    }
    printf("%llu\n", index);
    return 0;
}