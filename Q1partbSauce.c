#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sticks[5];
sem_t bowl;

void * philosopher(void * p);
void r(int m);

int main(){
    
    pthread_t tid[5];
    sem_init(&bowl, 0, 2);
    
   

    for(int i=0; i < 5;i++){
        sem_init(&sticks[i],0,1);
    }
  

    int tmp[5];
    

    for(int j = 0; j < 5; j++){

        tmp[j] = j; 
        pthread_create(&tid[j], NULL, &philosopher, (void *) &tmp[j]);

    }

 

    for(int k = 0; k < 5; k++){

         pthread_join(tid[k], NULL);
       
       
    }

    return 0;
}

void r(int m){
    
    sleep(m);
}

void * philosopher(void *p){

    int num = * (int*) p;
   
    while(1){

        printf("Philosopher %d is thinking\n", num);

        sem_wait(&bowl);
        printf("Philosopher %d takes a bowl\n", num);

        sem_wait(&sticks[num]);
        sem_wait(&sticks[(num + 1) % 5]);
        printf("Philosopher %d takes both forks\n", num); 

        printf("Philosopher %d is eating\n", num); 
        r(3);
        
        printf("Philosopher %d puts both forks \n", num);
        sem_post(&sticks[(num + 1) % 5]);
        sem_post(&sticks[num]);


        printf("Philosopher %d puts a bowl\n", num); 
        sem_post(&bowl);

            

    }
}