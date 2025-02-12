#include <stdio.h>
#include "processes.h"

int main() {
    initProcesses();

    int option;
    printf("Choose an option:\n");
    printf("1.Create a process\n");
    printf("2.Show all processes\n");
    printf("3.Stop a process\n");
    printf("4.Exit\n");
    scanf("%d", &option);

    switch(option){
        case 1:
            char name[MAX_PROCESS_NAME];
            printf("Input a name: ");
            scanf("%s", &name);
            createNewProcess(name);
        case 2:
            listProcesses();
        case 3:
            int id;
            printf("Input an ID: ");
            scanf("%d", &id);
            stopProcess(id);
        case 4:
            break;
    }

    return 0;
}
