#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    double a, b, c, d, e, f;
    double v1, v2, v3;

    a = 1.5;
    b = 4;
    c = 2;
    d = 3;
    e = 1.2;
    f = 4.3;

    v1 = (a*(c+d))/(b*(e+f));
    v2 = (pow(a, (b+c)))/(e+f);
    v3 = (-b + sqrt(pow(b, 2) - (4*a*c)))/(2*a);

    printf("Resultado\n\tv1: %lf\n\tv2: %lf\n\tv3: %lf", v1, v2, v3);

    return 0;
}
