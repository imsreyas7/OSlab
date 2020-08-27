typedef Block Data;

typedef struct Node
{
    Data d;
    struct Node *next;
} Node;

typedef Node *List;

extern void init_block(Block *const);

List createEmptyList()
{
    Node *head = (Node *)malloc(sizeof(Node));
    init_block(&(head -> d));
    head->next = NULL;
    return head;
}

void insertLast(List head, const Data d)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->d = d;
    Node *tmp = head;

    while (tmp->next)
        tmp = tmp->next;

    new->next = NULL;
    tmp->next = new;
}

void insertFirst(List head, const Data d)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->d = d;

    new->next = head->next;
    head->next = new;
}

Data delete (List prev)
{
    Data rVal;
    if (!prev)
        return rVal;
    if (!prev->next)
        return rVal;

    Node *tmp = prev->next;
    rVal = tmp->d;
    prev->next = prev->next->next;
    free(tmp);

    return rVal;
}

Data deleteFirst(List head)
{
    Data rVal;
    if (head->next == NULL)
    {
        printf(" Empty List!\n");
        return rVal;
    }

    delete (head);
}

Data deleteLast(List head)
{
    Data rVal;
    if (head->next == NULL)
    {
        printf(" Empty List!\n");
        return rVal;
    }

    Node *tmp = head;
    while (tmp->next->next != NULL)
        tmp = tmp->next;

    delete (tmp);
}

void display(List head)
{
    Node *tmp = head->next;

    if (tmp == NULL)
    {
        printf(" Empty!\n");
        return;
    }

    while (tmp)
    {
        printf(" BID: %-2d\tStatus: %d\n", tmp->d.id, tmp->d.status);
        tmp = tmp->next;
    }
}

int length(List head)
{
    Node *tmp = head->next;
    if (tmp == NULL)
        return 0;

    int count = 0;
    while (tmp)
    {
        tmp = tmp->next;
        count++;
    }
    return count;
}

Node* search(List head, const int id)
{
    
    if (head->next == NULL)
        return NULL;

    Node *tmp = head -> next;
    while (tmp)
    {
        if (tmp->d.id == id)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}
