/* A.M.D.G. */

/* heap.h/heap.c are courtesy Kyle Loudon's «Mastering Algorithms with C» ch. 10 "Heaps & Priority Queues." */

/*****************************************************************************
* *
* -------------------------------- heap.h -------------------------------- *
* *
*****************************************************************************/

#ifndef HEAP_H
#define HEAP_H

#include "datatypes.h"

/*****************************************************************************
* *
* Define a structure for heaps. *
* *
*****************************************************************************/

typedef struct Heap_ {

    int size;

    int (*compare)(const struct node *key1, const struct node *key2);
    void (*destroy)(struct node *data);

    void **tree;

} Heap;


/*****************************************************************************
* *
* --------------------------- Public Interface --------------------------- *
* *
*****************************************************************************/

void heap_init(Heap *heap, int (*compare)(const struct node *key1, const struct node *key2),
               void (*destroy)(struct node *data));

void heap_destroy(Heap *heap);

int heap_insert(Heap *heap, const struct node *data);

int heap_extract(Heap *heap, struct node **data);

//Alan's reheapify function
void reheapify(Heap *heap, struct node *n);

#define heap_size(heap) ((heap)->size)

#endif
