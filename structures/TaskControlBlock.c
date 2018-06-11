//
// Created by Matteo Cardellini on 17/04/18.
//

#include <stdlib.h>
#include <printf.h>
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
    newTCB->next = NULL;
    newTCB->blockingInstruction = NULL;

    return newTCB;
}

char *getStateName(enum task_state state) {
    switch (state) {
        case state_new :
            return "new";
        case state_ready :
            return "ready";
        case state_running :
            return "running";
        case state_blocked :
            return "blocked";
        case state_exit:
            return "exit";
    }
}

void changeStateToTask(TaskControlBlock *task, enum task_state state) {
    //TODO: Print into log file status change
    fprintf(stdout, "Task #%d è passata nello stato %s\n", task->id, getStateName(state));
    task->state = state;
}
