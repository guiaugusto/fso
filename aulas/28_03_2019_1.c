#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*
Montar a seguinte árvore de forks:

             A
           /  \
          B   C
             / \
            D  E

*/

void report(){
    printf("%d %d\n", getpid(), getppid());
}

void fazoqueobfaz(){
    report();
}

void fazoqueocfaz(){
    report();

    if(fork() == 0){
        fazoqueobfaz();
    }else{
        if(fork() == 0){
            fazoqueobfaz();
        }
    }
}

int main(){

    printf("%d\n", getpid());

    pid_t retf;

    retf = fork();

    if(retf == 0){
        fazoqueobfaz();
    }else{
        if(fork() == 0){
            fazoqueocfaz();
        }
    }

    return 0;
}
