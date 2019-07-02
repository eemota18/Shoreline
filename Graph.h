#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"
#define NIL 1000
#define INF  -1


// 	Exported Type --------------------------------------------------------------
typedef struct GraphObj* Graph;


// 	Constructors-Destructors ---------------------------------------------------

// 	newGraph()
// 	Returns reference to new empty Graph object.
Graph newGraph(int n);

// 	freeGraph()
// 	Frees all heap memory associated with Graph *pS, and sets *pS to NULL.
void freeGraph(Graph* pG);


// 	Access functions -----------------------------------------------------------
void printG( Graph G);
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
int getDistanceToFriend(Graph Network, int friend1, int friend2);


// 	Manipulation procedures ----------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);


// 	Other Functions ------------------------------------------------------------
void printGraph(FILE* out, Graph G);


#endif
