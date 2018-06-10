//
// Created by Matteo Cardellini on 10/06/18.
//

#include "TaskControlBlock.h"

#ifndef OS_PROJECT_STATEQUEUE_H
#define OS_PROJECT_STATEQUEUE_H

#endif //OS_PROJECT_STATEQUEUE_H

typedef struct {
    TaskControlBlock *task;
    struct StateListElement *next;
    struct StateListElement *previous;
} StateListElement;

typedef struct {
    StateListElement *front;
    StateListElement *back;
    int nOfElements;
} StateList;


void pushToStateList(StateList *queue, TaskControlBlock *task);

TaskControlBlock *popFromStateList(StateList *queue);

void removeFromList(StateList *list, StateListElement *element);

StateList *createStateList();