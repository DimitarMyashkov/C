#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[16];
    int classNum;
    double averageGrade;
} Student;

void printMenu() {
    printf("\n-Menu\n");
    printf("1. Add a student\n");
    printf("2. Show all students\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

int main() {
    Student* students = NULL;
    int classNum = 0;
    int choice;

    while (choice != 3) {
        printMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                students = realloc(students, (classNum + 1) * sizeof(Student));
                if (students == NULL) {
                    printf("Memory allocation failed!\n");
                    return 1;
                }

                printf("Input student name (max 15): ");
                fgets(students[classNum].name, sizeof(students[classNum].name), stdin);
                students[classNum].name[strcspn(students[classNum].name, "\n")] = '\0';

                printf("Input student class number: ");
                scanf("%d", &students[classNum].classNum);

                printf("Input average grade: ");
                scanf("%lf", &students[classNum].averageGrade);

                classNum++;
                printf("Student added successfully\n");

                break;

            case 2:
                if (classNum == 0) {
                    printf("No students added yet\n");
                } else {
                    printf("\nList of students:\n");
                    for (int i = 0; i < classNum; i++) {
                        printf("Name: %s, Class number: %d, Average grade: %.2f\n", students[i].name, students[i].classNum, students[i].averageGrade);
                    }
                }

                break;

            case 3:
                printf("Exiting\n");
                break;

            default:
                printf("Invalid input");
        }
    }

    free(students);

    return 0;
}
