#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50000

bool is_anagram(char s[], char t[]) {
    int countS[26] = {0};
    int countT[26] = {0};

    if (strlen(s) != strlen(t)) {
        return false;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        countS[s[i] - 'a']++;
        countT[t[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (countS[i] != countT[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    char s[MAX], t[MAX];

    printf("first word: ");
    scanf("%s", s);
    printf("second word: ");
    scanf("%s", t);

    if (is_anagram(s, t)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}
