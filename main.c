/* A.M.D.G. */

#include "main.h"
#include "heap.h"

//QSIZE must be ≥ totalNodes; it depends on the size. 1024 is just an arbitrary example.
#define QSIZE 1024

static struct node *Qarray[QSIZE]; //for "min-priority queue" for Dijkstra

void add2Qarray(struct node *anode) {
    if (anode != NULL) {
        Qarray[totalNodes] = anode;
        totalNodes++;
    }
}

/* compare function for priority queue
 * smallest at top of priority queue heap */
int compare(const struct node *n1, const struct node *n2) {

    if (n1->d < n2->d)
        return 1;
    if (n1->d == n2->d)
        return 0;
    if (n1->d > n2->d)
        return -1;
    else
        return -1;
}

void init_global_stats() {
    totalNodes = totalLinks = 0;
}

void print_stats() {
    printf("Total nodes: %d\nlinks: %d\n", totalNodes, totalLinks);
}

/* Depth-First Search
 * (WARNING: DOES NOT COMPUTE SHORTEST PATH!) */
void DFS(struct node *n, struct node *previous) {
    struct link *currentLink;
    struct node *currentNode;
    bool swapped = false; //Have we swapped from searching parents→children or vice versa?
    bool upOrDown = false; // true = up, false = down

    if (!(currentLink = n->cfirst_link)) { //test whether there's a child; if not, look at parents
        currentLink = n->pfirst_link;
        upOrDown = true;
    }

    while (currentLink) { //go down or up in depth on all children of node n
        if (upOrDown == false)
            currentNode = currentLink->child_node;
        else
            currentNode = currentLink->parent_node;

        if (currentNode->visited == false) {
            currentNode->visited = true;
            {
                currentNode->predecessorNode = previous;
                currentNode->polymerLink = currentLink;
                DFS(currentNode, n);
            }
        } else
            return;

        if (!(currentLink = currentLink->next_link) && !swapped) { //if we run out of parent/child links, toggle upOrDown, and continue looking among child/parents
            if (upOrDown == false) {
                currentLink = n->pfirst_link;
                upOrDown = true;
            }
            else {
                currentLink = n->cfirst_link;
                upOrDown = false;
            }
            swapped = true;
        }
    }
}

/* Dijkstra search
 s = source
 u = closest to s
 v = a neighbor of u */
void Dijkstra(struct node *s) {
    //init priority queue
    Heap *Q = malloc(sizeof(Heap));
    heap_init(Q, compare, NULL);

    struct node *u, *v;
    struct link *tempLink;
    uint w, newLen;
    int i;
    bool downOrUp; // true = down, false = up

    /* INITIALIZE SINGLE SOURCE
 (For nodes that're not s, this part already initialized upon loading the program.) */
    s->d = 0; //last command of "initialize single source" (all others are "∞" or UINT_MAX in this case)

    add2Qarray(s);

    //add all nodes to priority-queue
    for (i = 0; (uint)i < totalNodes; i++)
        heap_insert(Q, Qarray[i]);

    while (Q->size != 0) { //i.e., while Q ≠ Ø

        //Extract-Min: find u closest to s (of unvisited nodes)
        heap_extract(Q, &u);

        if (u->d == UINT_MAX)
            return;
        u->visited = true;

        //Relaxation on all neighbors v of u

        //starting v's link:
        downOrUp = false;
        tempLink = u->pfirst_link;

        while (true) {
            if (!tempLink) {
                if (downOrUp)
                    break;
                if (!(tempLink = u->cfirst_link))
                    break;
                downOrUp = true;
            }
            //neighbor v of u
            if (downOrUp == true) //if we're going down
                v = tempLink->child_node;
            else if (downOrUp == false) //if we're going up
                v = tempLink->parent_node;

            w = tempLink->weight; //weight of edge (u,v)
            newLen = u->d + w;
            if (newLen < v->d) {
                v->d = newLen;

                v->successorNode = u;
                u->predecessorNode = v;
                v->polymerLink = tempLink;

                reheapify(Q,v);
            }

            //advance to next link
            tempLink = tempLink->next_link;
        }
    }
    heap_destroy(Q);
}

int main(int argc, char *argv[]) {
    init_global_stats();

    /* IMPLEMENT THE CREATION OF YOUR "2-D DOUBLY-LINKED LIST" GRAPH HERE AND RUN
     * Dijkstra(node *n);
     * or
     * DFS(node *n, node *previous);
     * on it. */

    print_stats();

    return 0;
}
