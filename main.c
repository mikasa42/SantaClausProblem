#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_ELFOS 10
#define MAX_RENAS 9

int contador_elfos = 0;
int contador_renas = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_elfos = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_renas = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_papai_noel = PTHREAD_COND_INITIALIZER;

// Thread dos elfos
void* thread_elfo(void* arg) {
    int id_elfo = *((int*)arg); // Identifica cada novo elfo
    free(arg); // Libera a memória alocada para o ID do elfo

    while (1) {
        sleep(rand() % 5);  // Tempo randômico para um novo elfo aparecer

        pthread_mutex_lock(&mutex);
        contador_elfos++;
        printf("Elfo %d entrou na fila na posição %d\n", id_elfo, contador_elfos);

        if (contador_elfos == 3) {
            printf("Papai Noel ajudando os elfos\n");
            pthread_cond_signal(&cond_papai_noel);  // Acorda o Papai Noel para ajudar os elfos
        }

        pthread_cond_wait(&cond_elfos, &mutex);  // Espera o Papai Noel ajudar
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// Thread das renas
void* thread_rena(void* arg) {
    int id_rena = *((int*)arg); // Identifica cada nova rena
    free(arg); // Libera a memória alocada para o ID da rena

    while (1) {
        sleep(rand() % 10);  // Tempo randômico para a rena chegar

        pthread_mutex_lock(&mutex);
        contador_renas++;
        printf("Rena %d chegou\n", id_rena); // Cada rena identificada, o contador acrescenta 1 e printa sua chegada

        if (contador_renas == MAX_RENAS) {
            printf("Papai Noel já entregou todos os presentes desse Natal!\n");
            pthread_cond_signal(&cond_papai_noel);  // Acorda o Papai Noel para preparar o trenó
            pthread_mutex_unlock(&mutex);
            exit(0);  // Encerra o programa após a nona e última rena chegar
        }
        
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// Thread do Papai Noel
void* thread_papai_noel(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (contador_renas < MAX_RENAS && contador_elfos < 3) {
            pthread_cond_wait(&cond_papai_noel, &mutex);  // Aguarda a chegada de todas as renas ou elfos
        }

        if (contador_renas == MAX_RENAS) {
            printf("Papai Noel preparando o trenó\n");
            contador_renas = 0;
            // Acorda todas as renas para serem preparadas
            for (int i = 0; i < MAX_RENAS; i++) {
                pthread_cond_signal(&cond_renas);
            }
        }

        if (contador_elfos >= 3) {
            printf("Papai Noel ajudando os elfos\n");
            contador_elfos = 0;
            // Acorda os elfos para voltarem ao trabalho
            for (int i = 0; i < 3; i++) {
                pthread_cond_signal(&cond_elfos);
            }
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t tid_papai_noel;
    pthread_t tid_elfos[MAX_ELFOS];
    pthread_t tid_renas[MAX_RENAS];

    pthread_create(&tid_papai_noel, NULL, thread_papai_noel, NULL);

    for (int i = 1; i <= MAX_ELFOS; i++) {
        int* id_elfo = malloc(sizeof(int));
        *id_elfo = i;
        pthread_create(&tid_elfos[i - 1], NULL, thread_elfo, id_elfo);
    }

    for (int i = 1; i <= MAX_RENAS; i++) {
        int* id_rena = malloc(sizeof(int));
        *id_rena = i;
        pthread_create(&tid_renas[i - 1], NULL, thread_rena, id_rena);
    }

    pthread_join(tid_papai_noel, NULL);
    for (int i = 0; i < MAX_ELFOS; i++) {
        pthread_join(tid_elfos[i], NULL);
    }
    for (int i = 0; i < MAX_RENAS; i++) {
        pthread_join(tid_renas[i], NULL);
    }

    return 0;
}
