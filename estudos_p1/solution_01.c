#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

/*
        A
        |
        B
     / / \ \
    C D  E  F
       / | \
      G  H  I
            |
            J
*/

void espera(){
    int status;

    wait(&status);
}

void report(){
    printf("%d -- %d\n", getppid(), getpid());
}

void ultimo_filho(){
    report();
}

void cria_filho(){
    ultimo_filho();

    espera();
    if(fork() == 0){
        espera();
        ultimo_filho();
    }else if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
    }else if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
        cria_filho_simples();
        espera();
    }
}

void cria_filho_simples(){
    espera();
    if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
        printf("}\n");
    }
}

int main(){

    printf("graph {\n");
    report();

    espera();
    if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
    }else if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
    }else if(fork() == 0){
        espera();
        cria_filho();
        espera();
    }else if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
    }

    return 0;
}
