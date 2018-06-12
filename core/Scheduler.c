//
// Created by Matteo Cardellini on 10/06/18.
//

#include "../structures/TaskList.h"
#include "../structures/StateList.h"
#include "../utilities/utilities.h"
#include "../structures/TaskControlBlock.h"
#include <stddef.h>
#include <printf.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>


//SPN: Shortest Process Time
TaskControlBlock *selectionFunctionSPN(StateList *readyList) {
    StateListElement *currentElement = readyList->front;
    StateListElement *selectedElement = NULL;
    if (currentElement == NULL) {
        return NULL;
    }
    int minProcessTime = currentElement->task->process_time;
    while (currentElement != NULL) {
        int currentTaskProcessTime = currentElement->task->process_time;
        if (currentTaskProcessTime <= minProcessTime) {
            minProcessTime = currentTaskProcessTime;
            selectedElement = currentElement;
        }
        currentElement = (StateListElement *) currentElement->previous;
    }
    removeFromList(readyList, selectedElement);
    return selectedElement->task;
}


//SRT: Shortest Remaining Time
TaskControlBlock *selectionFunctionSRT(StateList *readyList) {
    StateListElement *currentElement = readyList->front;
    StateListElement *selectedElement = NULL;
    if (currentElement == NULL) {
        return NULL;
    }
    int minRemainingTime = currentElement->task->process_time - currentElement->task->execution_time;
    while (currentElement != NULL) {
        int currentTaskRemainingTime = currentElement->task->process_time - currentElement->task->execution_time;
        if (currentTaskRemainingTime <= minRemainingTime) {
            minRemainingTime = currentTaskRemainingTime;
            selectedElement = currentElement;
        }
        currentElement = (StateListElement *) currentElement->previous;
    }
    removeFromList(readyList, selectedElement);
    return selectedElement->task;
}


void tickAllBlockedTasks(StateList *blockedList, StateList *readyList) {

    StateListElement *currentElement = blockedList->front;

    while (currentElement != NULL) {
        TaskControlBlock *currentTask = currentElement->task;
        printf("\tTask #%d: Ha bisogno ancora di %d clock\n", currentTask->id, currentTask->pc->length);

        currentTask->pc->length--;
        if (currentTask->pc->length == 0) {
            StateListElement *endedElement = currentElement;
            currentElement = (StateListElement *) endedElement->previous;
            removeFromList(blockedList, endedElement);
            pushToStateList(readyList, endedElement->task);
            printf("\tTask #%d: Terminato I/O\n", endedElement->task->id);
        } else {
            currentElement = (StateListElement *) currentElement->previous;
        }
    }


}

int getRandomLenght(int maxLenght) {
    srand((unsigned int) time(NULL));
    return maxLenght;
    return rand() % maxLenght + 1; //TODO: Ricordati di rimuoverlo
}

void Scheduler(threadArgs_t *threadArgs) {

    unsigned int pc = 0;

    TaskControlBlock *nextTaskToArrive = threadArgs->taskList->head;
    TaskControlBlock *runningTask = NULL;
    Instruction *currentInstruction = NULL;

    StateList *readyList = createStateList();
    StateList *blockedList = createStateList();

    while (pc < 100) { //TODO: SAFE. Remember to remove it

//        printf("Core#%d - PC #%d\n", threadArgs->threadId, pc);

        FETCH:
        while (nextTaskToArrive != NULL && nextTaskToArrive->arrival_time <= pc) {

            pthread_mutex_lock(threadArgs->mutex);
            //Se la nextTaskToArrive non è nello state_new vuol dire che l'altro core l'ha già presa in carico
            //Utilizzo il mutex qui per rendere atomica il check e il cambio dello stato della task
            if (nextTaskToArrive->state == state_new) {
                changeTaskState(nextTaskToArrive, state_ready, pc, threadArgs->threadId);
            } else {
                pthread_mutex_unlock(threadArgs->mutex);
                nextTaskToArrive = (TaskControlBlock *) nextTaskToArrive->next;
                goto SELECTION;
            }
            pthread_mutex_unlock(threadArgs->mutex);

            pushToStateList(readyList, nextTaskToArrive);
            nextTaskToArrive = (TaskControlBlock *) nextTaskToArrive->next;
            if (threadArgs->isPreemptive && runningTask != NULL) {
                //Se siamo in modalità preemptive, secondo l'algoritmo SRT, devo rischedulare ad ogni arrivo
                pushToStateList(readyList, runningTask);
                changeTaskState(runningTask, state_ready, pc, threadArgs->threadId);
                runningTask = NULL;
            }
        }

        SELECTION:
        if (readyList->nOfElements == 0 && blockedList->nOfElements == 0 && nextTaskToArrive == NULL &&
            runningTask == NULL) {
            break;
        }


        if (runningTask == NULL) {
            runningTask = threadArgs->isPreemptive ? selectionFunctionSRT(readyList) : selectionFunctionSPN(readyList);

            if (runningTask == NULL) {
                goto TICK;
            }

            if (runningTask->pc == NULL) {
                currentInstruction = runningTask->instructionList->head;
                goto EXECUTION;
            }
        }

        if (runningTask->pc->length == 0) {
            if (runningTask->pc->next == NULL) {
                changeTaskState(runningTask, state_exit, pc, threadArgs->threadId);
                runningTask = NULL;
                goto TICK;
            } else {
                currentInstruction = (Instruction *) runningTask->pc->next;
            }
        } else {
            currentInstruction = runningTask->pc;
        }


        EXECUTION:
        runningTask->pc = currentInstruction;

        if (runningTask->state != state_running) {
            changeTaskState(runningTask, state_running, pc, threadArgs->threadId);
        }

        if (currentInstruction->type_flag == nonBlocking) {
            currentInstruction->length--;
            runningTask->execution_time++;

            printf("\tTask #%d: Eseguo calcolo\n", runningTask->id);
            if (currentInstruction->length > 0) {
                goto TICK;
            }

            if (currentInstruction->next != NULL) {
                printf("\tTask #%d: Nuova istruzione\n", runningTask->id);
                currentInstruction = (Instruction *) currentInstruction->next;
            } else {
                changeTaskState(runningTask, state_exit, pc, threadArgs->threadId);
                currentInstruction = NULL;
                runningTask = NULL;
            }
            goto TICK;
        }

        if (currentInstruction->type_flag == blocking) {
            currentInstruction->length = getRandomLenght(currentInstruction->length);
            changeTaskState(runningTask, state_blocked, pc, threadArgs->threadId);
            pushToStateList(blockedList, runningTask);
            runningTask = NULL;
            currentInstruction = NULL;
        }

        TICK:
        tickAllBlockedTasks(blockedList, readyList);

        pc++;
    }

    printf("Core #%d - PC #%d END\n", threadArgs->threadId, pc);
}

