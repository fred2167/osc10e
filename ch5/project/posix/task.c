#include "task.h"

Task* createTask(char* name, int priority, int burst){
    Task* t = malloc(sizeof(Task));
    t->name = name;
    t->priority = priority;
    t->burst = burst;
    t->tid = 0;
    return t;
}