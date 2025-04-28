#include <stdio.h>

#define MAX_NAME_LENGTH 50

typedef struct Node {
    char firstname[MAX_NAME_LENGTH];
    struct Node *father;
    struct Node *mother;
    struct Node *marriedto;
} Node;

void printPerson(Node *person) {
    if (person == NULL) {
        printf("Person not found.\n");
        return;
    }

    printf("Name: %s\n", person->firstname);

    if (person->father != NULL)
        printf("Father: %s\n", person->father->firstname);
    else
        printf("Father: Unknown\n");

    if (person->mother != NULL)
        printf("Mother: %s\n", person->mother->firstname);
    else
        printf("Mother: Unknown\n");

    if (person->marriedto != NULL)
        printf("Married to: %s\n", person->marriedto->firstname);
    else
        printf("Married to: Not married\n");

    printf("\n");
}

int main() {
    Node grandfather = {"Hristo", NULL, NULL, NULL};
    Node grandmother = {"Ivanka", NULL, NULL, NULL};
    Node grandfather2 = {"Nikolay", NULL, NULL, NULL};
    Node grandmother2 = {"Jeni", NULL, NULL, NULL};

    Node father = {"Dimitar", &grandfather, &grandmother, NULL};
    Node mother = {"Delyana", &grandfather2, &grandmother2, NULL};

    Node me = {"Dimitar", &father, &mother, NULL};
    Node brother = {"Martin", &father, &mother, NULL};

    grandfather.marriedto = &grandmother;
    grandmother.marriedto = &grandfather;

    grandfather2.marriedto = &grandmother2;
    grandmother2.marriedto = &grandfather2;

    printf("\nFamily Tree\n\n");
    printPerson(&grandfather);
    printPerson(&grandmother);
    printPerson(&grandfather2);
    printPerson(&grandmother2);
    printPerson(&father);
    printPerson(&mother);
    printPerson(&me);
    printPerson(&brother);

    return 0;
}
