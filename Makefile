BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f



FriendNetwork : FriendNetwork.o $(BASE_OBJECTS)
	$(LINK) FriendNetwork FriendNetwork.o $(BASE_OBJECTS)

FriendNetwork.o : FriendNetwork.c $(HEADERS)
	$(COMPILE) FriendNetwork.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindPath FriendNetwork FriendNetwork.o $(BASE_OBJECTS)