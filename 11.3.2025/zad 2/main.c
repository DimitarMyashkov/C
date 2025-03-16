#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 15

void newLine(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}

int main() {
    int numSubjects, numStudents = 0;
    char **subjects;
    char **students;
    int **grades;

    while (numSubjects <= 0) {
        printf("Input number of subjects: ");
        scanf("%d", &numSubjects);
        while (getchar() != '\n');
    }

    subjects = (char **)malloc(numSubjects * sizeof(char *));

    for (int i = 0; i < numSubjects; i++) {
        subjects[i] = (char *)malloc((MAX_NAME + 1) * sizeof(char));
        printf("Input subject %d: ", i + 1);
        newLine(subjects[i], MAX_NAME + 1);
    }

    int choice;
    while (choice != 3) {
        printf("\nMenu:\n");
        printf("1. Add student\n");
        printf("2. Print\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                numStudents++;
                students = (char **) realloc(students, numStudents * sizeof(char *));
                grades = (int **) realloc(grades, numStudents * sizeof(int *));

                students[numStudents - 1] = (char *) malloc((MAX_NAME + 1) * sizeof(char));
                grades[numStudents - 1] = (int *) malloc(numSubjects * sizeof(int));

                printf("Student name: ");
                newLine(students[numStudents - 1], MAX_NAME + 1);

                for (int j = 0; j < numSubjects; j++) {
                    printf("Grade in %s: ", subjects[j]);
                    scanf("%d", &grades[numStudents - 1][j]);
                    while (getchar() != '\n');
                }

            case 2:
                // Принтиране на дневника
                printf("\n%-15s", "Име");
                for (int i = 0; i < numSubjects; i++) {
                    printf("%-15s", subjects[i]);
                }
                printf("\n");

                for (int i = 0; i < numStudents; i++) {
                    printf("%-15s", students[i]);
                    for (int j = 0; j < numSubjects; j++) {
                        printf("%-15d", grades[i][j]);
                    }
                    printf("\n");
                }
        }
    }

    free(subjects);
    free(students);
    free(grades);

    return 0;
}
