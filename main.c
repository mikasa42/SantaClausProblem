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

// Thread dos elfos
void* thread_elfo(void* arg) {
    int id_elfo = *((int*)arg); // identifica cada novo elfo 

    while (1) {
        sleep(rand() % 5);  // Tempo randômico para um novo elfo aparecer 

        pthread_mutex_lock(&mutex);
        contador_elfos++;
        printf("Elfo %d entrou na fila na posicao %d \n", id_elfo, contador_elfos);

        if (contador_elfos == 3) {
            printf("Papai Noel ajudando os elfos\n");
            contador_elfos = 0;
            printf("Os elfos voltaram ao trabalho\n");
            pthread_cond_signal(&cond_elfos);  // Acorda o Papai Noel para ajudar os elfos
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// Thread das renas
void* thread_rena(void* arg) {

    while (1) {
        sleep(rand() % 10);  // Tempo randômico para a rena chegar

        pthread_mutex_lock(&mutex);
        contador_renas++;
        printf("Rena %d chegou\n", contador_renas); // cada rena identificada o contador acrescenta 1 e printa sua chegada 

        if (contador_renas == MAX_RENAS) {
            printf("Papai Noel já entregou todos os presentes desse Natal!\n");
            exit(0);  // assim que a nona e ultima rena chegar, Encerra o programa
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// Thread do Papai Noel
void* thread_papai_noel(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (contador_renas < MAX_RENAS) {
            pthread_cond_wait(&cond_renas, &mutex);  // Aguarda a chegada de todas as renas
        }
        pthread_mutex_unlock(&mutex);

        printf("Papai Noel ajudando os elfos\n");
        contador_elfos = 0;
      
        pthread_cond_signal(&cond_elfos);            // faz os elfos retornarem ao trabalho apos a ajuda do Papai Noel
    }

    return NULL;
}

int main() {
    pthread_t tid_papai_noel, tid_elfo, tid_rena;
    int i;

    pthread_create(&tid_papai_noel, NULL, thread_papai_noel, NULL);

    for (i = 1; i <= MAX_ELFOS; i++) {
        int* id_elfo = malloc(sizeof(int));
        *id_elfo = i;
        pthread_create(&tid_elfo, NULL, thread_elfo, id_elfo);
    }

    for (i = 1; i <= MAX_RENAS; i++) {
        int* id_rena = malloc(sizeof(int));
        *id_rena = i;
        pthread_create(&tid_rena, NULL, thread_rena, id_rena);
    }

    pthread_join(tid_papai_noel, NULL);
    pthread_join(tid_elfo, NULL);
    pthread_join(tid_rena, NULL);

    return 0;
}
//Neste código temos um limite de elfos = 10 
//Os elfos entram na fila respeitando a ordem de chegada/posição mas cada 1 tem seu numero 
// ex: "Elfo 6 entrou na fila na posicao 1" 
//Elfo 6 nos diz seu numero 
//posicao 1 a sua posicao na fila 
//Quando chegam 3 elfos o papai noel ajuda os elfos.  