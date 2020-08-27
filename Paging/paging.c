#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 10

typedef struct Process{
    unsigned int pid;
    unsigned int pages[MAX];
    unsigned int n_pages;
}Process;


#include "Queue.h"

void allocate(Queue*, Queue*, Process*, int, int, int);
void deallocate(Queue*, Queue*, Process*, const int);
void pagetable(Process*, const int);

int main(){
    Process p[MAX];



    for(int i = 0; i < MAX; i++){
        p[i].pid = -1;
        p[i].n_pages=0;
    }

    Queue front = NULL,
          rear = NULL;

    int phy_mem = -1,
        frame_size = -1,
        choice = -1,
        no_frames = -1,
        pid = -1,
        mem_reqd = -1;

    printf(" Enter the Size of Physical Memory: ");
    scanf("%d", &phy_mem);
    printf(" Enter the Page Size: ");
    scanf("%d", &frame_size);

    no_frames = phy_mem / frame_size;

    for(int i = 0; i < 12; i++)
        enqueue(&front, &rear, (rand() % no_frames) +1);


    while(1){
        printf("\t\t\t\tPAGING TECHNIQUES\n");
        printf(" 1 - Process Request\n");
        printf(" 2 - De-Allocation\n");
        printf(" 3 - Page table for all input processes\n");
        printf(" 4 - Free Frame List\n");
        printf(" 0 - Exit\n");
        printf(" ------------------------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 0:
                exit(0);
            case 1:
                printf("\n Enter the PID of the Process & Memory Required: ");
                scanf("%d %d", &pid, &mem_reqd);
                allocate(&front, &rear, p, pid, mem_reqd, frame_size);
                break;
            case 2:
                printf("\n Enter the PID of Process to De-Allocate: ");
                scanf("%d", &pid);
                deallocate(&front, &rear, p, pid);
                break;
            case 3:
                for(int i = 0; i < MAX; i++)
                    pagetable(p, i);
                break;
            case 4:
                printf("\n The List of Free Frames:\n");
                display(front, rear);
                break;
            default:
                printf(" Invalid Input!\n");
                break;
        }
    }
}

void allocate(Queue *front, Queue *rear, Process *p, int pid, int mem_reqd, int page_size){
    int no_pages = mem_reqd / page_size;

    if(no_pages > size(*front, *rear)){
        printf(" Insufficient Memory!\n");
        return;
    }

    if(p[pid].pid != -1){
        printf(" Duplicate PID!\n");
        return;
    }

    printf("\n Process is divided into %d Pages", no_pages);
    p[pid].pid = pid;
    p[pid].n_pages = no_pages;

    for(int i = 0; i < no_pages; i++)
        p[pid].pages[i] = dequeue(front, rear);
    
    pagetable(p, pid);

    printf(" Successfully Allocated Pages!\n");
}

void deallocate(Queue *front, Queue *rear, Process *p, const int pid){
    if(!p[pid].n_pages){
        printf(" No Such Process exists!\n");
        return;
    }

    p[pid].pid = -1;
    int n_pages = p[pid].n_pages;
    p[pid].n_pages = 0;

    for(int i = 0; i < n_pages; i++)
        enqueue(front, rear, p[pid].pages[i]);

    printf(" Successfully De-Allocated Process!\n");
}

void pagetable(Process* p, const int pid){
    if(p[pid].n_pages == 0)
        return;
    
    printf("\n\n Page Table for Process %d\n", pid);
    for(int i = 0; i < p[pid].n_pages; i++)
        printf(" Page %-2d : Frame %-2d\n", i, p[pid].pages[i]);
    printf("\n");
}