//
// Created by Matteo Cardellini on 17/04/18.
//

#include "TaskControlBlock.h"

#

#ifndef OS_PROJECT_TASKLIST_H
#define OS_PROJECT_TASKLIST_H

typedef struct {
    TaskControlBlock *head;
    TaskControlBlock *lastItem;
    int nOfElements;
} TaskList;

#endif //OS_PROJECT_TASKLIST_H
