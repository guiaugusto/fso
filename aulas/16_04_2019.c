#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>

int set[100];
int r = 0;
int ini, fim;
int espera;

void *get_ticket(){

    int j;

    for(j = ini; j < fim; j++){
        if(set[j] == 0){
            r = j;
            set[j] = -1;
            break;
        }
    }

    printf("Peguei o ticket %d\n", r);

    if(j == 99){
        printf("Não existem tickets suficientes.\n");
        r = -1;
    }

    pthread_exit(NULL);
}

void *return_ticket(){

    printf("%d %d\n", r, espera);
    // sleep(espera);
    wait(&r);

    if(r == -1){
        printf("Não tem ticket doidjo!\n");
    }else{
        if(set[r] != 0){
            set[r] = 0;
        }
    }


    pthread_exit(NULL);
}

int main(){

    memset(set, 0, sizeof set);

    pthread_t threads[4];
    pthread_t tas[2];
    time_t t;

    int i = 1, r, res[4];

    srand((unsigned) time(&t));

    while(i){
        ini = 0;
        fim = 49;
        pthread_create(&threads[0], NULL, get_ticket, NULL);
        // pthread_create(&threads[0], NULL, return_ticket(r, rand() % 10), &i);
        pthread_join(threads[0], NULL);
        // sleep(1);
        espera = rand() % 5;
        pthread_create(&tas[0], NULL, return_ticket, NULL);
        pthread_join(tas[0], NULL);

        ini = 50;
        fim = 99;
        pthread_create(&threads[1], NULL, get_ticket, NULL);
        pthread_join(threads[1], NULL);
        // pthread_create(&threads[1], NULL, return_ticket(r, rand() % 10), &i);
        espera = rand() % 5;
        pthread_create(&tas[1], NULL, return_ticket, NULL);
        pthread_join(tas[1], NULL);
        //
        // sleep(1);
        //
        // pthread_create(&threads[2], NULL, get_ticket, &i);
        // pthread_join(threads[2], NULL);
        // // res[2] = r;
        // //
        // pthread_create(&threads[3], NULL, get_ticket, &i);
        // pthread_join(threads[3], NULL);
        // res[3] = r;

    }

    return 0;
}
