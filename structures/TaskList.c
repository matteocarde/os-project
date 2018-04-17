//
// Created by Matteo Cardellini on 17/04/18.
//

#include "TaskControlBlock.h";
#include "TaskList.h"
#include <stddef.h>
#include <stdlib.h>

void addTaskToList(TaskList *list, TaskControlBlock *task) {

    if (list->head == NULL) {
        list->head = task;
    } else {
        list->lastItem->next = task;
    }
    list->lastItem = task;
    list->nOfElements++;
}


TaskList *createTaskList() {
    TaskList *newTaskList = malloc(sizeof(TaskList));
    newTaskList->head = NULL;
    newTaskList->nOfElements = 0;
    newTaskList->lastItem = NULL;
    return newTaskList;
}
