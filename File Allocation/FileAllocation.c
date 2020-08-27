#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100
#define FREE 0

typedef struct File
{
    char name[21];
    int size;
    int start_block;
    int end_block;
    int *indices;
    int length;
} File;

void init_file(File *const);

typedef struct Directory
{
    File f[MAX];
    int size;
} Directory;

void init_dir(Directory *const);

typedef struct Block
{
    int id;
    unsigned status : 1;
    struct Block *next_file_blk;
} Block;

void init_block(Block *const);

#include "LinkedList.h"

void contiguous(File *const, const int, const int, const int);
void linked(File *const, const int, const int, const int);
void indexed(File *const, const int, const int, const int);

int main()
{
    int mem_size;
    int blk_size;
    int num_blks;
    int num_file;
    int choice;

    File f[MAX];

    printf(" Enter the size of memory: ");
    scanf("%d", &mem_size);
    printf(" Enter the size of block: ");
    scanf("%d", &blk_size);
    num_blks = mem_size / blk_size;

    printf(" Enter the number of files: ");
    scanf("%d", &num_file);
    getchar();

    for (int i = 0; i < num_file; i++)
    {
        printf(" Enter the name of file: ");
        scanf("%[^\n]", f[i].name);

        printf(" Enter the size of file: ");
        scanf("%d", &f[i].size);
        getchar();
    }

    while (1)
    {
        printf("\t\t\tFILE ALLOCATION TECHNIQUES\n");
        printf(" 1 - Contiguous\n");
        printf(" 2 - Linked\n");
        printf(" 3 - Indexed\n");
        printf(" 0 - Exit\n");
        printf(" ----------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            exit(0);
        case 1:
            contiguous(f, num_file, blk_size, num_blks);
            break;
        case 2:
            linked(f, num_file, blk_size, num_blks);
            break;
        case 3:
            indexed(f, num_file, blk_size, num_blks);
            break;

        default:
            printf(" Invalid Input!\n");
        }
    }
}

void init_file(File *const f)
{
    strcpy(f->name, "");
    f->start_block = -1;
    f->end_block = -1;
    f->size = -1;
    f->indices = NULL;
    f->length = -1;
}

void init_dir(Directory *const d)
{
    d->size = 0;
    for (int i = 0; i < MAX; i++)
        init_file(&(d->f[i]));
}

void init_block(Block *const b)
{
    b->status = FREE;
    b->id = -1;
    b->next_file_blk = NULL;
}

