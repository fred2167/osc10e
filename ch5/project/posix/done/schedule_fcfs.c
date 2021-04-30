#include "schedulers.h"
#define arrSize 20

Task* arr[arrSize];
int size = 0;

// add a task to the list 
void add(char *name, int priority, int burst){
    Task* newTask = createTask(name, priority, burst);
    if (size >= arrSize){
        printf("ERROR: array FULL\n");
        return;
    }
    arr[size++] = newTask;
}

// invoke the scheduler
/* Running task = [T1] [4] [20] for 20 units.
        Time is now: 20
*/
void schedule(){
    int idx = 0;
    int time = 0;
    for (int i = 0; i < size; i++){
        Task* t = arr[i];
        time += t->burst;
        printf("Running task = [%s] [%d] [%d] for %d units.\n", t->name, t->priority, t->burst, t->burst);
        printf("\tTime is now: %d\n", time);
        free(t->name);
        free(t);
    }
    size = 0;
}