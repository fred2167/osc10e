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

  // use **-burst** as priority
  PriorityNode *newNode = createNode(-burst, name, priority, burst);

  if (size >= arrSize) {
    printf("ERROR: array FULL\n");
    return;
  }
  arr[size++] = newNode;
}

// invoke the scheduler
void schedule() {
  int time = 0;
  while (size > 0) {
    Task *t = pop();
    time += t->burst;
    run(t, t->burst);
    printf("\tTime is now: %d\n", time);
    free(t->name);
    free(t);
  }
}
