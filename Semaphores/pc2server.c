/*
Assignment 2:
Modify the program as separate client / server process programs to generate ‘N’ random
numbers in producer and write them into shared memory. Consumer process should read
them from shared memory and display them in terminal


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
void produce(int n);
int segid; /* id for shared memory bufer */
int empty_id;
int full_id;
int mutex_id;
char * buff;
char * input_string;
sem_t *empty;
sem_t *full;
sem_t *mutex;
int p=0;
int main()
{

	int i=0; 

	pid_t temp_pid;
	int bufid,empid,fullid,mutid;//shared memory for buffer, semaphores
	char *n;
	int nid;
	nid=shmget(300,1,IPC_CREAT | 00666);
	n=shmat(nid,NULL,0);

	int inn;
	bufid=shmget(100,10,IPC_CREAT | 00666);
	empid=shmget(150,50,IPC_CREAT | 00666);
	fullid=shmget(200,50,IPC_CREAT | 00666);
	mutid=shmget(250,50,IPC_CREAT | 00666);
	buff = shmat(bufid,NULL,0); 
	empty = shmat(empid,NULL,0); 
	full = shmat(fullid,NULL,0); 
	mutex = shmat(mutid,NULL,0); 
	// Initializing Semaphores Empty , Full & Mutex
	if(n[1]!=1)
	{
		sem_init(empty,1,10);//shared buffer size initialized to the semaphore
		sem_init(full,1,0);
		sem_init(mutex,1,1);
		n[1]=1;
	}

	printf("Enter the value of n: ");
	scanf("%d",&inn);
	n[0]=inn;
	produce(n[0]);
	shmdt(buff);
	shmdt(empty);
	shmdt(full);
	shmdt(mutex);
	shmctl(bufid, IPC_RMID,NULL);
	shmctl(nid, IPC_RMID,NULL);
	shmctl(empid, IPC_RMID,NULL);
	shmctl(fullid, IPC_RMID,NULL);
	shmctl(mutid, IPC_RMID,NULL);
	sem_destroy(empty);
	sem_destroy(full);
	sem_destroy(mutex);
	return(0);
} 
void produce(int n)
{

	while (1)
	{
		if(p>=n)
		{
			printf("\n Producer exited \n");
			exit(1);
		}
		sem_wait(empty);
		sem_wait(mutex);
		buff[p]=rand();//add next produced to buffer
		printf("produced: %d\n\n",buff[p]);
		p++;
		sem_post(mutex);
		sem_post(full);
		sleep(1);
	} 
}

/*
OUTPUT

Enter the value of n: 5
produced: 103

produced: -58

produced: 105

produced: 115

produced: 81


 Producer exited 
 */
