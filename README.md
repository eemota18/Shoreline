# Shoreline
Software Engineer - Language
To Compile 
1) run make
2) ./FriendNetwork


To implement the network I decided to use an undirected graph. The graph structure was built using linked list.  For example, the following graph G:
￼￼
1-------2---6
|           |   /
3---4---5/

Would be represented as follows
1: 2 3 
2: 1 4 5 6 
3: 1 4 
4: 2 3 5 
5: 2 4 6 
6: 2 5

Each vertex is represented by a linked list where its elements are the vertices connected by an edge from the source. I used my own implementation of a graph that I had done in a course and built up on it the necessary components. 

I considered two algorithms : DFS and BFS. I am more familiar and comfortable with DFS but in this case, it would not have yielded the best results. Specifically the case where there is a short distance between person A and B , DFS would likely not look at the closest neighbors at first while BFS would.
