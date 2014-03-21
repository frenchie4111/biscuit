#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "programlist.h"
#include "list.h"
#include "tokenizer.h"

int is_type( char *string ) {
	// TODO: List of seen types
	return !strcmp( string, "int" ) ||
		   !strcmp( string, "char*");
}

int is_operation( char *string ) {
	return 	is_type( string ) ||
			is_seperator( string[0] );
}

TreeNode *TreeNode_new( char *data ) {
	TreeNode *new = (TreeNode *)malloc( sizeof( TreeNode ) );
	new->data = (char *)malloc( sizeof( char ) * TN_MAX_DATA );
	strcpy( new->data, data );
	new->left = NULL;
	new->right = NULL;
	return new;
}

int Tree_order( char *new, char *old ) {
	if( is_operation( new ) ) {
		return 1;
	} else {
		return 0;
	}
}

// void Tree_add( Tree **root, char *data ) {
// 	printf("Adding %s : ", data);
// 	Tree_print( *root );
// 	printf("\n");
// 	TreeNode **currentNode = root;

// 	while( (*currentNode) ) {
// 		int order = Tree_order( data, (*currentNode)->data );
// 		if( order < 0 ) {
// 			printf("order < 0 going left\n");
// 			currentNode = &((*currentNode)->left);
// 		}
// 		else if( order > 0 ) {
// 			printf("order > 0 going right\n");
// 			currentNode = &((*currentNode)->right);
// 		}
// 		else {
// 			printf("order = 0\n");
// 			if( (*currentNode)->left && is_seperator((*currentNode)->left->data[0]) ) {
// 				currentNode = &((*currentNode)->left);
// 			}
// 			else if( (*currentNode)->right && is_seperator((*currentNode)->right->data[0]) ) {
// 				currentNode = &((*currentNode)->right);
// 			}
// 			else {
// 				return;
// 			}
// 		}
// 	}

// 	*currentNode = TreeNode_new( data );
// }

void Tree_add( Tree **root, char *data ) {
	TreeNode **currentNode = root;

	if( !(*currentNode) ) { // If null
		printf("if null\n");
		*currentNode = TreeNode_new( data );
	}
	else if( strcmp( data, (*currentNode)->data ) > 0 ) {
		printf("new node is now head, old node is new node's left\n");
		TreeNode *oldNode = (*currentNode);

		(*currentNode) = TreeNode_new( data );
		(*currentNode)->left = oldNode;
	}
	else if( !(*currentNode)->left ) {
		printf("Add to left is no left node\n");
		(*currentNode)->left = TreeNode_new( data );
	}
	else if( strcmp( data, ((*currentNode)->left->data) ) < 0 ) {
		printf("data < left.data, recurse on left\n");
		Tree_add( &(*currentNode)->left, data );
	}
	else if( !(*currentNode)->right ) {
		printf("Add to right if no right node\n");
		(*currentNode)->right = TreeNode_new( data );
	}
	else if( strcmp( data, ((*currentNode)->right->data) ) < 0 ) {
		printf("data > left.data but data < right.data, replace left\n");
		TreeNode *oldNode = (*currentNode)->left;

		(*currentNode)->left = TreeNode_new( data );
		(*currentNode)->left = oldNode;
	}
	else {
		printf("data > left.data and data > right.data, replace right\n");
		TreeNode *oldNode = (*currentNode)->right;

		(*currentNode)->right = TreeNode_new( data );
		(*currentNode)->right = oldNode;
	}

}

void TreeNode_delete( TreeNode *node ) {
	free( node->data );
	free( node );
}

void Tree_delete( Tree *root ) {
	if( root->left ) {
		Tree_delete( root->left );
	}
	if( root->right ) {
		Tree_delete( root->right );
	}
	TreeNode_delete( root );
}

void Tree_print( Tree *root ) {
	if( root ) {
		printf( "%s ", root->data );
		if( root->left ) {
			printf("l");
			Tree_print( root->left );
		}
		if( root->right ) {
			printf("r");
			Tree_print( root->right );
		}
	}
}

