





#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
	char *a;
	int fd;
	int id = shmget(121, 50, IPC_CREAT);
	a = shmat(id, NULL, 0);
	while(a[0] == '\0');
	fd = open(a, O_RDONLY);
	a[0] = '\0';
	if(fd < 0) {
		strcpy(a, "Does not exist!\n");
		shmdt(a);
		exit(0);
	}
	char r; int i = 0;
	while((read(fd, &r, 1)))
	{
		a[i] = r;
		i++;
	}
	printf("Read!\n");
	shmdt(a);
	shmctl(id, IPC_RMID, NULL);
}