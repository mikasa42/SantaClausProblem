#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MAX 3

int buffer[MAX];
int posicaoInsercao = 0;
int posicaoLeitura = 0;
int contador = 0;

int produtosTotais = 100;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t livre = PTHREAD_COND_INITIALIZER;
pthread_cond_t preenchido = PTHREAD_COND_INITIALIZER;

int randomico() {

    int i;
    int num;

    srand(time(NULL));

    for(i = 0; i < 10; i++){
        num = 1 + rand() % 100;
        num = num % 10;
    };

    return num;
}

void inserirBuffer(int valor) {
     buffer[posicaoInsercao] = valor;
     posicaoInsercao++;
     if (posicaoInsercao == MAX)
         posicaoInsercao = 0;
     contador++;
}

int lerBuffer() {
     int tmp = buffer[posicaoLeitura];
     posicaoLeitura++;
     if (posicaoLeitura == MAX)
         posicaoLeitura = 0;
     contador--;
     return tmp;
}

void *produtor(void *arg) {
     int i;
     for (i = 0; i < produtosTotais ; i++){
          pthread_mutex_lock(&mutex);
          printf("Elfo %d: trabalhando \n",i);
          while (contador == MAX)
                pthread_cond_wait(&livre,&mutex);
          inserirBuffer(i);
          pthread_cond_signal(&preenchido);
          pthread_mutex_unlock(&mutex);
     }
     return NULL;
}

void *consumidor(void *arg) {
     int i;
     for (i = 0; i < produtosTotais ; i++){
          pthread_mutex_lock(&mutex);
          printf("Elfo %d: precisa de ajuda\n",i);
          while (contador == 0)
                pthread_cond_wait(&preenchido,&mutex);
          printf("Elfo %d: recebeu ajuda\n",i);
          int tmp = lerBuffer();
          pthread_cond_signal(&livre);
          pthread_mutex_unlock(&mutex);
          printf("Lido: %d\n",tmp);
     }
     return NULL;
}


int main(void) {
    pthread_t prod,consu;
    pthread_create(&prod, NULL, produtor, NULL);
    pthread_create(&consu, NULL, consumidor, NULL);
    pthread_join(prod,NULL);
    pthread_join(consu,NULL);
    printf("Rena chegando !");
    int numero;
    int i=0;
    numero = randomico();
    while(i<=9);//contando até o 9 mas em instantes de tempo diferentes.
    {
          if(numero<5){
               printf("Rena chegando !");
               i++;
          }

    }

    return 0;
}

//Encontrar uma forma de printar o contador de fato.
//Fazer um while que conte até 9.
