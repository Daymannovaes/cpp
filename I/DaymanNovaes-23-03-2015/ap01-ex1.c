#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

int main() {
    double graus, resultado;

    printf("Digite o valor do grau: ");
    scanf("%lf", &graus);
    resultado = sin(graus * PI / 180);

    printf("O valor do seno = %lf\n", resultado);

    return 0;
}
