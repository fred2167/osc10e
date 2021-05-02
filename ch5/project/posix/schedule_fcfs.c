#include "cpu.h"
#include "schedulers.h"
#define arrSize 20

Task *arr[arrSize];
int size = 0;

Task *createTask(char *name, int priority, int burst) {
  Task *t = malloc(sizeof(Task));
  t->name = name;
  t->priority = priority;
  t->burst = burst;
  t->tid = 0;
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

// invoke the scheduler
/* Running task = [T1] [4] [20] for 20 units.
        Time is now: 20
*/
void schedule() {
  printf("========FCFS=========\n");
  int time = 0;
  double count = -1;
  for (int i = 0; i < size; i++) {
    Task *t = arr[i];
    time += t->burst;
    run(t, t->burst);
    printf("\tTime is now: %d\n", time);
    free(t->name);
    free(t);
    count++;
  }
  printf("CPU Utilization: %.2f%\n", (time / (count + time)) * 100);
}