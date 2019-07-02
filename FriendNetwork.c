#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

/*
To implement the network I decided to use an undirected graph. The graph structure was built using linked list
Each vertex is represented by a linked list where its elements are the vertices connected by an edge from the 
source. I used my own implementation of a graph that I had done in a course and built up on it the necessary components. 

I considered two algorithms : DFS and BFS. I am more familiar and comfortable with DFS but in this case, it would not 
have yielded the best results. Specifically the case where there is a short distance between person A and B , DFS would 
likely not look at the closest neighbors at first while BFS would.

My function is callled getDistanceToFriend
Takes 3 parameters: Network(Type:Graph),friend1(vertex#-int-corresponding to a friend),friend2(vertex#-int-corresponding to a friend)
Returns:
    -1 - friend1 = friend2
    -2 - empty Network
    -3 - one of the friends is not in the network 
*/


int main(){
    int dist = -1;
    Graph G = newGraph(6);
    addEdge(G,1,2);
    addEdge(G,1,3);
    addEdge(G,2,4);
    addEdge(G,2,5);
    addEdge(G,2,6);
    addEdge(G,3,4);
    addEdge(G,4,5);
    addEdge(G,5,6);
    printG(G);
    List L =newList();

    BFS(G,1);   
    printf("\nSource: 1\nTest with destination: 5\n");
    getPath(L,G,5);
    printf("Distance(edges) : %d\n",getDist(G,5) );
    dist = getDistanceToFriend(G,1,5);
    printf("Distance using getDistanceToFriend: %d\n", dist);
    clear(L);

    BFS(G,1);   
    printf("\nSource: 1\nTest with destination: 2\n");
    getPath(L,G,2);
    printf("Distance(edges) : %d\n",getDist(G,2) );
    dist = getDistanceToFriend(G,1,2);
    printf("Distance using getDistanceToFriend: %d\n", dist);
    clear(L);

    printf("\nSource: 3\nTest with destination: 6\n");
    BFS(G,3);  
    getPath(L,G,6);
    printf("Distance(edges) : %d\n",getDist(G,6) );
    dist = getDistanceToFriend(G,3,6);
    printf("Distance using getDistanceToFriend: %d\n", dist);
    clear(L);

    printf("\nSource: 3\nTest with destination: 4\n");
    BFS(G,3);  
    getPath(L,G,4);
    printf("Distance(edges) : %d\n",getDist(G,4) );
    dist = getDistanceToFriend(G,3,4);
    printf("Distance using getDistanceToFriend: %d\n", dist);
    clear(L);

    printf("\nSource: 3\nTest with destination: 3\n");
    BFS(G,3);  
    getPath(L,G,3);
    printf("Distance(edges) : %d\n",getDist(G,3) );
    dist = getDistanceToFriend(G,3,3);
    printf("Distance using getDistanceToFriend: %d\n", dist);
    clear(L);

    BFS(G,2);
    printf("\nSource: 2\nTest with destination: 3\n");
    getPath(L,G,3);
    printf("Distance(edges) : %d\n",getDist(G,3) );
    dist = getDistanceToFriend(G,2,3);
    printf("Distance using getDistanceToFriend: %d\n", dist);
    clear(L);
    
    printf("\nTest for one of friends not in the Network\n");
    dist = getDistanceToFriend(G,2,10);
    printf("Distance using getDistanceToFriend: %d\n", dist);

   printf("\nTest for both of friends not in the Network\n");
    dist = getDistanceToFriend(G,18,10);
    printf("Distance using getDistanceToFriend: %d\n", dist); 

    return 0;
}
