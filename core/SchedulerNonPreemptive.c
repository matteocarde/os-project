//
// Created by Matteo Cardellini on 10/06/18.
//

#include "../structures/TaskList.h"
#include "../structures/StateList.h"
#include "../structures/TaskControlBlock.h"
#include "../structures/Instruction.h"
#include <stddef.h>
#include <printf.h>

unsigned int pc = 0;


TaskControlBlock *selectionFunction(StateList *readyList) {
    return popFromStateList(readyList);
}

void tickAllBlockedTasks(StateList *blockedList, StateList *readyList) {

    StateListElement *currentElement = blockedList->front;

    while (currentElement != NULL) {
        TaskControlBlock *currentTask = currentElement->task;
        printf("Task #%d: Ha bisogno ancora di %d clock\n", currentTask->id, currentTask->blockingInstruction->length);
        if (currentTask->blockingInstruction->length == 0) {
            removeFromList(blockedList, currentElement);
            pushToStateList(readyList, currentElement->task);
            printf("Task #%d: Terminato I/O\n", currentElement->task->id);
        }
        currentTask->blockingInstruction->length--;
        currentElement = (StateListElement *) currentElement->next;
    }


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
            changeStateToTask(nextTaskToArrive, state_ready);
            pushToStateList(readyList, nextTaskToArrive);
            nextTaskToArrive = (TaskControlBlock *) nextTaskToArrive->next;
        }

        tickAllBlockedTasks(blockedList, readyList);

        if (readyList->nOfElements == 0 && nextTaskToArrive == NULL && runningTask == NULL) {
            break;
        }


        if (runningTask == NULL) {
            runningTask = selectionFunction(readyList);

            if (runningTask == NULL) {
                continue;
            }

            if (runningTask->blockingInstruction == NULL) {
                currentInstruction = runningTask->instructionList->head;
            } else {
                if (runningTask->blockingInstruction->next == NULL) {
                    runningTask = NULL;
                    continue;
                } else {
                    currentInstruction = (Instruction *) runningTask->blockingInstruction->next;
                }
            }
        }

        currentInstruction->length--;

        if (currentInstruction->type_flag == nonBlocking) {

            if (runningTask->state != state_running) {
                changeStateToTask(runningTask, state_running);
            }

            if (currentInstruction->length > 0) {
                continue;
            }

            if (currentInstruction->next != NULL) {
                printf("Task #%d: Nuova istruzione\n", runningTask->id);
                currentInstruction = (Instruction *) currentInstruction->next;
            } else {
                printf("Task #%d: Terminato\n", runningTask->id);
                currentInstruction = NULL;
                runningTask = NULL;
            }
            continue;
        }

        if (currentInstruction->type_flag == blocking) {
            runningTask->blockingInstruction = currentInstruction;
            changeStateToTask(runningTask, state_blocked);
            pushToStateList(blockedList, runningTask);
            runningTask = NULL;
            currentInstruction = NULL;
        }


    }

    printf("END\n");
}

