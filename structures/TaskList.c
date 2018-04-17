//
// Created by Matteo Cardellini on 17/04/18.
//

#include <stdlib.h>
#include "TaskControlBlock.h";
#include "TaskList.h"

TaskList *addTask(TaskList list, TaskControlBlock *task) {

    if (list.nOfElements == 0) {
        list.head = task;
    } else {
        list.lastItem->next = task;
    }
    list.nOfElements++;
}