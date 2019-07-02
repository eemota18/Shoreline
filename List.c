//-----------------------------------------------------------------------------
//  Edgar Mota
//  1593327
//  List.c
//  Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

#define MAX_LEN 160

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int Index;
} ListObj;


//  Constructors-Destructors ---------------------------------------------------

//  newNode()
//  Returns reference to new Node object. Initializes next and data fields.
//  Private.
Node newNode(int data ){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next= N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}

//  newList()
//  Return reference to new empty list object
List newList(void){
    List L;
    L = malloc( sizeof (ListObj) );
    L->front = L->back = NULL;
    L->length = 0;
    L->Index = -1;
    L->cursor = NULL;
    return(L);
}

//  freeList()
//  Frees all heap memory associated with List *pL and sets *pL to NULL.S
void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL){
        while( !isEmpty(*pL) ){
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

//  Access functions -----------------------------------------------------------


//
int isEmpty(List L){
    if(L==NULL){
        printf("List Error: List reference is NULL" );
        exit(1);
    }
    else
        return (L->length == 0);
}
//  Returns length 
int length(List L){
    return L->length;
}

//  Return cursor index if cursor is defined
//  else returns -1;
int index2(List L){
    return L->Index;

}

//  Returns front element. Pre : length()>0
int front(List L){
    if(L->length > 0){
        return L->front->data;
    }
    else{
        printf("List is empty\n");
        exit(1);
    }
}

//  Returns back element. Pre : length()>0
int back(List L){
    if(L->length > 0){
        return L->back->data;
    }
    else{
        printf("List is empty\n");
        exit(1);
    }
}

//  Returns cursor element. Pre : length()>0 and index != -1
int get(List L){

    if(L->length > 0 && L->Index != -1){
        if (!L->cursor) printf("WTF");
        //printf("appended");
        return L->cursor->data;
    }
    else{
        printf("Cursor undefined" );
        exit(1);

    }
}

//  Returns 1 for equal
//  Returns 0 for not equal
int equals(List A, List B){
    int eq = 0;
    Node n = NULL;
    Node m = NULL;

    if( A == NULL || B == NULL){
        printf("List A/B is NULL" );
        exit(1);
    }
    eq = ( A->length == B->length);
    n = A->front;
    m = B->front;
    int count = 0;
    while(eq && count < A->length){
        eq = ( n->data == m->data);
        n = n->next;
        m = m->next;    
        count++;
    }
    return eq;
}

//   Manipulation procedures ----------------------------------------------------

//  Resets this List to its original empty state
void clear(List L){
    if(L == NULL){
        printf("List Error: List reference is NULL" );
        exit(1);
    }
    else{
        while(L->length > 0)
            deleteBack(L);
    
        L->cursor = L->front = L->back = NULL;
        L->Index = -1;
        L->length = 0;
    }
}

//  If List is non-empty, places the cursor under the front elements,
//  other wise does nothing
void moveFront(List L){
    if(L->length > 0 ){
        L->cursor = L->front;
        L->Index = 0;
    }
}

void moveBack(List L){
    if(L->length > 0 ){
        L->cursor = L->back; 
        L->Index = L->length - 1;
    }
}

//  If cursor is defined and not at front, moves cursor one step toward
//  front of this List, if cursor is defined and at front, cursor becomes
//  undefined, if cursor is undefined does nothing.
void movePrev(List L){
    if( L->cursor == L->front){
        L->cursor = NULL;
        L->Index = -1;
    }
    else if( L->Index != -1){
        L->cursor = L->cursor->prev;
        L->Index = L->Index - 1; 
    }
}
  
//  If cursor is defined and not at back, moves cursor one step toward
//  back of this List, if cursor is defined and at back, cursor becomes
//  undefined, if cursor is undefined does nothing
void moveNext(List L){
    if( L->cursor == L->back ){
        L->cursor = NULL;
        L->Index = -1;
    }
    else if ( L->Index != -1) {
        L->cursor = L->cursor->next;
        L->Index = L->Index + 1;
    }
}

//  Insert new element into this List. If List is non-empty,
//  insertion takes place before front element
void prepend(List L, int data){
    Node N = newNode(data);
    if( L==NULL ){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    if(L->length == 0){
        L->front = L->back = N;
        L->front->prev = NULL;
    }
    else{
        if(L->Index != -1){
            L->Index = L->Index + 1;
        }
        L->front->prev = N;
        N->prev = NULL;
        N->next = L->front;
        L->front = N;
    }
    L->length = L->length + 1;
}

//  Insert new element into this List. If List is non-empty,
//  insertion takes place after back element.
void append(List L, int data){
    Node N = newNode(data);
    if( L==NULL ){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    if(L->length == 0){
        L->front = L->back = N;
        L->front->prev = NULL;
    }
    else{
        L->back->next = N;
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length = L->length + 1;
}

//  Insert new element before cursor.
//  Pre: length()>0, index2()>=0
void insertBefore(List L, int data){
    
    if( L->length > 0 && L->Index >= 0){
        if ( L->Index == 0){
            prepend(L,data);
            L->Index = 1;
        } 
        else{
            Node N = newNode(data);
            Node temp = L->cursor->prev;
            temp->next = N;
            N->next = L->cursor;
            N->prev = temp;
            L->cursor->prev = N;
            L->Index = L->Index + 1;
            L->length = L->length + 1;
        }
    }
}

//  Inserts new element after cursor.
//  Pre: length()>0, index2()>=0
void insertAfter(List L, int data){
    if( L->length > 0 && L->Index >= 0){
        if( L->Index == L->length -1){
            append(L,data);
        }
        else{
            Node N = newNode(data);
            N->next = L->cursor->next;
            N->prev = L->cursor;
            L->cursor->next->prev = N;
            L->cursor->next = N;
            L->length = L->length + 1;

        }
    }

}

//  Deletes the front element. Pre: length()>0
void deleteFront(List L){
    Node deleteNode = NULL;
    
    if( L == NULL){
        printf("List Error : calling deleteFront() on NULL reference \n");
        exit(1);
    }
    if(L->length == 0){
        printf("List Error : calling deleteFront() on empty List\n");
        exit(1);
    }
    
    if( L->length > 1){
        deleteNode = L->front;
        deleteNode = L->front;
        L->front = L->front->next;
    
    }
    else{
        deleteNode = L->front;
        L->front = L->back = NULL;
    }

    // Dealing with cursor
    if(L->Index == 0){
        L->Index = -1;
        L->cursor = NULL;
    }
    else if( L->cursor > 0){
        L->Index = L->Index - 1; 
    }

    L->length = L->length - 1;
    freeNode(&deleteNode);
}

void deleteBack(List L){
    Node deleteNode = NULL;
    
    if( L == NULL){
        printf("List Error : calling deleteFront() on NULL reference \n");
        exit(1);
    }
    deleteNode = L->back;
    if( L->length > 0 ){
        if (L->cursor == L->back){
            L->cursor = NULL;
            L->Index = -1;
        }
        L->back = L->back->prev;
        L->length = L->length - 1;
        freeNode(&deleteNode);
    }

}
//  Deletes cursor element, making cursor undefined.
//  Pre: length()>0, index2()>=0 

void delete(List L){
    if(L->length > 0 && L->Index >= 0 && L!=NULL){
        

        if(L->cursor == L->back){
            deleteBack(L);  

        }
        else if( L->cursor == L->front && L->length == 1){
            deleteBack(L);

        }
        else if (L->cursor == L->front ){
            deleteFront(L);
        }
        else{
            Node N = L->cursor;
            Node temp = L->cursor->prev;
            Node temp2 = L->cursor->next;
            if( temp != NULL && temp2 != NULL){
                temp->next = temp2;
                temp2->prev = temp;
            }   
            freeNode(&N);
            L->length = L->length - 1;

        }
        L->Index = -1;
        
        

    }
    
}

//  Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
    moveFront(L);
    for ( int k = 0; k < length(L) ; k++){
        fprintf(out,"%d ", get(L) );
        moveNext(L);
    }

}

List copyList(List L){
    List copy = newList();
    if(L->length == 0)
        return copy;
    if(L->length>0){
        Node temp = L->front;
        for(int i = 0 ; i<L->length;i++){
            int data = temp->data;
            append(copy,data);
            temp = temp->next;
        }
    }
    return copy;
}

List concatList(List A, List B){
    if(B->length == 0){
        return A;
    }
    else{
        Node temp = B->front;
        for(int i = 0 ; i < A->length ; i++){
            append(A,temp->data);
            temp = temp->next;
        }
    }
    return A;
}

