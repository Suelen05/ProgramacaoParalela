#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 

int main() {
    long long int num_pontos = 100000000; // 100 milhões de pontos
    long long int pontos_dentro = 0; // Contador de pontos dentro do círculo
    double x, y; // Coordenadas dos pontos gerados

    srand(time(NULL)); // Semente para o gerador de números aleatórios

    for (long long int i = 0; i < num_pontos; i++) { // Loop para gerar os pontos
        x = (double)rand() / RAND_MAX; // Gera um número aleatório entre 0 e 1 para x
        y = (double)rand() / RAND_MAX; // Gera um número aleatório entre 0 e 1 para y

        if ((x * x + y * y) <= 1.0) { // Verifica se o ponto (x, y) está dentro do círculo de raio 1
            pontos_dentro++;
        }
    }

    double pi = 4.0 * pontos_dentro / num_pontos; // Calcula a estimativa de Pi
    printf("Estimativa de Pi: %lf\n", pi); 

    return 0;
}

// Compilação: gcc -o pi.exe pi.c 
// Execução: ./pi.exe
