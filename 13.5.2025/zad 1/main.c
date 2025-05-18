#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

const char* statusToString(enum TaskStatus status) {
    switch (status) {
        case NEW: return "New";
        case STARTED: return "Started";
        case FINISHED: return "Finished";
        default: return "Unknown";
    }
}

void addTask(LinkedList* list, char* name, int priority) {
    Task newTask;
    strncpy(newTask.name, name, sizeof(newTask.name));
    newTask.status = NEW;

    if (priority <= 0) priority = 1;
    if (priority > list->size) priority = list->size + 1;

    push(list, priority - 1, newTask);
}

void changeTaskStatus(LinkedList* list, int priority, enum TaskStatus newStatus) {
    if (priority <= 0 || priority > list->size) {
        printf("Invalid priority!\n");
        return;
    }
    Task task = get(list, priority - 1);
    task.status = newStatus;
    set(list, priority - 1, task);
}

void deleteTask(LinkedList* list, int priority) {
    if (priority <= 0 || priority > list->size) {
        printf("Invalid priority!\n");
        return;
    }
    pop(list, priority - 1);
}

void printTasks(LinkedList* list) {
    for (int i = 0; i < list->size; i++) {
        Task task = get(list, i);
        printf("%d. %s - %s\n", i + 1, task.name, statusToString(task.status));
    }
}

void freeMemory(LinkedList* list) {
    for (int i = 0; i < list->size; i++) {
        pop(list, i);
    }
}

int main() {
    LinkedList tasks = init();
    int choice;

    while (1) {
        printf("\n1. Add task\n");
        printf("2. Change status\n");
        printf("3. Delete task\n");
        printf("4. Show all tasks\n");
        printf("5. Exit\n");
        printf("Choice:\n");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            char name[100];
            int prio;
            printf("Task name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            printf("priority: ");
            scanf("%d", &prio);
            addTask(&tasks, name, prio);
        } else if (choice == 2) {
            int prio, stat;
            printf("Task number: ");
            scanf("%d", &prio);
            printf("Status (0 = New, 1 = Started, 2 = Finished): ");
            scanf("%d", &stat);
            changeTaskStatus(&tasks, prio, stat);
        } else if (choice == 3) {
            int prio;
            printf("Task number: ");
            scanf("%d", &prio);
            deleteTask(&tasks, prio);
        } else if (choice == 4) {
            printTasks(&tasks);
        } else {
            break;
        }
    }

    freeMemory(&tasks);

    return 0;
}
