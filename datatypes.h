/* A.M.D.G. */

#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdbool.h>
#include <sys/types.h>

struct link {
    struct node *parent_node, *child_node; //"vertical"
    struct link *next_link, *previous_link; //doubly-linked list of links ("horizontal")

    //Dijkstra's algorithm vars
    uint weight;
};

struct node {
    //linked-list of links
    struct link *pfirst_link, *plast_link; //linked-list of links to parents
    struct link *cfirst_link, *clast_link; //linked-list of links to children

    //Dijkstra's algorithm vars
    uint d; //shortest-path estimate (upper bound on the weight of the shortest path length from source s to v) ; negative = infinite weight to vertex/node
    bool visited; //DFS search visited it? (Dijkstra updates this, but it doesn't need it.)
    //struct node *pi, *delta; //predecessor, sucessor
    struct link *polymerLink;
    struct node *predecessorNode, *successorNode;

    //heap position (ipos)
    int ipos;
};

#endif // DATATYPES_H
