#include <stdio.h>

enum DayOfWeek {
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

int main() {
    int dayNumber;

    printf("input a day of the week (1-7): ");
    scanf("%d", &dayNumber);

    if (dayNumber >= 1 && dayNumber <= 7) {
        enum DayOfWeek day = dayNumber;

        switch (day) {
            case Monday:
                printf("The day is: Monday\n");
                break;
            case Tuesday:
                printf("the day is: Tuesday\n");
                break;
            case Wednesday:
                printf("the day is: Wednesday\n");
                break;
            case Thursday:
                printf("the day is: Thursday\n");
                break;
            case Friday:
                printf("the day is: Friday\n");
                break;
            case Saturday:
                printf("the day is: Saturday\n");
                break;
            case Sunday:
                printf("the day is: Sunday\n");
                break;
        }
    } else {
        printf("invalid input\n");
    }

    return 0;
}
