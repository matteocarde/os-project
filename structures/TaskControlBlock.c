//
// Created by Matteo Cardellini on 17/04/18.
//

#include <stdlib.h>
#include "TaskControlBlock.h"

TaskControlBlock *createTaskControlBlock(int id, int pc, int arrival_time) {

    TaskControlBlock *newTCB = malloc(sizeof(TaskControlBlock));
    InstructionList *instructionList = malloc(sizeof(InstructionList));

    newTCB->id = id;
    newTCB->pc = pc;
    newTCB->arrival_time = arrival_time;
    newTCB->state = new;
    newTCB->instructionList = instructionList;

    return newTCB;
}