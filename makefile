#Preso spunto da https://web.stanford.edu/class/cs107/guide/make.html

#
# A simple makefile for managing build of project composed of C source files.
#


# It is likely that default C compiler is already gcc, but explicitly
# set, just to be sure
CC = gcc

# The CFLAGS variable sets compile flags for gcc:
#  -g        compile with debug information
#  -Wall     give verbose compiler warnings
#  -O0       do not optimize generated code
#  -std=c99  use the C99 standard language definition
CFLAGS = -g -Wall -O0 -std=c99

# The LDFLAGS variable sets flags for linker
#  -lpthread   says to link in pthread
LDFLAGS = -lpthread

# In this section, you list the files that are part of the project.
# If you add/change names of source files, here is where you
# edit the Makefile.
SOURCES = main.c utilities/utilities.c structures/TaskList.c structures/TaskControlBlock.c structures/StateList.c structures/InstructionList.c structures/Instruction.c libs/csvparser.c core/Scheduler.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = simulator


# The first target defined in the makefile is the one
# used when make is invoked with no argument. Given the definitions
# above, this Makefile file will build the one named TARGET and
# assume that it depends on all the named OBJECTS files.

all: simulator

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core