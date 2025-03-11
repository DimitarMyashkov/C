#include <stdio.h>
#include <stdlib.h>

void showMenu() {
    printf("\nMenu:\n");
    printf("1. Average grade\n");
    printf("2. Add a grade\n");
    printf("3. Delete last grade\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

float calculateAverage(int* grades, int count) {
    if (count == 0) return 0;
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += grades[i];
    }
    return (float)sum / count;
}

int main() {
    int numGrades;

    do {
        printf("Input the number of grades: ");
        scanf("%d", &numGrades);
        if (numGrades < 0) printf("The number of grades can't be negative\n");
    } while (numGrades < 0);

    int* grades = (numGrades > 0) ? (int*)malloc(numGrades * sizeof(int)) : NULL;
    if (numGrades > 0 && !grades) {
        printf("Error with allocating memory\n");
        return 1;
    }

    for (int i = 0; i < numGrades; ++i) {
        do {
            printf("Input a grade %d: ", i + 1);
            scanf("%d", &grades[i]);
            if (grades[i] < 2 || grades[i] > 6) {
                printf("The grade has to be between 2 and 6\n");
            }
        } while (grades[i] < 2 || grades[i] > 6);
    }

    int choice;
    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Average grade: %.2f\n", calculateAverage(grades, numGrades));
                break;

            case 2: {
                int newGrade;
                do {
                    printf("Input new grade): ");
                    scanf("%d", &newGrade);
                    if (newGrade < 2 || newGrade > 6) {
                        printf("The grade has to be between 2 and 6\n");
                    }
                } while (newGrade < 2 || newGrade > 6);

                int* temp = (int*)realloc(grades, (numGrades + 1) * sizeof(int));
                if (!temp) {
                    printf("Error with allocating memory\n");
                    break;
                }

                grades = temp;
                grades[numGrades] = newGrade;
                numGrades++;
                break;
            }

            case 3:
                if (numGrades > 0) {
                    numGrades--;
                    int* temp = (numGrades > 0) ? (int*)realloc(grades, numGrades * sizeof(int)) : NULL;
                    if (numGrades > 0 && !temp) {
                        printf("Error with allocating memory\n");
                        break;
                    }
                    grades = temp;
                    printf("The last grade is deleted\n");
                } else {
                    printf("No grades available for deleting\n");
                }
                break;

            case 4:
                printf("Exiting\n");
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    free(grades);
    return 0;
}
