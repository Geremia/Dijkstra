/* A.M.D.G. */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "datatypes.h"

bool DEBUG;

//Global counters
uint totalNodes = 0, totalLinks = 0;

//Functions
void init_global_stats();
void print_stats();

void add2Qarray(struct node *anode);
int compare(const struct node *n1, const struct node *n2);

void DFS(struct node *n, struct node *previous);
void Dijkstra(struct node *n);

#endif
