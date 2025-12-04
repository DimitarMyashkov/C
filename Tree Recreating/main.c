#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;

Node* node_create(int value) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct Tree {
    Node* root;
    int size;
};
typedef struct Tree Tree;

Tree* tree_create() {
    Tree* s = (Tree*)malloc(sizeof(Tree));
    s->root = NULL;
    s->size = 0;
    return s;
}

Node* push_internal(Node* root, int value) {
    if(root == NULL) {
        return node_create(value);
    }

    if(value < root->value) {
        root->left = push_internal(root->left, value);
    } else if(value > root->value) {
        root->right = push_internal(root->right, value);
    }
    return root;
}

void bst_push(Tree* s, int value) {
    s->root = push_internal(s->root, value);
    s->size++;
}

void print_dfs(Node* root) {
    if(root == NULL) {
        return;
    }

    print_dfs(root->left);
    printf("%d ", root->value);
    print_dfs(root->right);
}

struct queue_Node {
    Node* tree_node;
    struct queue_Node* next;
};

typedef struct queue_Node queue_Node;

struct queue_t {
    queue_Node* front;
    queue_Node* back;
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

void queue_enqueue(queue_t* q, Node* tree_node) {
    queue_Node* new_node = (queue_Node*)malloc(sizeof(queue_Node));
    new_node->tree_node = tree_node;
    new_node->next = NULL;

    if(q->back != NULL) {
        q->back->next = new_node;
    }
    q->back = new_node;

    if(q->front == NULL) {
        q->front = new_node;
    }
}

Node* queue_dequeue(queue_t* q) {
    if(queue_is_empty(q)) {
        return NULL;
    }

    queue_Node* front_node = q->front;
    Node* tree_node = front_node->tree_node;
    q->front = front_node->next;

    if(q->front == NULL) {
        q->back = NULL;
    }

    free(front_node);
    return tree_node;
}

void print_bfs(Node* root) {
    if(root == NULL) {
        return;
    }

    queue_t* q = queue_create();
    queue_t* temp = queue_create();
    queue_enqueue(q, root);
    while(!queue_is_empty(q)) {
        Node* current = queue_dequeue(q);

        if(current == NULL) {
            printf("N ");
            continue;
        }

        printf("%d ", current->value);

        queue_enqueue(temp, current->left);
        queue_enqueue(temp, current->right);

        if(queue_is_empty(q)) {
            queue_t* swap = q;
            q = temp;
            temp = swap;
            printf("\n");
        }
    }
}

Node *build_in(int *arr, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;

    Node *root = node_create(arr[mid]);
    root->left = build_in(arr, start, mid - 1);
    root->right = build_in(arr, mid + 1, end);

    return root;
}

Tree *recreate_in(int *arr, int size) {
    Tree *t = tree_create();
    t->root = build_in(arr, 0, size - 1);
    t->size = size;

    return t;
}

Node *build_pre(int *arr, int start, int end) {
    if (start > end) {
        return NULL;
    }

    Node *root = node_create(arr[start]);

    int split = start + 1;

    while (split <= end && arr[split] < root->value) {
        split++;
    }

    root->left = build_pre(arr, start + 1, split - 1);
    root->right = build_pre(arr, split, end);

    return root;
}

Tree *recreate_pre(int *arr, int size) {
        Tree *t = tree_create();
        t->root = build_pre(arr, 0, size - 1);
        t->size = size;

        return t;
}

Node *build_post(int *arr, int start, int end) {
    if (start > end) {
        return NULL;
    }

    Node *root = node_create(arr[end]);

    int split = end - 1;

    while (split >= start && arr[split] > root->value) {
        split--;
    }

    root->left = build_post(arr, start, split);
    root->right = build_post(arr, split + 1, end - 1);

    return root;
}

Tree *recreate_post(int *arr, int size) {
    Tree *t = tree_create();
    t->root = build_post(arr, 0, size - 1);
    t->size = size;

    return t;
}

int main() {
    int in_arr[] = {2, 5, 8, 10, 12, 15, 18};
    int pre_arr[] = {10, 5, 2, 8, 15, 12, 18};
    int post_arr[] = {2, 8, 5, 12, 18, 15, 10};
    
    Tree *in_t = recreate_in(in_arr, 7);
    print_bfs(in_t->root);
    printf("\n\n");

    Tree *pre_t = recreate_pre(pre_arr, 7);
    print_bfs(pre_t->root);
    printf("\n\n");

    Tree *post_t = recreate_post(post_arr, 7);
    print_bfs(post_t->root);
    printf("\n\n");

    free(in_t);
    free(pre_t);
    free(post_t);

    return 0;
}