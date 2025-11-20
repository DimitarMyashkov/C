#include <stdio.h>
#include <stdlib.h>

struct node_t {
    int value;
    struct node_t* left;
    struct node_t* right;
};
typedef struct node_t node_t;

struct bst_t {
    node_t* root;
    int size;
};
typedef struct bst_t bst_t;

node_t* node_create(int value) {
    node_t* n = (node_t*)malloc(sizeof(node_t));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

bst_t* bst_create() {
    bst_t* t = (bst_t*)malloc(sizeof(bst_t));
    t->root = NULL;
    t->size = 0;
    return t;
}

int height(node_t* root) {
    if (root == NULL) {
        return 0;
    }
    int left_h = height(root->left);
    int right_h = height(root->right);
    if (left_h > right_h) {
        return left_h + 1;
    } else {
        return right_h + 1;
    }
}

int get_balance(node_t* root) {
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

int is_balanced(node_t* root) {
    if (root == NULL) {
        return 1;
    }

    int left_h = height(root->left);
    int right_h = height(root->right);

    if (abs(left_h - right_h) > 1) {
        return 0;
    }

    return is_balanced(root->left) && is_balanced(root->right);
}

node_t* rotate_right(node_t* y) {
    node_t* x = y->left;
    node_t* temp = x->right;

    x->right = y;
    y->left = temp;

    return x;
}

node_t* rotate_left(node_t* x) {
    node_t* y = x->right;
    node_t* temp = y->left;

    y->left = x;
    x->right = temp;

    return y;
}

node_t* balance(node_t* root) {
    if (root == NULL) {
        return NULL;
    }

    int balance_value = get_balance(root);

    if (balance_value > 1) {
        if (get_balance(root->left) < 0) {
            root->left = rotate_left(root->left);
        }
        return rotate_right(root);
    }

    if (balance_value < -1) {
        if (get_balance(root->right) > 0) {
            root->right = rotate_right(root->right);
        }
        return rotate_left(root);
    }

    return root;
}

node_t* bst_push_internal(node_t* root, int value) {
    if (root == NULL) {
        return node_create(value);
    }

    if (value < root->value) {
        root->left = bst_push_internal(root->left, value);
    } else if (value > root->value) {
        root->right = bst_push_internal(root->right, value);
    } else {
        return root;
    }

    return balance(root);
}

void bst_push(bst_t* t, int value) {
    t->root = bst_push_internal(t->root, value);
    t->size++;
}

void bst_print_dfs(node_t* root) {
    if (root == NULL) {
        return;
    }
    bst_print_dfs(root->left);
    printf("%d ", root->value);
    bst_print_dfs(root->right);
}

struct queue_node_t {
    node_t* tree_node;
    struct queue_node_t* next;
};
typedef struct queue_node_t queue_node_t;

struct queue_t {
    queue_node_t* front;
    queue_node_t* back;
};
typedef struct queue_t queue_t;

queue_t* queue_create() {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    q->front = NULL;
    q->back = NULL;
    return q;
}

int queue_is_empty(queue_t* q) {
    return q->front == NULL;
}

void queue_enqueue(queue_t* q, node_t* tree_node) {
    queue_node_t* new_node = (queue_node_t*)malloc(sizeof(queue_node_t));
    new_node->tree_node = tree_node;
    new_node->next = NULL;
    if (q->back != NULL) {
        q->back->next = new_node;
    }

    q->back = new_node;

    if (q->front == NULL) {
        q->front = new_node;
    }
}

node_t* queue_dequeue(queue_t* q) {
    if (queue_is_empty(q)) {
        return NULL;
    }
    queue_node_t* front = q->front;
    node_t* tree_node = front->tree_node;
    q->front = front->next;
    if (q->front == NULL) {
        q->back = NULL;
    }
    free(front);
    return tree_node;
}

void bst_print_bfs(node_t* root) {
    if (root == NULL) {
        return;
    }
    queue_t* q = queue_create();
    queue_enqueue(q, root);

    while (!queue_is_empty(q)) {
        node_t* current = queue_dequeue(q);
        if (current != NULL) {
            printf("%d ", current->value);
            queue_enqueue(q, current->left);
            queue_enqueue(q, current->right);
        } else {
            printf("N ");
        }
    }
    printf("\n");
}

int main() {
    bst_t* tree = bst_create();

    for (int i = 0; i < 10000; i++) {
        bst_push(tree, rand() % 10000);
    }

    printf("Tree after balancing:\n");
    bst_print_bfs(tree->root);

    if (is_balanced(tree->root)) {
        printf("tree = balanced\n");
    } else {
        printf("tree != balanced\n");
    }

    return 0;
}
