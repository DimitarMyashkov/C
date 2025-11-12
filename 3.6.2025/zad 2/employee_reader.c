#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    char name[100];
    int num_subordinates;
    struct Employee** subordinates;
} Employee;

Employee* read_employee(FILE* file) {
    Employee* emp = malloc(sizeof(Employee));
    fread(emp->name, sizeof(char), 100, file);
    fread(&emp->num_subordinates, sizeof(int), 1, file);
    if (emp->num_subordinates > 0) {
        emp->subordinates = malloc(emp->num_subordinates * sizeof(Employee*));
        for (int i = 0; i < emp->num_subordinates; i++) {
            emp->subordinates[i] = read_employee(file);
        }
    } else {
        emp->subordinates = NULL;
    }
    return emp;
}

void print_employee(Employee* emp, int level) {
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%s\n", emp->name);
    for (int i = 0; i < emp->num_subordinates; i++) {
        print_employee(emp->subordinates[i], level + 1);
    }
}

int main() {
    FILE* file = fopen("employees.bin", "rb");
    if (file == NULL) {
        printf("error opening the file");
        return 1;
    }

    Employee* root = read_employee(file);
    fclose(file);

    printf("hierarchy from the file:\n");
    print_employee(root, 0);
    free(root);
    return 0;
}
