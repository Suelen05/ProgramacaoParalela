#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 

int main() {
    
    long long int num_pontos = 10000000000; // 1 bilhao de pontos
    long long int pontos_dentro = 0; 
    double x, y;

    clock_t inicio = clock();

    srand(time(NULL)); //gera números aleatórios

    for (long long int i = 0; i < num_pontos; i++) { //Gera as cordenadas aleatorias 
        x = (double)rand() / RAND_MAX; 
        y = (double)rand() / RAND_MAX; 

        if ((x * x + y * y) <= 1.0) { // Verifica se o ponto esta no circulo
            pontos_dentro++;
        }
    }

    clock_t fim = clock();

    double pi = 4.0 * pontos_dentro / num_pontos;           // Calcula a estimativa de Pi
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; // Calcula o tempo total de execução

    printf("Estimativa de Pi: %lf\n", pi);
    printf("Tempo de execução: %.2f segundos\n", tempo); 

    return 0;
}

// Compilação: gcc -o pi.exe pi.c 
// Execução: ./pi.exe
