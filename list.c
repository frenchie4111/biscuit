#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void GenericNode_add( void **root, void *new_node ) {
	GenericNode **current = (GenericNode **)root;
	
	while( (*current) ) {
		current = (GenericNode **)&((*current)->next);
	}

	(*current) = new_node;
}

void GenericNode_next( void **current ) {
	if( (*current) ) {
		(*current) = ((GenericNode *)(*current))->next;
	}
}

ListNode *ListNode_new( char* data ) {
	ListNode *new_node = (ListNode *)malloc( sizeof( ListNode ) );

	char *new_data = (char *)malloc( sizeof( char ) * MAX_DATA );
	strcpy( new_data, data );

	new_node->data = new_data;
	new_node->next = NULL;
	return new_node;
}

void List_add( ListNode **root, char* data ) {
	GenericNode_add( (void **)root, ListNode_new( data ) );
}

void ListNode_delete( ListNode *node ) {
	free( node->data );
	free( node );
}

void List_delete( ListNode *root ) {
	while( root ) {
		ListNode *temp = root->next;

		ListNode_delete( root );

		root = temp;
	}
}
void List_print( ListNode *root ) {
	ListNode *currentNode = root;

	while( currentNode ) {
		printf("<%s>\n", currentNode->data );
		currentNode = currentNode->next;
	}
}

void List_next( ListNode **current ) {
	GenericNode_next( (void**)current );
}

/**
 * Combines two sequential tokens
 */
void List_combine( ListNode *first ) {
	ListNode *second = first->next;
	char *new_data = (char *)malloc( sizeof( char ) * MAX_DATA );

	strcpy( new_data, first->data );
	strcat( new_data, second->data );

	first->data = new_data;
	first->next = second->next;
}
