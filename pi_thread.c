#include <stdio.h>          
#include <stdlib.h>        
#include <pthread.h>        
#include <time.h>           


#define NUM_THREADS 32

#define NUM_PONTOS 1000000000       // 1 bilhao de pontos

long long int pontos_dentro = 0;        

pthread_mutex_t mutex;             //mutex para controlar o acesso à variável compartilhada (para evitar condições de corrida)


void* calcular_pi(void* arg) {
    
    long long int pontos_por_thread = NUM_PONTOS / NUM_THREADS;     //Divide o numero total de pontos pelo numero de threads

    long long int local_contagem = 0;                               //Pontos dentro em cada thread

    unsigned int seed = time(NULL) ^ (long long int)pthread_self(); // Semente de numeros aleatorios de cada thread (pra evitar que usem a mesma sequência de números aleatórios)

    
    for (long long int i = 0; i < pontos_por_thread; i++) {         //Gera as cordenadas aleatorias 
        double x = (double)rand_r(&seed) / RAND_MAX;  
        double y = (double)rand_r(&seed) / RAND_MAX;  

        if ((x * x + y * y) <= 1.0) {   // Verifica se a cordenada ta dentro do círculo
            local_contagem++; 
        }
    }

    // trava mutex para atualizar a variável global 
    pthread_mutex_lock(&mutex);
    pontos_dentro += local_contagem;
    pthread_mutex_unlock(&mutex);


    pthread_exit(NULL); // Finaliza a thread
}

int main() {
    pthread_t threads[NUM_THREADS];     // cria o vetor de threads
    pthread_mutex_init(&mutex, NULL);   // Inicializa o mutex

    clock_t inicio = clock();           // Marca o tempo de início para a comparação

    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calcular_pi, NULL);  //Cria as threads e executa a função calcular_pi
    }

   
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);     // Aguarda todas as threads terminarem
    }

    clock_t fim = clock();  // Marca o tempo de término da execução

    
    double pi = 4.0 * pontos_dentro / NUM_PONTOS;   // Calcula a estimativa de Pi

    
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; // Calcula o tempo total de execução


    printf("Estimativa de Pi (pthreads): %lf\n", pi);
    printf("Tempo de execução: %.2f segundos\n", tempo);

    
    pthread_mutex_destroy(&mutex);  // Destroi o mutex

    return 0; 
}
// Compilação: gcc -o pi_thread.exe pi_thread.c -lpthread
// Execução: ./pi_thread.exe