#include "core/core.h"

int main(void) {
    struct Heap heap;
    heap_initialize(&heap, 2);
    double key[5] = {
        5,
        1,
        2,
        3,
        4
    };
    uint64_t data[5] = {
        5,
        1,
        2,
        3,
        4
    };
    for (uint64_t i = 0; i < 5; ++i) {
        heap_push(&heap, key[i], data[i]);
    }
    heap_log(&heap, stdout);
    for (uint64_t i = 0; i < 5; ++i) {
        printf("iteration %lu:\n", i);
        heap_pop(&heap);
        heap_log(&heap, stdout);
    }
    heap_finalize(&heap);
    return 0;
}
