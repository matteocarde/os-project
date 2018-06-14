#include <stdio.h>
#include <stdlib.h>
#include <ntsid.h>
#include <zconf.h>
#include <sysexits.h>
#include <pthread.h>
#include "utilities/utilities.h"
#include "core/Scheduler.h"

int main(int argc, char **argv) {

    //TODO: Use perror e codici di errore da https://goo.gl/Y40V0r

    printf("Getting programArgs from args...\n");
    programArgs_t programArgs;
    programArgs = getArgsSettings(argc, argv);

    printf("Path preemption %s\nPath nopreemption %s\nPath input %s\n", programArgs.preemptionPath,
           programArgs.noPreemptionPath, programArgs.inputPath);


    printf("Getting TaskList from CSV...\n");
    TaskList *taskList = getTaskListFromCSV(programArgs.inputPath);
    if (taskList == NULL) {
        fprintf(stderr, "ERROR: Impossible to create task list");
        exit(EX_OSFILE);
    }
    printf("Done\n");

    pid_t child_pid = fork();

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    threadArgs_t threadArgsCore1 = threadArgsCore1;
    threadArgsCore1.taskList = taskList;
    threadArgsCore1.isPreemptive = child_pid == 0;
    threadArgsCore1.programArgs = programArgs;
    threadArgsCore1.threadId = 0;
    threadArgsCore1.mutex = &mutex;

    threadArgs_t threadArgsCore2 = threadArgsCore1;
    threadArgsCore2.threadId = 1;

    pthread_t first_core_id;
    pthread_create(&first_core_id, NULL, &Scheduler, &threadArgsCore1);

    Scheduler(&threadArgsCore2);

    pthread_join(first_core_id, NULL);

}