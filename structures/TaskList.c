//
// Created by Matteo Cardellini on 17/04/18.
//

#include "TaskControlBlock.h"
#include "TaskList.h"
#include <stdlib.h>

/**
 * addTaskToList     - Adds a TaskControlBlock to the TaskList
 * @param list       - The list to add the TCB to
 * @param task       - The TaskControlBlock that will be inserted into the TaskList
 */
void addTaskToList(TaskList *list, TaskControlBlock *task) {

    if (list->head == NULL) {
        list->head = task;
    } else {
        list->lastItem->next = task;
    }
    list->lastItem = task;
    list->nOfElements++;
}

/**
 * createTaskList   - Initialize a new TaskList
 * @return          - The newly created TaskList
 */
TaskList *createTaskList() {
    TaskList *newTaskList = malloc(sizeof(TaskList));
    newTaskList->head = NULL;
    newTaskList->nOfElements = 0;
    newTaskList->lastItem = NULL;
    return newTaskList;
}
