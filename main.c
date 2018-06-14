#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <pthread.h>
#include <unistd.h>
#include "utilities/utilities.h"
#include "core/Scheduler.h"

int main(int argc, char **argv) {

    //TODO: Use perror e codici di errore da https://goo.gl/Y40V0r

    programArgs_t programArgs = getArgsSettings(argc, argv);


    FILE *noPreemptionFile = fopen(programArgs.noPreemptionPath, "w");
    if (noPreemptionFile == NULL) {
        perror(programArgs.noPreemptionPath);
        exit(EX_CANTCREAT);
    }

    FILE *preemptionFile = fopen(programArgs.preemptionPath, "w");
    if (preemptionFile == NULL) {
        perror(programArgs.preemptionPath);
        exit(EX_CANTCREAT);
    }

    programArgs.noPreemptionFile = noPreemptionFile;
    programArgs.preemptionFile = preemptionFile;

    printf("Loading TaskList from CSV...\n");
    TaskList *taskList = getTaskListFromCSV(programArgs.inputPath);
    if (taskList == NULL) {
        fprintf(stderr, "ERROR: Impossible to create task list");
        exit(EX_OSFILE);
    }
    printf("Finished loading TaskList from CSV\n");

    pid_t child_pid = fork();


    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    threadArgs_t threadArgsCore1;
    threadArgsCore1.taskList = taskList;
    threadArgsCore1.isPreemptive = child_pid == 0; // Figlio -> Preemptive, Padre -> Non-Preemptive
    threadArgsCore1.programArgs = programArgs;
    threadArgsCore1.threadId = 0;
    threadArgsCore1.mutex = &mutex;

    threadArgs_t threadArgsCore2 = threadArgsCore1;
    threadArgsCore2.threadId = 1;

    pthread_t first_core_id;
    pthread_create(&first_core_id, NULL, (void *(*)(void *)) &Scheduler, &threadArgsCore1);

    Scheduler(&threadArgsCore2);


    pthread_join(first_core_id, NULL);

    if (child_pid != 0) {
        waitpid(child_pid, NULL, 0);
    }


}