#include <stdio.h>

int main(void){
    char b[2];
    int a; a = 10;
    b[0] = 'O';
    b[1] = 'l';
    b[2] = 'a';
    b[3] = '\0';

    printf("%s\n", b);
    printf("%d\n", a);
}
