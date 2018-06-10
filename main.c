#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include "utilities/utilities.h"
#include "core/SchedulerNonPreemptive.h"

int main(int argc, char **argv) {

    //TODO: Use perror e codici di errore da https://goo.gl/Y40V0r

    printf("Getting settings from args...\n");
    settings argsSettings;
    argsSettings = getArgsSettings(argc, argv);

    printf("Path preemption %s\nPath nopreemption %s\nPath input %s\n", argsSettings.preemptionPath,
           argsSettings.noPreemptionPath, argsSettings.inputPath);


    printf("Getting TaskList from CSV...\n");
    TaskList *taskList = getTaskListFromCSV(argsSettings.inputPath);
    if (taskList == NULL) {
        fprintf(stderr, "ERROR: Impossible to create task list");
        exit(EX_OSFILE);
    }
    printf("Done\n");


    SchedulerNonPreemptive(taskList);

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