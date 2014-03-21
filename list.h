#ifndef _LIST_H_
#define _LIST_H_

typedef struct GenericNode {
	void *next;
} GenericNode;

void GenericNode_add( void **root, void *new_node );
void GenericNode_next( void **current );

#define MAX_DATA (80)

typedef struct ListNode{
	struct ListNode *next;
	char *data;
}ListNode;

typedef ListNode List;

ListNode *ListNode_new( char* data );

void List_add( ListNode **root, char* data );

void List_delete( ListNode *root );

void List_print( ListNode *root );

void List_next( ListNode **current );

void List_combine( ListNode *first );

#endif
