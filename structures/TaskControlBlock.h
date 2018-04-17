//
// Created by Matteo Cardellini on 17/04/18.
//

#ifndef OS_PROJECT_TASK_H
#define OS_PROJECT_TASK_H

#include "InstructionsList.h"

/*
 * Un task in esecuzione viene gestito tramite una struttura dati, la Task Control Block (TCB), definita da:
id: id univoco
pc: program counter (puntatore alla prossima istruzione da eseguire)
arrival_time: numero intero che descrive a quale ciclo di clock il task deve essere considerato dallo scheduler
instr_list: la lista delle istruzioni da eseguire.
state: lo stato (new, ready, running, blocked, exit)

 */

enum task_state {
    state_new = 0,
    state_ready = 1,
    state_running = 2,
    state_blocked = 3,
    state_exit = 4
};

typedef struct {
    int id;
    int pc;
    int arrival_time;
    InstructionList* instructionList;
    enum task_state state;

} TaskControlBlock;

#endif //OS_PROJECT_TASK_H
