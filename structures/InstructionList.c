//
// Created by Matteo Cardellini on 17/04/18.
//

#include <stdlib.h>
#include "Instruction.h";
#include "InstructionsList.h"

Instruction *addInstruction(InstructionList list, enum blockingFlag flag, int length) {

    Instruction *newNode = malloc(sizeof(Instruction));
    newNode->next = NULL;
    newNode->type_flag = flag;
    newNode->length = length;

    if (list.nOfElements == 0) {
        list.head = newNode;
    } else {
        list.lastItem->next = newNode;
    }
    list.nOfElements++;

    return newNode;
}