#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int main (void){
int i=0;
    while(i<=9)//contando até o 9 mas em instantes de tempo diferentes.
        {
              printf("%d \n",i);
              i++;
        }
    return 0;
}