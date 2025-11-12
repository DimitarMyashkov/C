#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 255

typedef struct {
    long egn;
    char name[MAX_NAME_LEN];
    int age;
    short int education;
    short int work_status;
    short int marital_status;
} Citizen;

FILE *file = NULL;


void openFile() {
    file = fopen("citizens.txt", "rb+");
    if (file == NULL) {
        file = fopen("citizens.txt", "wb+");
        if (file == NULL) {
            printf("file not found\n");
            exit(1);
        }
        printf("new file created\n");
    } else {
        printf("file was opened successfully\n");
    }
}

void addCitizen() {
    if (file == NULL) {
        printf("no file opened.\n");
        return;
    }

    Citizen c;
    printf("input egn: ");
    scanf("%ld", &c.egn);

    printf("input name: ");
    fgets(c.name, MAX_NAME_LEN, stdin);
    c.name[strcspn(c.name, "\n")] = '\0';

    printf("input age: ");
    scanf("%d", &c.age);

    printf("education (0 - no; 1 - primary; 2 - middle; 3 - high): ");
    scanf("%d", &c.education);

    printf("employment status (0 - unemployed; 1 - employed): ");
    scanf("%d", &c.work_status);

    printf("marital status (0 - single; 1 - married): ");
    scanf("%d", &c.marital_status);

    fseek(file, 0, SEEK_END);
    fwrite(&c, sizeof(Citizen), 1, file);
    printf("citizen added successfully\n");
}

void printCitizens() {
    if (file == NULL) {
        printf("no file opened.\n");
        return;
    }

    rewind(file);
    Citizen c;
    while (fread(&c, sizeof(Citizen), 1, file) == 1) {
        printf("-----------------------------\n");
        printf("egn: %ld\n", c.egn);
        printf("name: %s\n", c.name);
        printf("age: %d\n", c.age);
        printf("education: %s\n", (char*[]){"no", "primary", "middle", "high"}[c.education]);
        printf("employment status: %s\n", c.work_status ? "employed" : "unemployed");
        printf("marital status: %s\n", c.marital_status ? "married" : "single");
        printf("-----------------------------\n");
    }
}

void deleteByEGN() {
    if (file == NULL) {
        printf("no file opened.\n");
        return;
    }

    long targetEGN;
    printf("input egn for deletion: ");
    scanf("%ld", targetEGN);

    FILE *temp = tmpfile();
    Citizen c;
    int found = 0;

    rewind(file);
    while (fread(&c, sizeof(Citizen), 1, file) == 1) {
        if (c.egn == targetEGN) {
            fwrite(&c, sizeof(Citizen), 1, temp);
        } else {
            found = 1;
        }
    }

    if (!found) {
        printf("citizen with this egn was not found\n");
        fclose(temp);
        return;
    }

    freopen("citizens.txt", "wb+", file);
    rewind(temp);
    while (fread(&c, sizeof(Citizen), 1, temp) == 1) {
        fwrite(&c, sizeof(Citizen), 1, file);
    }
    fclose(temp);
    printf("citizen deleted successfully.\n");
}

void menu() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add citizen\n");
        printf("2. Show all citizens\n");
        printf("3. Delete citizen by egn\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCitizen(); break;
            case 2: printCitizens(); break;
            case 3: deleteByEGN(); break;
            case 4: break;
            default: printf("invalid choice\n");
        }
    } while (choice != 4);

    if (file != NULL) {
        fclose(file);
    }
}

int main() {
    openFile();
    menu();
    return 0;
}
