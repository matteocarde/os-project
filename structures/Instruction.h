//
// Created by Matteo Cardellini on 17/04/18.
//

#ifndef OS_PROJECT_INSTRUCTION_H
#define OS_PROJECT_INSTRUCTION_H

/*
 * Un’istruzione è composta da:
type_flag:
Flag 0 := istruzione di calcolo, ovvero non bloccante;
Flag 1 := operazione di I/O, ovvero bloccante.
length:
se l'istruzione non è bloccante indica la sua durata di esecuzione in cicli di clock
se l’istruzione è bloccante, il task si blocca per un numero randomico compreso tra 1 e length cicli di clock
 */

enum blockingFlag {
    nonBlocking = 0,
    blocking = 1
};

//TODO: Use Instruction_t like gnu
typedef struct {
    enum blockingFlag type_flag;
    int length;
    struct Instruction *next;
} Instruction;

#endif //OS_PROJECT_INSTRUCTION_H
