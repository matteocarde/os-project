//
// Created by Matteo Cardellini on 17/04/18.
//

#include <stdlib.h>
#include "Instruction.h";
#include "InstructionsList.h"

Instruction *addInstructionToList(InstructionList *list, enum blockingFlag flag, int length) {

    Instruction *newNode = malloc(sizeof(Instruction));
    newNode->next = NULL;
    newNode->type_flag = flag;
    newNode->length = length;

    if (list->nOfElements == 0) {
        list->head = newNode;
    } else {
        list->lastItem->next = newNode;
    }
    list->lastItem = newNode;
    list->nOfElements++;

    return newNode;
}


InstructionList *createInstructionList() {
    InstructionList *newList = malloc(sizeof(InstructionList));
    newList->nOfElements = 0;
    newList->head = NULL;
    newList->lastItem = NULL;

    return newList;
}
