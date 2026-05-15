#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[16];
    char var;
    char op[3];
    int value;

    struct node *left;
    struct node *right;
} node;

node *SUCCESS = NULL;
node *FAILURE = NULL;

node *get_terminal(const char* name) {
    if (strcmp(name, "S") == 0) {
        if (!SUCCESS) {
            SUCCESS = calloc(1, sizeof(node));
            strcpy(SUCCESS->name, "S");
        }
        return SUCCESS;
    }
    if (strcmp(name, "F") == 0) {
        if (!FAILURE) {
            FAILURE = calloc(1, sizeof(node));
            strcpy(FAILURE->name, "F");
        }
        return FAILURE;
    }
    return NULL;
}

node *find_node(node *root, const char* name) {
    if (!root) {
        return NULL;
    }
    if (strcmp(name, root->name) == 0) {
        return root;
    }

    node *l = find_node(root->left, name);
    if (l) {
        return l;
    }
    return find_node(root->right, name);
}



node *add_node(char *step, node *root) {
    char *tokens[32];
    int count = 0;

    char buffer[256];
    strcpy(buffer, step);

    char *tok = strtok(buffer, " ");
    while (tok) {
        tokens[count++] = tok;
        tok = strtok(NULL, " ");
    }


    char* step_name = tokens[0];
    node* current = root ? find_node(root, step_name) : NULL;

    if (!current) {
        current = calloc(1, sizeof(node));
        strcpy(current->name, step_name);
    }

    node* cursor = current;
    int i = 1;

    while (i + 4 < count) {
        cursor->var = tokens[i][0];
        strcpy(cursor->op, tokens[i + 1]);
        cursor->value = atoi(tokens[i + 2]);

        char* true_next = tokens[i + 3];
        char* false_next = tokens[i + 4];

        cursor->left = get_terminal(true_next);
        if (!cursor->left) {
            cursor->left = find_node(root, true_next);
            if (!cursor->left) {
                cursor->left = calloc(1, sizeof(node));
                strcpy(cursor->left->name, true_next);
            }
        }

        if (i + 5 < count) {
            cursor->right = calloc(1, sizeof(node));
            cursor = cursor->right;
        } else {
            cursor->right = get_terminal(false_next);
            if (!cursor->right) {
                cursor->right = find_node(root, false_next);
                if (!cursor->right) {
                    cursor->right = calloc(1, sizeof(node));
                    strcpy(cursor->right->name, false_next);
                }
            }
        }
        i += 4;
    }

    return current;
}

node *build_tree(char **steps, int step_count) {
    node *root = NULL;

    for (int i = 0; i < step_count; i++) {
        if (!root) {
            root = add_node(steps[i], NULL);
        } else {
            add_node(steps[i], root);
        }
    }
    return root;
}

int eval(node *n, int x, int y) {
    int var = (n->var == x) ? x : y;
    if (strcmp(n->op, "gt") == 0) {
        return var > n->value;
    }
    return var < n->value;
}

int is_success(node *root, int x, int y) {
    node *curr = root;

    while (curr) {
        if (strcmp(curr->name, "S") == 0) {
            return 1;
        }
        if (strcmp(curr->name, "F") == 0) {
            return 0;
        }

        if (eval(curr, x, y)) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return 0;
}

int main() {
    char *steps[] = {
        "AAA x gt 10 BBB y lt 8 CCC S",
        "BBB y gt 4 S F",
        "CCC x gt 4 DDD x lt 3 F S",
        "DDD y lt 3 S F"
    };

    node *root = build_tree(steps, 4);

    int tests[][2] = {
        {15, 5},
        {2, 2},
        {3, 2},
        {5, 10}
    };

    for (int i = 0; i < 4; i++) {
        printf("X:%d Y:%d -> %s\n",
                tests[i][0], tests[i][1],
                is_success(root, tests[i][0], tests[i][1]) ? "SUCCESS" : "FAILURE"
        );
    }

    return 0;
}