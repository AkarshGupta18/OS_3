#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>      
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include <stdbool.h>

int str_len = 5;
int len = 50;

int main(){

			int shmid;
			char *shmptr, *var, *rd;
			key_t key2 = 345;

			shmid = shmget(key2, 1024 , 0666);       
			if( shmid < 0){
				printf("Client could not get the shared memory \n");
				exit(1);
			}
			shmptr = shmat(shmid, NULL, 0);       
			if(shmptr == (char *)-1){
				printf("shared memory could not attached to the client");
				exit(1);
			}
			printf("ID ===> String\n");

			var = shmptr;    
            
			char a,b;
            int i=0;
			while(i< 10){


						while((*var) != '&'){
							

							for(int j = 0; j< str_len; j++){
								printf("%c" , *var);
								var++;
							}
							
							printf("\n");
							a = *temp;
							printf("%c",*var);

							var++;
							b = *var;

							printf("%c\n", *var);
							var++;							
						}
						
						*var = '#';
						sleep(1);
						*var = a;  
						var++;
						*var = b;
						sleep(1);
             i++;
			}

			shmdt(shmptr);  

}
