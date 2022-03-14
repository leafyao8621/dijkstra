#include "util.h"

#include <stdlib.h>

int list_initialize(struct List *list) {
    if (!list) {
        return 1;
    }
    list->size = 0;
    list->head = 0;
    list->tail = 0;
    return 0;
}

int list_push(struct List *list, uint64_t to, double distance) {
    if (!list) {
        return 1;
    }
    struct ListNode *temp = malloc(sizeof(struct ListNode));
    temp->to = to;
    temp->distance = distance;
    temp->next = 0;
    if (!list->tail) {
        list->head = temp;
    } else {
        list->tail->next = temp;
    }
    list->tail = temp;
    return 0;
}

int list_finalize(struct List *list) {
    if (!list) {
        return 1;
    }
    for (struct ListNode *i = list->head; i;) {
        struct ListNode *temp = i;
        i = i->next;
        free(temp);
    }
    return 0;
}

int list_log(struct List *list, FILE *fout) {
    if (!list || !fout) {
        return 1;
    }
    for (struct ListNode *i = list->head; i; i = i->next) {
        printf("%lu %lf\n", i->to, i->distance);
    }
    return 0;
}
