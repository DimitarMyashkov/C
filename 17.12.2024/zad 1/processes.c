#include "processes.h"
#include <stdio.h>
#include <string.h>

Process processes[MAX_PROCESSES];
int processescount = 0;

void initProcesses() {
    processescount = 0;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].id = -1;
        processes[i].name[0] = '\0';
    }
}

void listProcesses() {
    printf("list with processes (%d/%d):\n", processescount, MAX_PROCESSES);
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].id != -1) {
            printf("id: %d, name: %s\n", processes[i].id, processes[i].name);
        }
    }
}

int nextProcessID() {
    int nextID = processescount + 1;
    return nextID;
}

int createNewProcess(const char *name) {
    if (processescount > MAX_PROCESSES) {
        printf("Max process capacity is reached.\n");
    }

    for (int i = 0; i < MAX_PROCESSES; i++) {
        int id = nextProcessID();
        if (processes[i].id == -1) {
            processes[i].id = id;
            strncpy(processes[i].name, name, MAX_PROCESS_NAME - 1);
            processes[i].name[MAX_PROCESS_NAME - 1] = '\0';
            processescount++;
            printf("process with id %d and name \"%s\" has been added.\n", id, name);
        }
    }
}

int stopProcess(int id) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        scanf("%d", &id);

        if(id > processes[processescount - 1].id || id < processes[0].id) {
            return -1;
        }

        if (processes[i].id == id) {
            processes[i].id = -1;
            processes[i].name[0] = '\0';
            return 0;
        }
    }
    return -1;
}