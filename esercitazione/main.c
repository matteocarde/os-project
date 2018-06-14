#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_t *pNode;
typedef struct node_t {
    char *desc;
    pNode prev;
    pNode next;
} Node;


typedef struct queue_t *pQueue;
typedef struct queue_t {
    pNode first;
    pNode last;
} Queue;


void print_queue(pQueue p) {
    int i = 0;
    printf("v~~top\n");
    pNode tmp = p->first;
    while (NULL != tmp) {
        printf("%d: %s\n", ++i, tmp->desc);
        tmp = tmp->next;
    }
    printf("---bottom\n");
    i = 0;
    tmp = p->last;
    while (NULL != tmp) {
        printf("%d: %s\n", ++i, tmp->desc);
        tmp = tmp->prev;
    }
    printf("^~~top\n\n");
}


void insert_bottom(pQueue p, pNode n) {
    n->next = n->prev = NULL;
    if (NULL == p->first) {
        p->first = n;
        p->last = n;
        return;
    }
    p->last->next = n;
    n->prev = p->last;
    p->last = n;
}


pNode search_node_by_desc(pQueue p, char *desc) {
    pNode tmp = p->first;
    while (NULL != tmp) {
        if (strcmp(desc, tmp->desc) == 0) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


void delete_node(pQueue p, char *desc) {
    pNode del = search_node_by_desc(p, desc);
    if (NULL == del) return;
    //Migliorata la sintassi per vedere visivamente se la condizione viene eseguita
    if (del == p->first) {
        p->first = del->next;
    }
    if (del == p->last) {
        p->last = del->prev;
    }
    if (NULL != del->next) {
        del->next->prev = del->prev;
    }
    //BUG: Bisogna ricollegare il filo anche tra il nodo precedente e quello successivo
    if (NULL != del->prev) {
        del->prev->next = del->next;
    }

    free(del);
}


pNode create_node(char *desc) {
    pNode new_node = (pNode) malloc(sizeof(Node));
    //BUG: Non c'è bisogno di allocare anche lo spazio per la descrizione essa è già considerata in sizeof(Node)
    new_node->desc = desc;
    return new_node;
}


int main() {
    Queue queue;
    //BUG: La lista deve essere inizializzata
    queue.first = queue.last = NULL;

    insert_bottom(&queue, create_node("a1"));
    insert_bottom(&queue, create_node("b2"));
    insert_bottom(&queue, create_node("c3"));
    insert_bottom(&queue, create_node("d4"));
    insert_bottom(&queue, create_node("e5"));
    print_queue(&queue);

    delete_node(&queue, "e5");
    delete_node(&queue, "a1");
    print_queue(&queue);

    delete_node(&queue, "b2");
    delete_node(&queue, "c3");
    print_queue(&queue);

    delete_node(&queue, "d4");
    print_queue(&queue);

    return 0;
}