void contiguous(File *const f, const int n_files, const int blk_size, const int num_blk)
{
    List list = createEmptyList();

    Block b;
    init_block(&b);

    Node *ptr, *tmp;

    int blocks_visited, flag, id, counter, blk_req;
    int start, end;

    for (int i = 0; i < num_blk; i++)
    {
        b.id = i;
        insertLast(list, b);
    }

    for (int i = 0; i < n_files; i++)
    {
        blocks_visited = 0;
        flag = 0;
        blk_req = f[i].size / blk_size;
        if (f[i].size % blk_size)
            blk_req++;

        while (blocks_visited < num_blk && !flag)
        {
            id = rand() % num_blk;
            ptr = search(list, id);
            if (ptr->d.status != FREE)
            {
                blocks_visited++;
                continue;
            }

            counter = 0;

            start = ptr->d.id;

            tmp = ptr;
            while (tmp)
            {
                if (tmp->d.status == FREE)
                {
                    counter++;
                    if (counter == blk_req)
                    {
                        flag = 1;
                        break;
                    }
                }
                else
                    break;
                tmp = tmp->next;
            }

            if (flag)
            {
                f[i].start_block = start;
                f[i].length = blk_req;
                tmp = ptr;
                for (int i = 0; i < blk_req; i++)
                {
                    tmp->d.status = 1;
                    tmp = tmp->next;
                }
            }
            else
                blocks_visited++;
        }
        if (!flag)
            printf(" Unable to allocate file: %s\n!", f[i].name);
    }

    printf("\n\t\tDIRECTORY STRUCTURE\n");
    printf(" +----------------------+-------+--------+\n");
    printf(" |      File Name       | Start | Length |\n");
    printf(" +----------------------+-------+--------+\n");

    for (int i = 0; i < n_files; i++)
        if (f[i].length > 0)
            printf(" | %-20s | %-5d | %-6d |\n", f[i].name, f[i].start_block, f[i].length);
    printf(" +----------------------+-------+--------+\n");
}
void linked(File *const f, const int n_files, const int blk_size, const int num_blk)
{
    List list = createEmptyList();

    Block b;
    init_block(&b);

    Node *ptr, *tmp, *left, *right;

    int blocks_visited, flag, id, counter, blk_req;

    for (int i = 0; i < num_blk; i++)
    {
        b.id = i;
        insertLast(list, b);
    }

    for (int i = 0; i < n_files; i++)
    {
        counter = 0;
        blocks_visited = 0;
        flag = 0;
        blk_req = f[i].size / blk_size;
        if (f[i].size % blk_size)
            blk_req++;
        int *allocated = (int *)calloc(blk_req, sizeof(int));

        while (blocks_visited < num_blk && !flag)
        {
            id = rand() % num_blk;
            ptr = search(list, id);

            if (ptr->d.status != FREE)
            {
                blocks_visited++;
                continue;
            }
            ptr -> d.status = 1;
            allocated[counter++] = id;

            if (counter == blk_req)
                flag = 1;
        }
        if (!flag){
            printf(" Unable to allocate file: %s\n", f[i].name);
            for(int i = 0; i < counter; i++){
                ptr = search(list, allocated[i]);
                ptr -> d.status = FREE;
            }
            free(allocated);
        }
        else
        {

            f[i].start_block = allocated[0];
            f[i].end_block = allocated[blk_req - 1];
            f[i].length = blk_req;
            for (int i = 0; i < blk_req - 1; i++)
            {

                left = search(list, allocated[i]);
                right = search(list, allocated[i + 1]);
                left->d.next_file_blk = &(right->d);
                left->d.status = 1;
            }
            right->d.next_file_blk = NULL;
            free(allocated);
        }
    }
    printf("\n\t\tDIRECTORY STRUCTURE\n");
    printf(" +----------------------+-------------+-----------+\n");
    printf(" |      File Name       | Start Block | End Block |\n");
    printf(" +----------------------+-------------+-----------+\n");
    for (int i = 0; i < n_files; i++)
        if (f[i].end_block >= 0)
            printf(" | %-20s |     %-2d      |    %-2d     |\n",
                   f[i].name, f[i].start_block, f[i].end_block);
    printf(" +----------------------+-------------+-----------+\n");

    printf("\n");
    for (int i = 0; i < n_files; i++)

        if (f[i].start_block >= 0)
        {
            printf("\n\n File Name: %s\n ",f[i].name);
            ptr = search(list, f[i].start_block);
            Block *b = &(ptr->d);
            while (b)
            {
                printf("%-2d ", b->id);
                b = b->next_file_blk;
            }
        }
}
void indexed(File *const f, const int n_files, const int blk_size, const int num_blk)
{
    List list = createEmptyList();

    Block b;
    init_block(&b);

    Node *ptr, *tmp;

    int blocks_visited, flag, id, counter, blk_req;
    int start, end;

    for (int i = 0; i < num_blk; i++)
    {
        b.id = i;
        insertLast(list, b);
    }

    for (int i = 0; i < n_files; i++)
    {
        blocks_visited = 0;
        flag = 0;
        blk_req = f[i].size / blk_size;
        if (f[i].size % blk_size)
            blk_req++;
        f[i].indices = (int *)calloc(blk_req + 1, sizeof(int));
        f[i].length = blk_req;
        counter = 0;
        while (blocks_visited < num_blk && !flag)
        {
            id = rand() % num_blk;
            ptr = search(list, id);
            if (ptr->d.status == FREE)
            {
                f[i].indices[counter++] = id;
                if (counter == blk_req + 1)
                {
                    flag = 1;
                    break;
                }
            }
            else
                blocks_visited++;
        }
        if (!flag)
        {
            printf(" Unable to allocate memory for file: %s\n", f[i].name);
            free(f[i].indices);
            f[i].indices = NULL;
        }
    }
    printf("\n\t\tDIRECTORY STRUCTURE\n");
    printf(" +----------------------+-------------+\n");
    printf(" |      File Name       | Index Block |\n");
    printf(" +----------------------+-------------+\n");
    for (int i = 0; i < n_files; i++)
        if (f[i].indices)
            printf(" | %-20s |     %-2d      |\n", f[i].name, f[i].indices[0]);
    printf(" +----------------------+-------------+\n");

    printf("\n\n");
    printf(" +----------------------+----------------+\n");
    printf(" |      File Name       | Blocks Indexed |\n");
    printf(" +----------------------+----------------+\n");
    for (int i = 0; i < n_files; i++)
    {
        if (f[i].indices)
        {
            for (int j = 1; j <= f[i].length; j++)
                printf(" | %-20s |       %-2d       |\n", ((j > 1) ? "" : f[i].name), f[i].indices[j]);
        }
        printf(" +----------------------+----------------+\n");
    }
}