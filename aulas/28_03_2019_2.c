#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void gera_aleatorio(){
    int aleatorio = rand();

    FILE *arq = fopen("/tmp/numeros", "w+");

    fprintf(arq, "%d \n", aleatorio);

    fclose(arq);
}

void verifica(){
    FILE *arq = fopen("/tmp/numeros", "r");

    int n;

    fscanf(arq, "%d", &n);

    fclose(arq);

    if(n % 2 == 0){
        printf("%d eh par \n", n);
    }else{
        printf("%d eh impar \n", n);
    }
}

void fazoqueopaifaz(pid_t filho){
    signal(SIGUSR1, gera_aleatorio);
    int retorno;

    wait(&retorno);
}

void fazoqueofilhofaz(pid_t pai){
    while(1){
        kill(pai, SIGUSR1);
        sleep(1);
        verifica();
    }

}

int main(){

    pid_t filho = fork();

    if(filho > 0){
        //sou o pai
        sleep(1);
        fazoqueopaifaz(filho);
    }else{
        fazoqueofilhofaz(getppid());
    }

    return 0;
}
