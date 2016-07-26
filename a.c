#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node_t {
    int key;
    struct node_t *parent;
    struct node_t *left;
    struct node_t *right;
    int balence;
} Node;

Node *root = NULL;

Node* new_node() {
    Node *new = (Node*) malloc(sizeof(Node));
    new->left = new->right = new->parent = NULL;
    new->key = new->balence = 0;
    return new;
}

int power(int s, int p) {
    p--;
    if (p == -1) {
        return 1;
    } else if (p == 0) {
        return s;
    }
    return power(s * 2, p);
}

Node* get_biggest_node(Node *node) {
    if (!node->right) {
        return node;
    }
    return get_biggest_node(node->right);
}

void insert_internal(Node *node, int key) {
    if (node->key == key) {
        printf("already exist\n");
    } else if (key > node->key) {
        if (node->right) {
            insert_internal(node->right, key);
        } else {
            Node *new = new_node();
            new->key = key;
            new->parent = node;
            node->right = new;
        }
    } else if (key < node->key) {
        if (node->left) {
            insert_internal(node->left, key);
        } else {
            Node *new = new_node();
            new->key = key;
            new->parent = node;
            node->left = new;
        }
    }
}

void insert_key(int key) {
    if (!root) {
        Node *new = new_node();
        new->key = key;
        root = new;
        return;
    }
    insert_internal(root, key);
}

void remove_internal(Node *node, int key) {
    if (!node) {
        printf("node is NULL\n");
    } else if (node->key == key) {
        if ((node->left == NULL) && (node->right == NULL)) {
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
            free(node);
        } else {
            if ((node->left != NULL) && (node->right != NULL)) {
                Node *biggest_node = get_biggest_node(node->left);
                node->key = biggest_node->key;
                if (node->parent->left == biggest_node) {
                     node->parent->left = NULL;
                } else {
                    node->parent->right = NULL;
                }
            } else if (node->left != NULL) {
                if (node->parent->left == node) {
                    node->parent->left = node->left;
                } else {
                    node->parent->right = node->left;
                }
                free(node);
            } else {
                if (node->parent->left == node) {
                    node->parent->left = node->right;
                } else {
                    node->parent->right = node->right;
                }
                free(node);
            }
        }
    } else if (key > node->key) {
        remove_internal(node->right, key);
    } else if (key < node->key) {
        remove_internal(node->left, key);
    }
}

void remove_key(int key) {
    remove_internal(root, key);
}

void print() {
    if (!root) {
        return;
    }

    int deps = 0;
    int need_next = 1;
    Node **print_queue = NULL;
    Node **next_print_queue = NULL;
    while (need_next) {
        if (deps == 0) {
            print_queue = (Node**) calloc(1, sizeof(Node*));
            print_queue[0] = root;
        }
        char buf[200] = {0x00,};
        int next_node_size = power(2, deps+1);
        next_print_queue = (Node**) calloc(next_node_size, sizeof(Node*));

        int i;
        for (i = 0; i < 199; i++) {
            buf[i] = ' ';
        }

        int j = 0;
        int node_cnt = power(2, deps);
        char temp[3];
        for (j = 0; j < node_cnt; j++) {
            if (print_queue[j]) {
                sprintf(temp, "%02d", print_queue[j]->key);
                memcpy(&buf[(int)(100 + (j - node_cnt/2.0)*4)], temp, 2);

                next_print_queue[2*j] = print_queue[j]->left;
                next_print_queue[2*j+1] = print_queue[j]->right;
            } else {
                sprintf(temp, "%02d", 0);
                memcpy(&buf[(int)(100 + (j - node_cnt/2.0)*4)], temp, 2);

                next_print_queue[2*j] = NULL;
                next_print_queue[2*j+1] = NULL;
            }
        }
        if (print_queue) {
            free(print_queue);
        }
        printf("%s\n", buf);

        need_next = 0;
        for (i = 0; i < next_node_size; i++) {
            if (next_print_queue[i] != NULL) {
                need_next = 1;
                break;
            }
        }

        if (need_next) {
            deps++;
            print_queue = next_print_queue;
        } else {
            if (next_print_queue) {
                free(next_print_queue);
            }
        }
    }
}

int main(void) {
    insert_key(15);
    insert_key(3);
    insert_key(10);
    insert_key(5);
    insert_key(1);
    insert_key(21);
    insert_key(30);
    insert_key(19);
    insert_key(8);
    insert_key(7);
    insert_key(1);
    insert_key(67);
    insert_key(90);
    print();

    return 0;
}

