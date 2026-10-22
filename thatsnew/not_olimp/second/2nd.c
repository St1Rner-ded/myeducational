#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void append (Node **head, int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf (stderr, "Ошибка памяти!\n");
        exit(1);
    }
    new_node->value = value;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void print_list (Node *head) {
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf ("\n");
}

void free_list (Node **head) {
    while (*head != NULL) {
        Node *current = *head;
        Node *cur_next = current->next;
        free (current);
        *head = cur_next;
    }
}

void reverse_list (Node **head) {
    Node *prev = NULL, *current = *head, *next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

int main (void) {
    //здесь моя главная функция
    Node *head = NULL;
    for (int i = 0; i < 5; ++i) {
        append (&head, i * 5);
    }
    print_list (head);
    reverse_list (&head);
    print_list (head);
    free_list (&head);
    return 0;
}