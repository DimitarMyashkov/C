#ifndef PROCESSES_H
#define PROCESSES_H

#define MAX_PROCESSES 5
#define MAX_PROCESS_NAME 30

typedef struct {
    int id;
    char name[MAX_PROCESS_NAME];
} Process;

extern Process processes[MAX_PROCESSES];
extern int processescount;

void initProcesses();
void listProcesses();
int nextProcessID();
int createNewProcess(const char *name);
int stopProcess(int id);

#endif
