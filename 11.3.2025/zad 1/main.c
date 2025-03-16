#include <stdio.h>
#include <stdlib.h>

float average(int* grades, int count) {
    if (count == 0) return 0;
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += grades[i];
    }
    return (float)sum / count;
}

int main() {
    int numGrades;

    while (numGrades < 0) {
        printf("Input number of grades: ");
        scanf("%d", &numGrades);
        if (numGrades < 0) printf("The number of grades can't be negative\n");
    }

    int *grades = (int *)malloc(numGrades * sizeof(int));

    for (int i = 0; i < numGrades; ++i) {
        while (grades[i] < 2 || grades[i] > 6) {
            printf("Input grade %d: ", i + 1);
            scanf("%d", &grades[i]);
            if (grades[i] < 2 || grades[i] > 6) {
                printf("The grade has to be between 2 and 6\n");
            }
        }
    }

    int choice;
    while (choice != 4) {
        printf("\nMenu:\n");
        printf("1. Average grade\n");
        printf("2. Add a grade\n");
        printf("3. Delete last grade\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Average grade: %.2f\n", average(grades, numGrades));
                break;

            case 2:
                int newGrade;
                while (newGrade < 2 || newGrade > 6) {
                    printf("Input new grade): ");
                    scanf("%d", &newGrade);
                    if (newGrade < 2 || newGrade > 6) {
                        printf("The grade has to be between 2 and 6\n");
                    }
                }

                int *temp = (int *)realloc(grades, (numGrades + 1) * sizeof(int));

                grades = temp;
                grades[numGrades] = newGrade;
                numGrades++;
                break;

            case 3:
                if (numGrades > 0) {
                    numGrades--;
                    int *temp = (int *)realloc(grades, numGrades * sizeof(int));

                    grades = temp;
                    printf("The last grade is deleted\n");
                } else {
                    printf("No grades available for deleting\n");
                }
                break;

            case 4:
                break;

            default:
                printf("Invalid choice\n");
        }
    }

    free(grades);
    return 0;
}
