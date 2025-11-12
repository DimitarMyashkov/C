#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    char name[100];
    int num_subordinates;
    struct Employee** subordinates;
} Employee;

Employee* create_employee(const char* name) {
    Employee* emp = malloc(sizeof(Employee));
    strncpy(emp->name, name, 100);
    emp->num_subordinates = 0;
    emp->subordinates = NULL;
    return emp;
}

void add_subordinate(Employee* manager, Employee* subordinate) {
    manager->num_subordinates++;
    manager->subordinates = realloc(manager->subordinates, manager->num_subordinates * sizeof(Employee*));
    manager->subordinates[manager->num_subordinates - 1] = subordinate;
}

void write_employee(FILE* file, Employee* emp) {
    fwrite(emp->name, sizeof(char), 100, file);
    fwrite(&emp->num_subordinates, sizeof(int), 1, file);
    for (int i = 0; i < emp->num_subordinates; i++) {
        write_employee(file, emp->subordinates[i]);
    }
}

int main() {
    Employee* w1 = create_employee("Employee 1");
    Employee* w2 = create_employee("Employee 2");
    Employee* w3 = create_employee("Employee 3");
    Employee* w4 = create_employee("Employee 4");
    Employee* w5 = create_employee("Employee 5");
    Employee* w6 = create_employee("Employee 6");

    Employee* m1 = create_employee("Manager 1");
    add_subordinate(m1, w1);
    add_subordinate(m1, w2);
    add_subordinate(m1, w3);

    Employee* m2 = create_employee("Manager 2");
    add_subordinate(m2, w4);
    add_subordinate(m2, w5);
    add_subordinate(m2, w6);

    Employee* director = create_employee("Supervisor");
    add_subordinate(director, m1);
    add_subordinate(director, m2);

    FILE* file = fopen("employees.bin", "wb");
    if (file == NULL) {
        printf("error opening the file");
        return 1;
    }
    write_employee(file, director);
    fclose(file);

    printf("hierarchy documented successfully in employees.bin\n");
    return 0;
}
