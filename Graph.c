#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// 	private GraphObj type
typedef struct GraphObj{
    List *arrayList; // for each vertex
    char *color; // color : white, gray or black 
    int *distance; // array of distaces from source vector
    int *parentV; // parent vector
    int order; // number of vertices
    int size; // number of edges
    int source; // starting point
    
    
} GraphObj;


// 	Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n){
    Graph G;
    
    // intializing values
    G = (Graph)malloc(sizeof(GraphObj));
    G->distance = (int*)malloc(sizeof(int) * (n + 1));
    G->color = (char*)malloc(sizeof(char) * (n+ 1));
    G->parentV = (int*)malloc(sizeof(int) * (n + 1));
    G->arrayList = (List*)malloc(sizeof(List) * (n + 1));
    
    G->order = n;
    G-> size = 0;
    G-> source = NIL;
    
    for ( int i = 1 ; i <= n ; i++){
        G->arrayList[i] = newList();
    }
       
    return G;
    
}
void freeGraph(Graph* pG){
    // free up memory
    free((*pG)->distance);
    free((*pG)->color);
    free((*pG)->parentV);
    for(int i = 1; i < getOrder(*pG)+1 ; i++){
        freeList(&(*pG)->arrayList[i]);
    }
    free((*pG)->arrayList);

    free(*pG);
    *pG = NULL;
}

// 	Access functions -----------------------------------------------------------

int getOrder(Graph G){
    return G->order;
}
int getSize(Graph G){
    return G->size;
}

int getSource(Graph G){
	return G->source;
}

int getParent(Graph G, int u){
	if( getSource(G)!= NIL && u >= 1 && u <= getOrder(G) ){
		return G->parentV[u];
	}
    else
        return NIL;
}

int getDist(Graph G, int u){
    if(getSource(G) != NIL)
        return G->distance[u];
    else
        return INF;
}

void getPath(List L, Graph G, int u){
	if( getSource(G) != NIL && u >= 1 && u <= getOrder(G) ){
		if( u == getSource(G) ){
			append(L,u);
		}
		else if (getParent(G,u) == NIL){
			append(L,NIL);
		}
		else{
			getPath(L,G,getParent(G,u));
			append(L,u);
		}
	}
}


// 	Manipulation procedures ----------------------------------------------------

void printGraph(FILE *out ,Graph G){
    for (int i = 1 ; i <= G->order ; i++ ){
        moveFront(G->arrayList[i]);
        
        if( !isEmpty(G->arrayList[i]) ){
            fprintf(out,"%d: ", i);
	        while( index2(G->arrayList[i]) != -1 ){
        		fprintf(out,"%d ", get(G->arrayList[i]) );
	            moveNext(G->arrayList[i]);
	        }
	        fprintf(out,"\n");
    	}
    }
}

void printG(Graph G){
    for (int i = 1 ; i <= G->order ; i++ ){
        moveFront(G->arrayList[i]);
        
        if( !isEmpty(G->arrayList[i]) ){
            printf("%d: ", i);
            while( index2(G->arrayList[i]) != -1 ){
                printf("%d ", get(G->arrayList[i]) );
                moveNext(G->arrayList[i]);
            }
            printf("\n");
        }
    }
}

void makeNull(Graph G){
    for( int i=1 ; i <= getOrder(G) ; i++  ){
        clear(G->arrayList[i]);
    }
}

void addEdge(Graph G, int u, int v){
    addArc(G,u,v);
    addArc(G,v,u);
    int temp = G->size;
    G->size = temp-1;
    
}

void addArc(Graph G, int u, int v){
    int control = 0;
    if( u >= 1 && u<=getOrder(G) ){
        moveFront(G->arrayList[u]);
        if( length(G->arrayList[u]) == 0){
            append(G->arrayList[u],v);
            G->size++;
            control = 1;
        }
        while (index2(G->arrayList[u])!=-1 && control==0){
            if(get(G->arrayList[u]) > v){
                insertBefore(G->arrayList[u],v);
                G->size++;
                control = 1;
            }
            else
                moveNext(G->arrayList[u]);
        }
        
        if(control == 0){
            append(G->arrayList[u],v);
            G->size++;
        }
    }

}

void BFS(Graph G, int s){
    // 174 - 185 : Initialize vertices
    for (int i = 1 ; i <= getOrder(G) ; i++){
        if( i != s){
            G->color[i] = 'w';
            G->distance[i] = INF;
            G->parentV[i] = NIL;
        }
    }
    
    G->source = s;
    G->color[s] = 'g';
    G->distance[s] = 0;
    G->parentV[s] = NIL;
    
    // 188- 190 : Initialize FIFO queue
    List Q = NULL;
    Q = newList();
    append(Q,s);
    int i;

    // 197 - end : Explore the Graph
    // w - undiscovered
    // g - frontier
    // b - finished
    while( !isEmpty(Q)){
        moveFront(Q);
        i = get(Q);
        deleteFront(Q);
                 
    	moveFront(G->arrayList[i]);
        while(index2(G->arrayList[i]) != -1 ){
            if(G->color[get(G->arrayList[i])] == 'w'){
                G->color[get(G->arrayList[i])] = 'g';
                G->distance[get(G->arrayList[i])] = G->distance[i] + 1;
                G->parentV[get(G->arrayList[i])] = i;
                append(Q,get(G->arrayList[i]));	
                moveNext(G->arrayList[i]);
            }
            else
                moveNext(G->arrayList[i]);
        }           
        G->color[i] = 'b';
    }
    freeList(&Q);
    
    
}
// BFS and getPath get the number of edges between 
// 2 vertices. In a social network, the number of friends
// between would be = edges - 1
// -1 for friend1 = friend2
// -2 for empty Network
// -3 for one of the two friends is not in the network
int getDistanceToFriend(Graph Network, int friend1, int friend2){
    if (friend1 > Network->order || friend2 > Network->order )
        return -3;
    if(Network->size == 0)
        return -2;
    if(friend1 == friend2)
        return -1;
    List L =newList();
    BFS(Network,friend1);
    getPath(L,Network,friend2);

    return getDist(Network,friend2) - 1;
}
