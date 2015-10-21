#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int meses;
    float juros = 0.01; //1%
    float resultado = 500;

    printf("Digite o valor de meses: ");
    scanf("%d", &meses);

    resultado = resultado*(pow(1 + juros, meses));

    printf("O valor da conta = %f\n", resultado);

    return 0;
}
