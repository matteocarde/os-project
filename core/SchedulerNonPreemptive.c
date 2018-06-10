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
        currentTask->blockingInstruction->length--;
        if (currentTask->blockingInstruction->length == 0) {
            removeFromList(blockedList, currentElement);
            pushToStateList(readyList, currentElement->task);
        }
        currentElement = (StateListElement *) currentElement->next;
    }


}

void SchedulerNonPreemptive(TaskList *taskList) {

    TaskControlBlock *nextTaskToArrive = taskList->head;
    TaskControlBlock *runningTask = NULL;
    Instruction *currentInstruction = NULL;

    StateList *readyList = createStateList();
    StateList *blockedList = createStateList();

    while (1) {

        pc++; //TODO: Magari mettilo in fondo ?
        printf("PC #%d\n", pc);

        if (nextTaskToArrive != NULL && nextTaskToArrive->arrival_time == pc) {
            changeStateToTask(nextTaskToArrive, state_ready);
            pushToStateList(readyList, nextTaskToArrive);
            nextTaskToArrive = (TaskControlBlock *) nextTaskToArrive->next;
        }

        tickAllBlockedTasks(blockedList, readyList);

        if (readyList->nOfElements == 0) {
            //Non ci sono task pronte ad essere eseguite
            if (nextTaskToArrive == NULL) {
                break;
            } else {
                continue;
            };
        }

        if (runningTask == NULL) {
            runningTask = selectionFunction(readyList);
            currentInstruction = runningTask->instructionList->head;
        }

        currentInstruction->length--;
        if (currentInstruction->type_flag == nonBlocking) {
            if (runningTask->state != state_running) {
                changeStateToTask(runningTask, state_running);
            }
            if (currentInstruction->length == 0) {
                printf("Task #%d: Nuova istruzione", runningTask->id);
                if (currentInstruction->next != NULL) {
                    currentInstruction = (Instruction *) currentInstruction->next;
                } else {
                    currentInstruction = NULL;
                    runningTask = NULL;
                }
            }
            continue;
        }

        if (currentInstruction->type_flag == blocking) {

            runningTask->blockingInstruction = currentInstruction;
            changeStateToTask(runningTask, state_blocked);
            pushToStateList(blockedList, runningTask);
            runningTask = NULL;

        }


    }

}

