#include "cpu.h"
#include "schedulers.h"
#define arrSize 20

Task *arr[arrSize];
int size = 0;
int first = 0;

void printTable(Task* arr[], int size){
    printf("...|");
    for (int i = 0; i < size; i++){
        Task* t = arr[i];
        printf("%3s|", t->name);
    }
    printf("\nTAT|");
    for (int i = 0; i < size; i++){
        Task* t = arr[i];
        printf("%3d|", t->turnAroundTime);
    }
    printf("\n WT|");
    for (int i = 0; i < size; i++){
        Task* t = arr[i];
        printf("%3d|", t->waitTime);
    }
    printf("\n RT|");
    for (int i = 0; i < size; i++){
        Task* t = arr[i];
        printf("%3d|", t->responseTime);
        free(t->name);
        free(t);
    }
    printf("\n");
}

Task *createTask(char *name, int priority, int burst) {
  Task *t = malloc(sizeof(Task));
  t->name = name;
  t->priority = priority;
  t->burst = burst;
  t->tid = 0;
  t->turnAroundTime = 0;
  t->waitTime = 0;
  t->responseTime = 0;
  return t;
}

// add a task to the list
void add(char *name, int priority, int burst) {
  if (size >= arrSize) {
    printf("ERROR: array FULL\n");
    return;
  }
  arr[size++] = createTask(name, priority, burst);
}

Task *pop() {
  size--;
  return arr[first++];
}

// invoke the scheduler
/* Running task = [T1] [4] [20] for 20 units.
        Time is now: 20
*/
void schedule() {
  printf("=====================FCFS=====================\n");
  int time = 0;
  double count = 0;
  int printSize = size;
  while (size > 0) {
    Task *t = pop();
    t->waitTime = time;
    t->responseTime = time;
    count++;
    time += t->burst;
    run(t, t->burst);
    t->turnAroundTime = time;
    printf("\tTime is now: %d\n", time);
  }
  printf("CPU Utilization: %.2f%%\n", (time / (count - 1 + time)) * 100);
  printTable(arr, printSize);
}