#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

int res[1000][1000];
int a[1000][1000];
int b[1000][1000];

int v1;
int v2;

void *calcula_multiplicacao(){
    int i, j;
    long int aux = 1;
    for(i = v1; i <= v2; i++){
        aux = 1;
        for(j = 0; j < 1000; j++){
            aux = a[i][j] * b[i][j];
            res[i][j] = aux;
        }
    }

    v1 += 250;
    v2 += 250;

    pthread_exit (NULL) ;
}

int main(){


    memset(a, 0, sizeof(int));
    memset(b, 0, sizeof(int));
    memset(res, 0, sizeof(int));

    time_t t;

    int i, j;

    srand((unsigned) time(&t));

    for(i = 0; i < 1000; i++){
        for(j = 0; j < 1000; j++){
            a[i][j] = rand() % 15 + 1;
        }
    }

    for(i = 0; i < 1000; i++){
        for(j = 0; j < 1000; j++){
            b[i][j] = rand() % 15 + 1;
        }
    }

    v1 = 0;
    v2 = 249;

    pthread_t threads[4];
    int rc;

    pthread_create(&threads[0], NULL, calcula_multiplicacao, &i);
    pthread_create(&threads[1], NULL, calcula_multiplicacao, &i);
    pthread_create(&threads[2], NULL, calcula_multiplicacao, &i);
    pthread_create(&threads[3], NULL, calcula_multiplicacao, &i);

    pthread_join(&threads[0], NULL);
    pthread_join(&threads[1], NULL);
    pthread_join(&threads[2], NULL);
    pthread_join(&threads[3], NULL);

    // v1 = 0;
    // v2 = 999;
    // calcula_multiplicacao();

    // printf("\n\n\n\n\n");

    // for(i = 0; i < 16; i++){
    //     for(j = 0; j < 16; j++){
    //         printf("%d ", a[i][j]);
    //     }
    //     printf("\n");
    // }
    //
    // printf("\n\n\n\n\n");
    //
    // for(i = 0; i < 16; i++){
    //     for(j = 0; j < 16; j++){
    //         printf("%d ", b[i][j]);
    //     }
    //     printf("\n");
    // }
    //
    // printf("\n\n\n\n\n");
    //

    // for(i = 0; i < 1000; i++){
    //     for(j = 0; j < 1000; j++){
    //         printf("%d ", res[i][j]);
    //     }
    //     printf("\n");
    // }


    return 0;
}
