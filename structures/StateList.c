//
// Created by Matteo Cardellini on 10/06/18.
//

#include <MacTypes.h>
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
        newElement->previous = list->back;
        list->back->next = newElement;
        list->back = newElement;

    }
    list->nOfElements++;

}


TaskControlBlock *popFromStateList(StateList *list) {

    if (list->nOfElements == 0) {
        return NULL;
    }

    StateListElement *poppedElement = list->back;
    TaskControlBlock *poppedTask = poppedElement->task;

    list->back = (StateListElement *) list->back->previous;
    list->nOfElements--;
    free(poppedElement);


    return poppedTask;
}


void removeFromList(StateList *list, StateListElement *element) {

    if (element->next != NULL) {
        element->next = element->previous;
    }

    if (element->previous != NULL) {
        element->previous = element->next;
    }

    if (list->front == element) {
        list->front = (StateListElement *) element->next;
    }

    if (list->back == element) {
        list->back = (StateListElement *) element->previous;
    }

    list->nOfElements--;

    free(element);
}
