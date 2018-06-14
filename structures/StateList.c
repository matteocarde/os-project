//
// Created by Matteo Cardellini on 10/06/18.
//

#include <stdlib.h>
#include "StateList.h"


StateList *createStateList() {
    StateList *newList = malloc(sizeof(StateList));
    newList->front = NULL;
    newList->back = NULL;
    newList->nOfElements = 0;
    return newList;
}

void pushToStateList(StateList *list, TaskControlBlock *task) {
    StateListElement *newElement = malloc(sizeof(StateListElement));
    newElement->next = NULL;
    newElement->previous = NULL;
    newElement->task = task;

    if (list->nOfElements == 0) {
        list->front = newElement;
        list->back = newElement;
    } else {
        newElement->next = list->back;
        list->back->previous = newElement;
        list->back = newElement;

    }
    list->nOfElements++;

}

TaskControlBlock *popFromStateList(StateList *list) {

    if (list->nOfElements == 0) {
        return NULL;
    }

    StateListElement *poppedElement = list->front;
    TaskControlBlock *poppedTask = poppedElement->task;

    list->front = (StateListElement *) list->front->previous;
    list->nOfElements--;
    free(poppedElement);


    return poppedTask;
}


void removeFromList(StateList *list, StateListElement *element) {

    if (list->front == element) {
        if (element->previous != NULL) {
            list->front = (StateListElement *) element->previous;
            ((StateListElement *) element->previous)->next = NULL;
        } else {
            list->front = NULL;
        }
    }

    if (list->back == element) {
        if (element->next != NULL) {
            list->back = (StateListElement *) element->next;
            ((StateListElement *) element->next)->previous = NULL;
        } else {
            list->back = NULL;
        }
    }

    if (element->next != NULL && element->previous != NULL) {
        ((StateListElement *) element->previous)->next = element->next;
        ((StateListElement *) element->next)->previous = element->previous;
    }


    list->nOfElements--;

    free(element);
}
