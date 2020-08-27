typedef int Data;

typedef struct Node{
    Data d;
    struct Node *next;
}Node;

typedef Node* Queue;

int isEmpty(Queue front, Queue rear){
    if (front == NULL)
        return 1;
    return 0;
}

int size(Queue front, Queue rear){
    if(isEmpty(front, rear))
        return 0;
    int c = 0;
    Node *tmp = front;
    while(tmp){
        tmp = tmp -> next;
        c++;
    }
    return c;
}

void enqueue(Queue *front, Queue *rear, const Data d){
    Node* new = (Node*)malloc(sizeof(Node));
    new -> d = d;
    new -> next = NULL;

    if(isEmpty(*front, *rear))
        (*front) = (*rear) = new;
    else{
        (*rear) -> next = new;
        (*rear) = new;
    }
}

Data dequeue(Queue *front, Queue *rear){
    Data rVal =0;
    if(isEmpty(*front, *rear))
        return rVal;

    Node *tmp = (*front);
    rVal = (*front) -> d;

    if (*front == *rear)
        (*rear) = NULL;

    (*front) = (*front) -> next;
    free(tmp);
    return rVal;
}

void display(Queue front, Queue rear){
    if(isEmpty(front, rear)){
        printf(" Empty Queue!\n");
        return;
    }
    
    Queue tmp = front;
    while(tmp){
        printf("% d", tmp -> d);
        tmp = tmp -> next;
    }
    printf("\n");
}