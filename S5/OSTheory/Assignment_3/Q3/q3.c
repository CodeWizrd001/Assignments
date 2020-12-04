#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define n 5 

int state[n]; 
int phil[n] = { 0, 1, 2, 3, 4 }; 

sem_t mutex; 
sem_t S[n]; 

int left(int i) 
{
    return (i + 4) % n  ;
}

int right(int i) 
{
    return (i + 1) % n  ;
}
  
void test(int phnum) 
{ 
    if (state[phnum]==HUNGRY && state[left(phnum)]!=EATING && state[right(phnum)]!=EATING) 
    {
        state[phnum] = EATING; 
        sleep(2); 
        printf("Philosopher %d takes fork %d and %d\n", 
                      phnum + 1, left(phnum) + 1, phnum + 1); 
        printf("Philosopher %d is Eating\n", phnum + 1); 
        sem_post(&S[phnum]); 
    } 
} 

void take_fork(int phnum) 
{ 
    sem_wait(&mutex); 
    state[phnum] = HUNGRY; 
    printf("Philosopher %d is Hungry\n", phnum + 1); 
    test(phnum); 
    sem_post(&mutex); 
    sem_wait(&S[phnum]); 
    sleep(1); 
} 

void put_fork(int phnum) 
{
    sem_wait(&mutex); 
    state[phnum] = THINKING; 
    printf("Philosopher %d putting fork %d and %d down\n",phnum + 1, left(phnum) + 1, phnum + 1); 
    printf("Philosopher %d is thinking\n", phnum + 1); 
    test(left(phnum)); 
    test(right(phnum)); 
    sem_post(&mutex); 
} 
  
void* philospher(void* num) 
{
    while (1) { 
        int* i = num; 
        sleep(1); 
        take_fork(*i); 
        sleep(0); 
        put_fork(*i); 
    } 
} 

int main() 
{ 
    int i; 
    pthread_t thread_id[n]; 
    sem_init(&mutex, 0, 1); 
    for (i = 0; i < n; i++) 
        sem_init(&S[i], 0, 0); 

    for (i = 0; i < n; i++) 
    { 

        pthread_create(&thread_id[i], NULL,philospher,&phil[i]); 
        printf("Philosopher %d is thinking\n", i + 1); 
    }
    for (i = 0; i < n; i++) 
        pthread_join(thread_id[i], NULL); 
}
