#include "util.h"

#include <stdlib.h>

int heap_initialize(struct Heap *heap, uint64_t capacity) {
    if (!heap) {
        return 1;
    }
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = malloc(sizeof(struct HeapNode) * capacity);
    heap->tail = heap->data;
    return 0;
}

static void swap(struct HeapNode *a, struct HeapNode *b) {
    struct HeapNode c = *a;
    *a = *b;
    *b = c;
}

static void heapify_up(struct HeapNode *data, uint64_t size) {
    for (uint64_t i = size; i > 1; i >>= 1) {
        if (data[i - 1].key < data[(i >> 1) - 1].key) {
            swap(data + i - 1, data + (i >> 1) - 1);
        } else {
            break;
        }
    }
}

int heap_push(struct Heap *heap, double key, uint64_t data) {
    if (!heap) {
        return 1;
    }
    if (heap->size == heap->capacity) {
        heap->capacity <<= 1;
        heap->data =
            realloc(heap->data, sizeof(struct HeapNode) * heap->capacity);
        heap->tail = heap->data + heap->size;
    }
    ++heap->size;
    heap->tail->key = key;
    heap->tail->data = data;
    ++heap->tail;
    heapify_up(heap->data, heap->size);
    return 0;
}

int heap_finalize(struct Heap *heap) {
    if (!heap) {
        return 1;
    }
    free(heap->data);
    return 0;
}

int heap_log(struct Heap *heap, FILE *fout) {
    if (!heap || !fout) {
        return 1;
    }
    struct HeapNode *iter = heap->data;
    for (uint64_t i = 0; i < heap->size; ++i, ++iter) {
        printf("%lf %lu\n", iter->key, iter->data);
    }
    return 0;
}
