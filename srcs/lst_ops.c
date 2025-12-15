#include "nemergent.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_llist *llist_new(int number){
    t_llist *node = (t_llist *)malloc(sizeof(t_llist));
    node->number = number;
    node->next = NULL;
    return (node);
}

void llist_add(t_llist **head, int number){
    if (!head)
        return;
    t_llist *current = *head;
    t_llist *prev = NULL;
    while (current && current->number < number){
        prev = current;
        current = current->next;
    }
    t_llist *node = llist_new(number);
    node->next = current;
    if (prev)
        prev->next = node;
    else
        *head = node;
}

void llist_print(t_llist *head){
    unsigned int i = 0;
    while(head){
        printf("node[%d] = %d\n", ++i, head->number);
        head = head->next;
    }
}