#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdint.h>

struct ListNode {
    uint64_t to;
    double distance;
    struct ListNode *next;
};

struct List {
    uint64_t size;
    struct ListNode *head;
    struct ListNode *tail;
};

struct HeapNode {
    double key;
    uint64_t data;
};

struct Heap {
    uint64_t size, capacity;
    struct HeapNode *data, *tail;
};

int list_initialize(struct List *list);
int list_push(struct List *list, uint64_t to, double distance);
int list_finalize(struct List *list);
int list_log(struct List *list, FILE *fout);

int heap_initialize(struct Heap *heap, uint64_t capacity);
int heap_push(struct Heap *heap, double key, uint64_t data);
int heap_pop(struct Heap *heap);
int heap_finalize(struct Heap *heap);
int heap_log(struct Heap *heap, FILE *fout);

#endif
