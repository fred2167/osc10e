/**
 * Representation of a task in the system.
 */

#ifndef TASK_H
#define TASK_H
#include <stdlib.h>
#include <string.h>

// representation of a task
typedef struct task {
    char *name;
    int tid;
    int priority;
    int burst;
} Task;

Task* createTask(char* name, int priority, int burst);

#endif
