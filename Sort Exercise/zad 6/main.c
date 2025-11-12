#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LEN 100

void merge(char str[], int left, int mid, int right, char temp[]) {
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (str[i] <= str[j]) {
            temp[k++] = str[i++];
        } else {
            temp[k++] = str[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = str[i++];
    }
    while (j <= right) {
        temp[k++] = str[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        str[i] = temp[k];
    }
}

void merge_sort(char str[], int left, int right, char temp[]) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(str, left, mid, temp);
        merge_sort(str, mid + 1, right, temp);
        merge(str, left, mid, right, temp);
    }
}

void sort_word(char word[]) {
    int len = strlen(word);
    if (len <= 1) {
        return;
    }
    char temp[MAX_LEN];
    merge_sort(word, 0, len - 1, temp);
}

int main() {
    int n;
    char words[MAX_WORDS][MAX_LEN];
    char sorted[MAX_WORDS][MAX_LEN];
    int used[MAX_WORDS] = {0};

    printf("num words: ");
    scanf("%d", &n);

    printf("words:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
        strcpy(sorted[i], words[i]);
        sort_word(sorted[i]);
    }

    printf("\ngrouped anagrams:\n");
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            continue;
        }
        used[i] = 1;
        printf("[ %s", words[i]);

        for (int j = i + 1; j < n; j++) {
            if (!used[j] && strcmp(sorted[i], sorted[j]) == 0) {
                printf(", %s", words[j]);
                used[j] = 1;
            }
        }
        printf(" ]\n");
    }

    return 0;
}
