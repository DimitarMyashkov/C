#include <stdio.h>
#include <stdbool.h>

#define MAX_TITLE_LENGTH 25
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_NAME_LENGTH 15
#define MAX_EMAIL_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 15
#define MAX_VOLUNTEERS 100

typedef struct {
    int hour;
    int minute;
} Time;


typedef struct {
    char firstName[MAX_NAME_LENGTH + 1];
    char secondName[MAX_NAME_LENGTH + 1];
    char thirdName[MAX_NAME_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
    char phoneNumber[MAX_PHONE_NUMBER_LENGTH + 1];
} Volunteer;

typedef struct {
    bool answer;
    Volunteer volunteer;
} Response;

typedef struct {
    char title[MAX_TITLE_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    struct {
        int day;
        int month;
        int year;
        Time time;
    } date;
    Response responses[MAX_VOLUNTEERS];
    int responseCount;
} Cause;

void printTime(Time time) {
    printf("%02d:%02d", time.hour, time.minute);
}

void printDate(const void *date_ptr) {
    const struct {
        int day;
        int month;
        int year;
        Time time;
    } *date = date_ptr;

    printf("%02d/%02d/%04d ", date->day, date->month, date->year);
    printTime(date->time);
}

void printVolunteer(Volunteer v) {
    printf("Name: %s %s %s\n", v.firstName, v.secondName, v.thirdName);
    printf("Email: %s\n", v.email);
    printf("Phone: %s\n", v.phoneNumber);
}

void printResponse(Response r) {
    printVolunteer(r.volunteer);
    printf("Will participate: %s\n", r.answer ? "Yes" : "No");
}

void printCause(Cause c) {
    printf("Title: %s\n", c.title);
    printf("Description: %s\n", c.description);
    printf("Date: ");
    printDate(&c.date);
    printf("\nParticipants:\n");
    for (int i = 0; i < c.responseCount; i++) {
        printf("\nParticipant %d:\n", i + 1);
        printResponse(c.responses[i]);
    }
}

int main() {
    Cause causes[2];

    Volunteer Dimitar = {
            .firstName = "Dimitar",
            .secondName = "Dimitrov",
            .thirdName = "Myashkov",
            .email = "mitkomyashkov@gmail.com",
            .phoneNumber = "+359889400669"
    };

    Volunteer Martin = {
            .firstName = "Martin",
            .secondName = "Miroslavov",
            .thirdName = "Nedkov",
            .email = "nedibrazil@gmail.com",
            .phoneNumber = "+359888149716"
    };

    Volunteer Stefan = {
            .firstName = "Stefan",
            .secondName = "Stefanov",
            .thirdName = "Yanakiev",
            .email = "stefan.yanakiev@gmail.com",
            .phoneNumber = "+359889123456"
    };

    Volunteer Ivan = {
            .firstName = "Ivan",
            .secondName = "Hristov",
            .thirdName = "Kostov",
            .email = "ivan.kostov@gmail.com",
            .phoneNumber = "+359887654321"
    };

    Response response1 = {true, Dimitar};
    Response response2 = {false, Martin};
    Response response3 = {true, Stefan};
    Response response4 = {true, Ivan};

    causes[0] = (Cause) {
            .title = "Help the turtles",
            .description = "Collecting trash from the ocean",
            .date = {.day = 15, .month = 6, .year = 2025, .time = {.hour = 10, .minute = 30}},
            .responses = { response1, response2 },
            .responseCount = 2
    };

    causes[1] = (Cause) {
            .title ="Plant trees",
            .description = "Tree planting event for a greener city",
            .date = {.day = 22, .month = 4, .year = 2025, .time = {.hour = 9, .minute = 0}},
            .responses = {response3, response4},
            .responseCount = 2
    };

    for (int i = 0; i < 2; i++) {
        printf("\n=== Cause %d ===\n", i + 1);
        printCause(causes[i]);
        printf("\n");
    }

    return 0;
}
