#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define FILENAME "books.txt"

typedef struct Book {
    char title[MAX_LEN];
    char author[MAX_LEN];
    char genre[MAX_LEN];
    int year;
    char isbn[MAX_LEN];
    struct Book* next;
} Book;

void loadBooks(Book** head);
void saveBooks(Book* head);
void addBook(Book** head);
void displayBooks(Book* head);
void deleteBook(Book** head, const char* isbn);
void freeList(Book* head);

int main() {
    Book* library = NULL;
    int choice;
    char isbn[MAX_LEN];

    loadBooks(&library);

    do {
        printf("\nLibrary\n");
        printf("1. Add a book\n");
        printf("2. Show all books\n");
        printf("3. Delete book by ISBN\n");
        printf("4. Save changes\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addBook(&library);
                break;
            case 2:
                displayBooks(library);
                break;
            case 3:
                printf("Input ISBN for deletion: ");
                scanf("%s", isbn);
                deleteBook(&library, isbn);
                break;
            case 4:
                saveBooks(library);
                printf("Changes are saved.\n");
                break;
            case 5:
                saveBooks(library);
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    freeList(library);
    return 0;
}

void loadBooks(Book** head) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) return;

    Book temp;
    while (fscanf(file, "%s %s %s %d %s", temp.title, temp.author, temp.genre, &temp.year, temp.isbn) == 5) {
        Book* newBook = (Book*)malloc(sizeof(Book));
        *newBook = temp;
        newBook->next = *head;
        *head = newBook;
    }

    fclose(file);
}

void saveBooks(Book* head) {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }

    while (head) {
        fprintf(file, "%s %s %s %d %s\n", head->title, head->author, head->genre, head->year, head->isbn);
        head = head->next;
    }

    fclose(file);
}

void addBook(Book** head) {
    Book* newBook = (Book*)malloc(sizeof(Book));

    printf("Title (without spaces): ");
    scanf("%s", newBook->title);
    printf("Author: ");
    scanf("%s", newBook->author);
    printf("Genre: ");
    scanf("%s", newBook->genre);
    printf("Year of publishing: ");
    scanf("%d", &newBook->year);
    printf("ISBN: ");
    scanf("%s", newBook->isbn);

    newBook->next = *head;
    *head = newBook;

    printf("Book added successfully.\n");
}

void displayBooks(Book* head) {
    if (!head) {
        printf("Library is empty.\n");
        return;
    }

    printf("\nList of books:\n");
    while (head) {
        printf("Title: %s | Author: %s | Genre: %s | Year: %d | ISBN: %s\n",
               head->title, head->author, head->genre, head->year, head->isbn);
        head = head->next;
    }
}

void deleteBook(Book** head, const char* isbn) {
    Book* current = *head;
    Book* prev = NULL;

    while (current) {
        if (strcmp(current->isbn, isbn) == 0) {
            if (prev)
                prev->next = current->next;
            else
                *head = current->next;

            free(current);
            printf("Book with ISBN %s was deleted.\n", isbn);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Book with ISBN %s was not found.\n", isbn);
}

void freeList(Book* head) {
    while (head) {
        Book* temp = head;
        head = head->next;
        free(temp);
    }
}
