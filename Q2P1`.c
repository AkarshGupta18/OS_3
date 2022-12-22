#define infinite  100000000L
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
int variation = 12345; 

char *fn(int size) {       
    char *rnd_str = NULL;
    rnd_str = malloc(sizeof(char) * ( size +1));         
    srand(time(NULL) * (size + ++variation));            
    short k = 0; 
    char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    size_t Len = strlen(str);
    for (int n = 0;n < size;n++) {            
        k = rand() % Len;          
        rnd_str[n] = str[k];
    }
    rnd_str[size] = '\0';
    return rnd_str;        
}

int main(int argc, char** argv){    
    double t1;
    char *c;
    char arr[len][str_len + 1];       

    for(int i = 0; i<len ; i++){
        c = fn(str_len);           
        for(int j = 0; j<str_len + 1; j++){
            arr[i][j] = c[j];
        } 
    }                              
  
    for(int i = 0; i < len; i++){
        printf("%s %d\n" ,arr[i], i+1);
    }
            printf("\n Shared memory (IPC) \n");

            int shmid;
            char *shmptr, *temp;
            key_t k = 345;

            struct timespec bgn, end;
            clock_gettime( CLOCK_REALTIME, &bgn);
            double bgn_ns = (bgn.tv_sec*infinite) + bgn.tv_nsec;

            shmid = shmget(k,1024,IPC_CREAT | 0666);        

            if(shmid < 0 ){
                printf("Shared memory not created \n");
                exit(1);
            }
            
            shmptr = shmat(shmid, NULL, 0);        

            if( shmptr == (char *)-1){     
                printf("shared memory not attached ");
                int index = 0;
                exit(1);
            }

            temp = shmptr ; 

            int index = 0;
            int i=0;
            while(i< 10){
                int j=0;
                while(j< 5){
                    char *c = arr[index];
                    for(int k = 0; k< str_len; k++){

                         *temp = c[k];
                         temp++;
                }
                if(index <= 9){
                        char ch[2];                   
                        *temp = '0';
                        temp++;
                        *temp = ch[0];
                        temp++;
                }
                else{
                        char ch[2];                   
                        sprintf(ch, "%d", index);
                        *temp = ch[0];
                        temp++;
                        *temp = ch[1];
                        temp++;

                }
                    index++;
                    j++;
                }

                *temp = '&';

                while(*temp != '#'){
                    sleep(1);
                }
                sleep(1);
                printf("Received ID is : ");
                printf("%c",*temp);
                temp++;
                printf("%c\n",*temp);
             i++;
            }

            shmdt(shmptr);           
            shmctl(shmid,IPC_RMID, NULL);

            clock_gettime( CLOCK_REALTIME, &end);
            double end_ns = (end.tv_sec*infinite) + end.tv_nsec;
            t1 = end_ns - bgn_ns;
            printf("Shared memory : %f nanoseconds,%f seconds\n",t1,(t1/infinite));

}
