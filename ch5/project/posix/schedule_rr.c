#include "cpu.h"
#include "schedulers.h"
#define arrSize 20

Task *arr[arrSize];
int first, last, size = 0;

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
  arr[last] = createTask(name, priority, burst);
  last = (last + 1) % arrSize;
  size++;
}

Task *pop() {
  if (size == 0) {
    return NULL;
  }

  Task *t = arr[first];
  first = (first + 1) % arrSize;
  size--;
  return t;
}

// invoke the scheduler
/* Running task = [T1] [4] [20] for 20 units.
        Time is now: 20
*/
void schedule() {
  printf("========RR=========\n");
  int time = 0;
  while (size != 0) {
    Task *t = pop();
    int diffTime = t->burst - QUANTUM;

    if (diffTime > 0) {
      run(t, QUANTUM);
      time += QUANTUM;
      printf("\tTime is now: %d\n", time);
      add(t->name, t->priority, diffTime);
      free(t);
    } else {
      run(t, t->burst);
      time += t->burst;
      printf("\tTime is now: %d\n", time);
      free(t->name);
      free(t);
    }
  }
}