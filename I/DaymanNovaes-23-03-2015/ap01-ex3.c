#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    unsigned int a, b, c;
    a = b = c = 0;

    int semi = 0;
    int totals = 0;
    double area = 0;

    printf("Digite o valor de A, B e C: ");
    scanf("%d%d%d", &a, &b, &c);

    semi = (a+b+c)/2;

    area = sqrt(semi*(semi - a)*(semi - b)*(semi - c));

    printf("O valor da area = %lf\n", area);

    return 0;
}
