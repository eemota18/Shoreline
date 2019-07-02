//-----------------------------------------------------------------------------
// 	Edgar Mota
//	pa4
//  eemota
//	List.h
// 	Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// 	Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// 	Constructors-Destructors ---------------------------------------------------

// 	newList()
// 	Returns reference to new empty List object. 
List newList(void);

//	freeList()
// 	Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pL);

// 	Access functions -----------------------------------------------------------

int isEmpty(List L);
//	Returns length 
int length(List L);

//	Return cursor index if cursor is defined
//	else returns -1;
int index2(List L);

//	Returns front element. Pre : length()>0
int front(List L);

//	Returns back element. Pre : length()>0
int back(List L);

//	Returns cursor element. Pre : length()>0 and index != -1
int get(List L);

//	Returns 1 for equal
//	Returns 0 for not equal
int equals(List A, List B);

//	 Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// 	Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);
List concatList(List A, List B);

#endif

