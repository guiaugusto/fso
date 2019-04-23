#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void imprime(){
    printf("%d %d\n", getppid(), getpid());
}

int main(){

    printf("%d %d\n", getppid(), getpid());

    pid_t filho = fork();

    int a;

    if(filho > 0){
        // é o pai
        imprime();
        sleep(10);
    }else{
        if(fork() == 0){
            // scanf("%d", &a);
            imprime();
        }
    }
    return 0;
}
