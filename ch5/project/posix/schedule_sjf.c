#include "cpu.h"
#include "schedulers.h"
#define arrSize 20

typedef struct {
  int priority;
  Task *task;
} PriorityNode;

PriorityNode *arr[arrSize];
int size = 0;

PriorityNode *createNode(int nodePriority, char *name, int taskPriority,
                         int burst) {
  PriorityNode *newNode = malloc(sizeof(PriorityNode));
  newNode->task = malloc(sizeof(Task));

  newNode->priority = nodePriority;
  newNode->task->priority = taskPriority;
  newNode->task->name = name;
  newNode->task->burst = burst;
  newNode->task->tid = 0;
  return newNode;
}

// pop the **highest** priority
Task *pop() {
  if (size == 0) {
    return NULL;
  }

  int highestPriority = -1000;
  Task *highestTask = NULL;
  int highestPriorityIdx = 0;

  for (int i = 0; i < size; i++) {
    PriorityNode *node = arr[i];

    if (node->priority > highestPriority) {
      highestPriority = node->priority;
      highestTask = node->task;
      highestPriorityIdx = i;
    }
  }

  for (int i = highestPriorityIdx; i < size; i++) {
    arr[i] = arr[i + 1];
  }
  size--;
  return highestTask;
}

// add a task to the list
void add(char *name, int priority, int burst) {
  if (size >= arrSize) {
    printf("ERROR: array FULL\n");
    return;
  }

  // use **-burst** as priority
  arr[size++] = createNode(-burst, name, priority, burst);
}

// invoke the scheduler
void schedule() {
  printf("=====================SJF======================\n");
  int time = 0;
  double count = 0;
  while (size > 0) {
    Task *t = pop();
    count++; // track dispatcher's time
    time += t->burst;
    run(t, t->burst);
    printf("\tTime is now: %d\n", time);
    free(t->name);
    free(t);
  }
  printf("CPU Utilization: %.2f%%\n", (time / (count - 1 + time)) * 100);
}
