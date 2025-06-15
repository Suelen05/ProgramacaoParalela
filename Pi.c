#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    long long int num_pontos = 10000000000; // 100 milhões de pontos
    long long int pontos_dentro = 0;
    double x, y;

    srand(time(NULL));

    for (long long int i = 0; i < num_pontos; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        if ((x * x + y * y) <= 1.0) {
            pontos_dentro++;
        }
    }

    double pi = 4.0 * pontos_dentro / num_pontos;
    printf("Estimativa de Pi: %lf\n", pi);

    return 0;
}
