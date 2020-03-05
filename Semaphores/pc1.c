/*
Assignment 1:
Aim:
To write a C program to create parent/child processes to implement the producer/consumer
problem using semaphores in pthread library.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h> // for semaphore operations sem_init,sem_wait,sem_post
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
extern int errno;
#define BUF_SIZE 8192
int segid; /* id for shared memory bufer */
int empty_id;
int full_id;
int mutex_id;
char * buff;
char * input_string;
sem_t *empty;
sem_t *full;
sem_t *mutex;
int p=0,c=0;

void produce()
{

	while (1)
	{
		if(p>=strlen(input_string))
		{
			printf("\n Producer exited \n");
			exit(1);
		}
		sem_wait(empty);
		sem_wait(mutex);
		buff[p]=input_string[p];//add next produced to buffer
		printf("produced: %c\n\n",buff[p]);
		p++;
		sem_post(mutex);
		sem_post(full);
		sleep(1);
	} 
}
void consume()
{
	while (1)
	{
		if(c>=strlen(input_string))
		{
			printf("\n Consumer exited \n");
			exit(1);
		}
		sem_wait(full);
		sem_wait(mutex);
		printf("consumed %c\n\n",buff[c]);//consumer consumes
		c++;
		sem_post(mutex);
		sem_post(empty);
		sleep(1);
	} 
} 

int main()
{
	int i=0; 

	pid_t temp_pid;
	int bufid,empid,fullid,mutid;//shared memory for buffer, semaphores
	bufid=shmget(100,10,IPC_CREAT | 00666);
	empid=shmget(150,50,IPC_CREAT | 00666);
	fullid=shmget(200,50,IPC_CREAT | 00666);
	mutid=shmget(250,50,IPC_CREAT | 00666);
	buff = shmat(bufid,NULL,0); 
	empty = shmat(empid,NULL,0); 
	full = shmat(fullid,NULL,0); 
	mutex = shmat(mutid,NULL,0); 
	// Initializing Semaphores Empty , Full & Mutex
	sem_init(empty,1,10);//shared buffer size initialized to the semaphore
	sem_init(full,1,0);
	sem_init(mutex,1,1);
	printf("\n Enter the input string  : ");
	input_string=(char *)malloc(20);
	scanf("%s",input_string);
	temp_pid=fork();
	if(temp_pid>0) //parent
	{
		produce();
	}
	else //child
	{ 
		consume();
	}
	shmdt(buff);
	shmdt(empty);
	shmdt(full);
	shmdt(mutex);
	shmctl(bufid, IPC_RMID,NULL);
	shmctl(empid, IPC_RMID,NULL);
	shmctl(fullid, IPC_RMID,NULL);
	shmctl(mutid, IPC_RMID,NULL);
	sem_destroy(empty);
	sem_destroy(full);
	sem_destroy(mutex);
	return(0);
} 

/*
OUTPUT


Enter the input string  : semaphores
produced: s

consumed s

produced: e

consumed e

produced: m

consumed m

produced: a

consumed a

produced: p

consumed p

produced: h

consumed h

produced: o

consumed o

produced: r

consumed r

produced: e

consumed e

produced: s

consumed s


 Producer exited 

 Consumer exited 
*/
