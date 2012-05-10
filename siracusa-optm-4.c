// siracusa-optm-4.c -- 4ª versión optimizada en C de siracusa-performante.c
// acá solo hacemos caché de los números impares, además quitamos la recursión. No es más performante.
// por @aldrinmartoq
// 
// 
// Ejemplo compilación clang y ejecución:
// $ clang -O4 siracusa-optm-4.c -o siracusa
// $ time ./siracusa 10000000
// 8400511
// 
// real 0m4.886s
// user 0m4.871s
// sys  0m0.011s

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

typedef unsigned long long NUM;
#define MAX 1000000
NUM cache[MAX];

NUM siracusa(NUM n) {
    NUM largo = 0;
    NUM orig = n;
    do {
        /* impar, buscar en caché */
        if (n & 1) {
            if (n < (MAX * 2) && cache[n / 2] != 0) {
                return cache[n / 2] + largo;
            }

            /* siguiente número par */
            n = n * 3 + 1;
        }
        /* incrementar largo dividiendo por 2 */
        do {
            // printf("voy: l %llu o %llu m %llu n %llu\n", largo, orig, m, n);
            largo += 1;
            n = n / 2;
        } while (!(n & 1));
    } while (n > 1);

    if ((orig < MAX * 2) && (orig & 1)) {
        cache[orig/2] = largo;
    }

    // /* guardar en caché ssi impar */
    // if (orig & 1) {
    //     NUM m = n / 2;
    //     if (m < MAX) {
    //         cache[m] = largo;
    //     }
    // }
    
    return largo;
}

int main(int argc, char **argv) {
    NUM i, max = 0, index;
    bzero(cache, MAX);
    cache[0] = 3;
    for (i = 1; i <= atol(argv[1]); i++) {
        NUM resultado = siracusa(i);
        // printf("%20llu %llu\n", i, resultado);
        if (resultado > max) {
            max = resultado;
            index = i;
        }
    }
    printf("%llu\n", index);
    return 0;
}