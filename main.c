#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilities/utilities.h"
#include "libs/csvparser.h"
#include "structures/TaskList.h"
#include "structures/TaskControlBlock.h"
#include "structures/InstructionsList.h"
#include "structures/Instruction.h"

int main(int argc, char **argv) {


    settings argsSettings;
    argsSettings = getArgsSettings(argc, argv);

    printf("Path preemption %s\nPath nopreemption %s\nPath input %s\n", argsSettings.preemptionPath,
           argsSettings.noPreemptionPath, argsSettings.inputPath);

    CsvParser *csvParser = CsvParser_new(argsSettings.inputPath, ",", 0);
    CsvRow *row;


    //TODO: Check if file exists !!!

    TaskList *taskList = createTaskList();

    TaskControlBlock *currentTask = NULL;


    do {
        row = CsvParser_getRow(csvParser);
        if (row == NULL) {
            break;
        }

        char **rowFields = CsvParser_getFields(row);

        char *type = rowFields[0];
        if (strcmp(type, "t") == 0) {
            int taskId = atoi(rowFields[1]);
            int arrivalTime = atoi(rowFields[2]);
            currentTask = createTaskControlBlock(taskId, arrivalTime);
            addTaskToList(taskList, currentTask);
        } else if (strcmp(type, "i") == 0) {
            if (currentTask == NULL) {
                fprintf(stderr, "CSV FORMAT ERROR: The file starts with instructions without a parent task");
                return 1;
            }
            enum blockingFlag type_flag = (enum blockingFlag) atoi(rowFields[1]);
            int length = atoi(rowFields[2]);
            addInstructionToList(currentTask->instructionList, type_flag, length);
        }
        CsvParser_destroy_row(row);
    } while (row);

    CsvParser_destroy(csvParser);


//    TaskControlBlock *printTCB = taskList->head;
//    for (int i = 0; i < taskList->nOfElements; ++i) {
//        Instruction *printInstruction = printTCB->instructionList->head;
//        printf("-T,%d,%d\n", printTCB->id, printTCB->arrival_time);
//        for (int j = 0; j < printTCB->instructionList->nOfElements; ++j) {
//            printf("--I,%d,%d\n", printInstruction->type_flag, printInstruction->length);
//            printInstruction = printInstruction->next;
//        }
//        printTCB = printTCB->next;
//    }


}