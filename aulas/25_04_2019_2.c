#include <stdio.h>

int main(){

    int x, y;

    short int *a, *b, *c, *d;

    a = &x;
    b = a+1;
    c = &y;
    d = c+1;

    *a = 10;
    *b = 20;
    *c = 7;
    *d = 8;

    x = x + y;

    printf("%d\n", x);

    return 0;
}
