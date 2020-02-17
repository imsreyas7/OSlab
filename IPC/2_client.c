#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
  int id;
  char *a;
  id = shmget(121, 50, IPC_CREAT | 00666);
  a = shmat(id, NULL, 0);
  a[0] = '\0';
  printf("Enter file name: ");
  scanf("%s", a);
  sleep(1);
  while(a[0] == '\0');
  printf("%s", a);
  shmdt(a);
  shmctl(id, IPC_RMID, NULL);
  return 0;
}
