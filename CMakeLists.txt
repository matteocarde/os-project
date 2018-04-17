cmake_minimum_required(VERSION 3.9)
project(os_project C)

set(CMAKE_C_STANDARD 99)

add_executable(os_project main.c utilities/utilities.c utilities/utilities.h structures/TaskControlBlock.h structures/InstructionsList.h structures/Instruction.h structures/Instruction.c structures/InstructionList.c structures/TaskControlBlock.c libs/csvparser.c libs/csvparser.h structures/TaskList.h structures/TaskList.c)