Line *Line_new( Tree *callRoot ) {
	Line *new = (Line *)malloc( sizeof( Line ) );
	new->callRoot = callRoot;
	new->next = NULL;
	return new;
}

void Block_addLine( Line **root, Line *line ) {
	GenericNode_add( (void **)root, line );
}

void Block_add( Line **root, Tree *callRoot ) {
	Block_addLine( root, Line_new( callRoot ) );
}

void Line_delete( Line *line ) {
	Tree_delete( line->callRoot );
	free( line );
}

void Block_delete( Block *block ) {
	while( block ) {
		Line *temp = block->next;

		Line_delete( block );

		block = temp;
	}
}


ArgumentListNode *ArgumentListNode_new( char *type, char *name ) {
	ArgumentListNode *new = (ArgumentListNode *)malloc( sizeof( ArgumentListNode ) );
	new->type = (char *)malloc( sizeof( char ) * ALN_MAX_TYPE );
	strcpy( new->type, type );
	new->name = (char *)malloc( sizeof( char ) * ALN_MAX_NAME );
	strcpy( new->name, name );
	new->next = NULL;
	return new;
}

void ArgumentList_addNode( ArgumentList **root, ArgumentListNode *newNode ) {
	GenericNode_add( (void **)root, newNode );
}

void ArgumentList_add( ArgumentList **root, char *type, char *name ) {
	ArgumentList_addNode( root, ArgumentListNode_new( type, name ) );
}

void ArgumentListNode_delete( ArgumentListNode *node ) {
	free( node->type );
	free( node->name );
	free( node );
}

void ArgumentList_delete( ArgumentList *root ) {
	while( root ) {
		ArgumentListNode *temp = root->next;

		ArgumentListNode_delete( root );

		root = temp;
	}
}


Function *Function_new( ArgumentList *argumentList, Block *block, char *returnType, char *functionName ) {
	Function *new = (Function *)malloc( sizeof( Function ) );

	new->returnType  = (char *)malloc( sizeof( char ) * F_RETURNTYPE_MAX );
	strcpy( new->returnType, returnType );
	new->functionName = (char *)malloc( sizeof( char ) * F_FUNCTIONNAME_MAX );
	strcpy( new->functionName, functionName );

	new->argumentList = argumentList;
	new->block = block;
	return new;
}

void Function_delete( Function *function ) {
	ArgumentList_delete( function->argumentList );
	Block_delete( function->block );
	free( function );
}


ProgramListNode *ProgramListNode_new( void *data, ProgramListNodeType type ) {
	ProgramListNode *new = (ProgramListNode *)malloc( sizeof( ProgramListNode ) );
	new->data = data;
	new->next = NULL;
	new->type = type;
	return new;
}

void ProgramList_add( ProgramList **root, void *data, ProgramListNodeType type ) {
	GenericNode_add( (void **)root, ProgramListNode_new( data, type ) );
}

void ProgramListNode_delete( ProgramListNode *node ) {
	if( node->type == ProgramListNodeTypeFunction ) {
		Function_delete( node->data );
	}
	free( node );
}

void ProgramList_delete( ProgramList *program ) {
	while( program ) {
		ProgramList *temp = program->next;

		ProgramListNode_delete( program );

		program = temp;
	}
}

void ProgramList_print( ProgramList *program ) {
	ProgramListNode *programNode = program;
	while( programNode ) {
		printf( "Program List Node (%d):\n", programNode->type );
		if( programNode->type == ProgramListNodeTypeFunction ) {
			Function *function = (Function *)programNode->data;
			printf( "\tFunction (%s, %s):\n", function->returnType, function->functionName );
			printf( "\t\tArgument List:\n");
			ArgumentListNode *argumentNode = function->argumentList;
			while( argumentNode ) {
				printf("\t\t\t%s, %s\n", argumentNode->type, argumentNode->name );
				GenericNode_next( (void **)&argumentNode );
			}
			printf( "\t\tBlock:\n" );
			Line *line = function->block;
			while( line ) {
				printf("\t\t\t");
				Tree_print(line->callRoot);
				printf("\n");
				GenericNode_next( (void **)&line );
			}
		}
		GenericNode_next( (void **)&programNode );
	}
}
