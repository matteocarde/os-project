//
// Created by Matteo Cardellini on 17/04/18.
//

#include <stdlib.h>
#include "TaskControlBlock.h"


/**
 * Creates a new task with "NEW" as state and the following properties
 * @param {int} id              - The ID of the task to create
 * @param {int} arrival_time    - An integer number that describe at what clock cycle the task has to be considered by the scheduler
 * @return {TaskControlBlock}   - The newly created task
 */
TaskControlBlock *createTaskControlBlock(int id, int arrival_time) {

    TaskControlBlock *newTCB = malloc(sizeof(TaskControlBlock));
    InstructionList *instructionList = createInstructionList();

    newTCB->id = id;
    newTCB->arrival_time = arrival_time;
    newTCB->state = state_new;
    newTCB->instructionList = instructionList;

    return newTCB;
}