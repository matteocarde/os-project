//
// Created by Matteo Cardellini on 10/06/18.
//

#include "../structures/TaskList.h"
#include "../structures/StateList.h"
#include "../structures/Instruction.h"
#include <stddef.h>
#include <printf.h>
#include <stdlib.h>

unsigned int pc = 0;


TaskControlBlock *selectionFunction(StateList *readyList) {
    return popFromStateList(readyList);
}

void tickAllBlockedTasks(StateList *blockedList, StateList *readyList) {

    StateListElement *currentElement = blockedList->front;

    while (currentElement != NULL) {
        TaskControlBlock *currentTask = currentElement->task;
        printf("\tTask #%d: Ha bisogno ancora di %d clock\n", currentTask->id, currentTask->pc->length);

        if (currentTask->pc->length == 1) {
            StateListElement *endedElement = currentElement;
            currentElement = (StateListElement *) endedElement->previous;
            removeFromList(blockedList, endedElement);
            pushToStateList(readyList, endedElement->task);
            printf("\tTask #%d: Terminato I/O\n", endedElement->task->id);
        } else {
            currentTask->pc->length--;
            currentElement = (StateListElement *) currentElement->previous;
        }
    }


}

int getRandomLenght(int maxLenght) {
    srand(time(NULL));
    return maxLenght;
    return rand() % maxLenght + 1; //TODO: Ricordati di rimuoverlo
}

void SchedulerNonPreemptive(TaskList *taskList) {

    TaskControlBlock *nextTaskToArrive = taskList->head;
    TaskControlBlock *runningTask = NULL;
    Instruction *currentInstruction = NULL;

    StateList *readyList = createStateList();
    StateList *blockedList = createStateList();

    while (pc < 100) { //TODO: SAFE. Remember to remove it

        //TODO: Guardare il caso in cui due task arrivano assieme

        pc++; //TODO: Magari mettilo in fondo ?
        printf("PC #%d\n", pc);

        if (nextTaskToArrive != NULL && nextTaskToArrive->arrival_time == pc) {
            changeTaskState(nextTaskToArrive, state_ready);
            pushToStateList(readyList, nextTaskToArrive);
            nextTaskToArrive = (TaskControlBlock *) nextTaskToArrive->next;
        }

        tickAllBlockedTasks(blockedList, readyList);

        if (readyList->nOfElements == 0 && blockedList->nOfElements == 0 && nextTaskToArrive == NULL &&
            runningTask == NULL) {
            break;
        }


        if (runningTask == NULL) {
            runningTask = selectionFunction(readyList);

            if (runningTask == NULL) {
                continue;
            }

            if (runningTask->pc == NULL) {
                currentInstruction = runningTask->instructionList->head;
            } else {
                if (runningTask->pc->next == NULL) {
                    changeTaskState(runningTask, state_exit);
                    runningTask = NULL;
                    continue;
                } else {
                    currentInstruction = (Instruction *) runningTask->pc->next;
                }
            }
        }

        currentInstruction->length--;
        runningTask->pc = currentInstruction;

        if (currentInstruction->type_flag == nonBlocking) {

            if (runningTask->state != state_running) {
                changeTaskState(runningTask, state_running);
            }

            if (currentInstruction->length > 0) {
                printf("\tTask #%d: Eseguo calcolo\n", runningTask->id);
                continue;
            }

            if (currentInstruction->next != NULL) {
                printf("\tTask #%d: Nuova istruzione\n", runningTask->id);
                currentInstruction = (Instruction *) currentInstruction->next;
            } else {
                printf("\tTask #%d: Terminato\n", runningTask->id);
                currentInstruction = NULL;
                runningTask = NULL;
            }
            continue;
        }

        if (currentInstruction->type_flag == blocking) {
            srand(time(NULL));
            currentInstruction->length = getRandomLenght(currentInstruction->length);
            changeTaskState(runningTask, state_blocked);
            pushToStateList(blockedList, runningTask);
            runningTask = NULL;
            currentInstruction = NULL;
        }


    }

    printf("END\n");
}

