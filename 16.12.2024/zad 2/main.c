//zad 2
#include <stdio.h>

int main() {
    int lights[8] = {0};
    int choice;

    while (1) {
        printf("\n1. Switch lights\n");
        printf("2. Show lights\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter room number (1-8, end with 0): ");
            while (1) {
                int room;
                scanf("%d", &room);

                if (room == 0) {
                    break;
                } else if (room >= 1 && room <= 8) {
                    lights[room - 1] = 1 - lights[room - 1];
                    printf("Light in room %d is now %s.\n", room, lights[room - 1] == 1 ? "ON" : "OFF");
                } else {
                    printf("Invalid room number.\n");
                }
            }
        } else if (choice == 2) {
            printf("Lights are ON in rooms: ");
            int any_on = 0;
            for (int i = 0; i < 8; i++) {
                if (lights[i]) {
                    printf("%d ", i + 1);
                    any_on = 1;
                }
            }
            if (!any_on) printf("None");
            printf("\n");
        } else if (choice == 3) {
            printf("Exiting. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
