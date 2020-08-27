#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float avg;
int max;
int min;

void *average(void *val)
{
    int sum = 0;
    int *ival = (int *)val;

    for (int i = 1; i <= ival[0]; i++)
    {
        sum += ival[i];
    }

    avg = sum / ival[0] ;
    pthread_exit(0);
}

void *maximum(void *val)
{
    int *ival = (int *)val;
    max = ival[1];
    for (int i = 1; i <= ival[0]; i++)
        if (max < ival[i])
            max = ival[i];

    pthread_exit(0);
}

void *minimum(void *val)
{
    int *ival = (int *)val;
    min = ival[1];
    for (int i = 1; i <= ival[0]; i++)
        if (min > ival[i])
            min = ival[i];

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2, thread3;
    pthread_attr_t attr;
    
    //Initialising with default attributes
    pthread_attr_init(&attr);

    if (argc < 2)
    {
        fprintf(stderr, "usage: ./exe-file <integer value>\n");
        return -1;
    }

    int *val = calloc(100, sizeof(int));
    
    //Storing No. of elements in the first index of array
    val[0] = argc - 1;

    for (int i = 1; i < argc; i++)
        val[i]= atoi(argv[i]);

    pthread_create(&thread1, &attr, average, val);
    pthread_create(&thread2, &attr, maximum, val);
    pthread_create(&thread3, &attr, minimum, val);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nAverage value is: %.3f\n", avg);
    printf("\nMaximum value is: %d\n", max);
    printf("\nMinimum value is: %d\n", min);

    free(val);
}

/*
OUTPUT

C:\Users\sreyas\Desktop\labs\OS\threads>gcc threads.c -o x -lpthread
C:\Users\sreyas\Desktop\labs\OS\threads>x 2 5 6 73 178 56 88 23 98

Average value is: 58.000

Maximum value is: 178

Minimum value is: 2

C:\Users\sreyas\Desktop\labs\OS\threads>
*/