#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EGN_LENGTH 11

typedef struct {
    char **data;
    int size;
    int capacity;
} DynamicArray;

void initArray(DynamicArray *arr, int capacity) {
    arr->data = (char **)malloc(capacity * sizeof(char *));
    arr->size = 0;
    arr->capacity = capacity;
}

void append(DynamicArray *arr, const char *egn) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (char **)realloc(arr->data, arr->capacity * sizeof(char *));
    }
    arr->data[arr->size] = (char *)malloc((EGN_LENGTH + 1) * sizeof(char));
    strcpy(arr->data[arr->size], egn);
    arr->size++;
}

int find_index(DynamicArray *arr, const char *egn) {
    for (int i = 0; i < arr->size; i++) {
        if (strcmp(arr->data[i], egn) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_by_egn(DynamicArray *arr, const char *egn) {
    int index = find_index(arr, egn);
    if (index == -1) {
        printf("Donor with EGN %s can't be found.\n", egn);
        return;
    }

    free(arr->data[index]);

    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
    printf("Donor with EGN %s was removed.\n", egn);
}

void print_all(DynamicArray *arr) {
    if (arr->size == 0) {
        printf("No documented donors.\n");
        return;
    }

    printf("List of donors:\n");
    for (int i = 0; i < arr->size; i++) {
        printf("%d. %s\n", i + 1, arr->data[i]);
    }
}

void freeArray(DynamicArray *arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->data[i]);
    }
    free(arr->data);
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Add donor\n");
    printf("2. Remove donor by EGN\n");
    printf("3. Show donors\n");
    printf("4. Exit\n");
    printf("Choice: ");
}

int main() {
    DynamicArray donors;
    initArray(&donors, 4);

    int choice;
    char egn[EGN_LENGTH + 1];

    do {
        menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Input EGN (10 numbers): ");
                fgets(egn, sizeof(egn), stdin);
                egn[strcspn(egn, "\n")] = '\0';
                if (strlen(egn) == 10) {
                    append(&donors, egn);
                    printf("Donor with EGN %s was added.\n", egn);
                } else {
                    printf("Invalid Egn. Has to be 10 numbers long.\n");
                }
                break;
            case 2:
                printf("Enter EGN for removal: ");
                fgets(egn, sizeof(egn), stdin);
                egn[strcspn(egn, "\n")] = '\0';
                remove_by_egn(&donors, egn);
                break;
            case 3:
                print_all(&donors);
                break;
            case 4:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    freeArray(&donors);
    return 0;
}
