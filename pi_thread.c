#include <stdio.h>          // Biblioteca para funções de entrada e saída (printf, etc)
#include <stdlib.h>         // Biblioteca para funções de alocação de memória e geração de números aleatórios
#include <pthread.h>        // Biblioteca para trabalhar com threads (pthreads)
#include <time.h>           // Biblioteca para medir tempo de execução e criar sementes de aleatoriedade

// Definindo o número de threads que vamos usar (pode ajustar conforme o número de núcleos da sua máquina)
#define NUM_THREADS 4

// Definindo o número total de pontos a serem gerados no método de Monte Carlo
#define NUM_PONTOS 100000000

// Variável global que vai contar quantos pontos caíram dentro do círculo
long long int pontos_dentro = 0;

// Variável global do tipo mutex para controlar o acesso à variável pontos_dentro (evitar condições de corrida)
pthread_mutex_t mutex;

// Função que cada thread vai executar
void* calcular_pi(void* arg) {
    // Calcula quantos pontos cada thread deve gerar (divide igualmente entre as threads)
    long long int pontos_por_thread = NUM_PONTOS / NUM_THREADS;

    // Variável local para contar os pontos dentro do círculo, para essa thread
    long long int local_contagem = 0;

    // Semente exclusiva para cada thread (evita que todas usem a mesma sequência de números aleatórios)
    unsigned int seed = time(NULL) ^ (long long int)pthread_self();

    // Loop que gera os pontos e testa se estão dentro do círculo
    for (long long int i = 0; i < pontos_por_thread; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;  // Gera um número aleatório entre 0 e 1 para x
        double y = (double)rand_r(&seed) / RAND_MAX;  // Gera um número aleatório entre 0 e 1 para y

        // Verifica se o ponto (x, y) está dentro do círculo de raio 1
        if ((x * x + y * y) <= 1.0) {
            local_contagem++;  // Incrementa a contagem local de pontos dentro do círculo
        }
    }

    // Entra na região crítica para atualizar a variável global de forma segura
    pthread_mutex_lock(&mutex);
    pontos_dentro += local_contagem;
    pthread_mutex_unlock(&mutex);

    // Finaliza a execução da thread
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];  // Declaração do vetor de threads
    pthread_mutex_init(&mutex, NULL);  // Inicializa o mutex

    clock_t inicio = clock();  // Marca o tempo de início da execução

    // Cria as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calcular_pi, NULL);  // Cada thread executa a função calcular_pi
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t fim = clock();  // Marca o tempo de término da execução

    // Calcula a estimativa final de Pi
    double pi = 4.0 * pontos_dentro / NUM_PONTOS;

    // Calcula o tempo total de execução
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Exibe o resultado
    printf("Estimativa de Pi (pthreads): %lf\n", pi);
    printf("Tempo de execução: %.2f segundos\n", tempo);

    // Destroi o mutex
    pthread_mutex_destroy(&mutex);

    return 0;  // Fim do programa
}
// Compilação: gcc -o pi_thread pi_thread.c -lpthread
// Execução: ./pi_thread