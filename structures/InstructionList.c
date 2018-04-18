//
// Created by Matteo Cardellini on 17/04/18.
//

#include <stdlib.h>
#include "Instruction.h";
#include "InstructionsList.h"


/**
 * addInstructionToList             - Creates an instruction with the blockingFlag and length specified and adds it to the passed InstructionList
 * @param {InstructionList*} list   - The list to add the instruction to
 * @param {blockingFlag} flag       - The blockingFlag of the instruction
 * @param {int} length              - The length of the instruction
 * @return {Instruction *}          - The created Instruction
 */
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

/**
 * createInstructionList        - Creates a new InstructionList
 * @return {InstructionList*}   - The newly created InstructionList
 */
InstructionList *createInstructionList() {
    InstructionList *newList = malloc(sizeof(InstructionList));
    newList->nOfElements = 0;
    newList->head = NULL;
    newList->lastItem = NULL;

    return newList;
}
