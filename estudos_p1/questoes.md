# Lista de exercícios - Aula 02/04

## Questões básicas

1. Enumere e explique resumidamente as principais responsabilidades de um sistema.

2. Qual é a diferença entre modo usuário e modo kernel? Por que esta distinção é feita?

3. Descreva como são implementados os seguintes eventos: (i) chamada de sistema, (ii) tratamento de interrupção e (iii) tratamento de sinais. Quais são as semelhanças e diferenças entre estes eventos?

4. Qual é a diferença entre um sistema monolítico e um baseado em camadas?

## Processos

1. Descreva o funcionamento da função fork(). Após o fork, como os processos pai e filho podem se comunicar/sincronizar?

Resposta:

2. O que é um processo Zumbi? Escreva um programa que crie processos zumbis.

Resposta: um processo zumbi, de forma simples, é um processo que mesmo ao término de
sua finalidade ainda permanece na tabela de processos em execução.

Anexo: ao executar o arquivo 02_04_2019_1.c, é possível analisar, temporariamente,
um processo zumbi sendo criado e mantido por um tempo.

3. Familiarize-se com as chamadas: fork(2), wait(2),

4. Abra um terminal e execute o comando: pstree -c -p Descreva o que está vendo.

Resposta: o resultado recebido assemelha-se com uma árvore de processos que estão sendo
executados pelo sistema operacional, desde a serviços específicos do sistema operacional
até a serviços de aplicativos associados à ele, como o chrome.

Resolva  http://wiki.inf.ufpr.br/maziero/doku.php?id=so:criacao_de_processos

Resolva http://www.dei.isep.ipp.pt/~orlando/so2/processos.htm

Familiarize-se com as chamdas: execve(2), clone(2),

## Gerando uma árvore de processos

Durante as aulas de 26 e 28 de março foram iniciadas as ideias de produzir um conjunto de processos para se gerar uma árvore.

Utilize a ferramenta dot, oriunda do pacote graphviz (possui pacote nas ditribuições debian e ubuntu).

O comando dot gera um grafo (ou uma árvore) dada as ligações entre os nós. Por exemplo o arquivo abaixo (nomeado como arvore-forks.dot):

```
graph {
4208 -- 4922;
4931 -- 4933;
4931 -- 4934;
4922 -- 4931;
4922 -- 4932;
4931 -- 4936;
4932 -- 4935;
4935 -- 4938;
4936 -- 4937;
}
```

O arquivo acima pode ser renderizado utilizando o comando:

```
dot -t png arvore-forks.dot -o arvore-forks.png
```

Neste exemplo foi impresso o PID do PAI de um processo e o PID do processo, o dot cuidou para gerar as ligações.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
  if(fork()>0)
  {
    if(fork()==0)
      if(fork()==0)
        fork();
  }
  else
  {
    if(fork())
      if(fork())
        if(fork())
          ;
        else
          fork();
  }
  return 0;
}
```

1. Como é a árvore gerada no programa acima?

Resposta: a árvore gerada é uma árvore binária onde o filho do processo inicial (do terminal),
possui dois filhos de igual altura, contendo um filho cada, até os terceiros sendo os ultimos nós.

2. Modifique o programa acima para que ele imprima na tela o conteúdo de um arquivo para ser passado para o dot.

Resposta: arquivo tree_below.c

3. Faça um programa em C, que gere um conjunto de processos que tenha uma árvore semelhante como da ilustração abaixo:

Resposta: arquivo solution_01.c

1. Faça várias execuções do seu programa e verifique o comportamento do desenho da árvore, a ordem é sempre a mesma? Explique

Não é a mesma, justamente pelo problema da execução em thread, existe uma grande dificuldade de manter o pai
original do processo criado, impedindo do pai ser o processo padrão do sistema.
