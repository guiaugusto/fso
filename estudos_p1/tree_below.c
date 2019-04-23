#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void report(){
    printf("%d -- %d\n", getppid(), getpid());
}

void espera(){
    int status;

    wait(&status);
}

void cria_filho_1(){

    espera();
    if(fork() == 0){
      espera();
      ultimo_filho();
      espera();
      if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
        cria_filho_simples_1();
        espera();
      }
    }
}

void cria_filho_2(){

    if(fork()){
      if(fork()){
        espera();
        ultimo_filho();
        espera();
      }else{
        espera();
        ultimo_filho();
        espera();
        cria_filho_simples_2();
        espera();
      }
    }
}

void cria_filho_simples_1(){
    espera();
    if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
        printf("}\n");
    }
}

void cria_filho_simples_2(){
    espera();
    if(fork() == 0){
        espera();
        ultimo_filho();
        espera();
    }
}

void ultimo_filho(){
    report();
}

int main(void)
{

  printf("graph {\n");
  report();

  if(fork()>0)
  {
      espera();
      cria_filho_1();
      espera();
  }
  else
  {
    if(fork()){
        espera();
        cria_filho_2();
        espera();
    }
  }
  return 0;
}
