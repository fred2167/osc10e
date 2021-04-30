#include "schedulers.h"

#define arrSize 20

typedef struct{
    int priority;
    Task* task;
}PriorityNode;

PriorityNode* arr[arrSize];
int size = -1;

PriorityNode* createNode(char *name, int priority, int burst){
    
}

void heapify(){

}

// add a task to the list 
void add(char *name, int priority, int burst){
    Task* newTask = createTask(name, priority, burst);
    
}

// invoke the scheduler
void schedule(){

}
