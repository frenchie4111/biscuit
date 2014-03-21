#include <stdio.h>
#include <string.h>

#include <programlist.h>

int main() {
	ProgramList *plist = NULL;
	Function *func = NULL;
	ArgumentList *alist = NULL;
	Block *block = NULL;
	TreeNode *tree = NULL;

	tree = TreeNode_new( "head" );
	tree->left = TreeNode_new( "left" );
	tree->right = TreeNode_new( "right" );
	printf( "Tree: (%s) L: (%s) R:(%s)\n", tree->data, tree->left->data, tree->right->data );

	Block_add( &block, tree );
	printf( "Block: Tree (%s) L: (%s) R:(%s)\n", block->callRoot->data, block->callRoot->left->data, block->callRoot->right->data );

	ArgumentList_add( &alist, "int", "variable" );
	printf( "Arg: Type: (%s) (%s)\n", alist->type, alist->name );
	ArgumentList_add( &alist, "char", "variable2" );
	printf( "Arg 2: Type: (%s) (%s)\n", alist->next->type, alist->next->name );

	func = Function_new( alist, block, "returntype", "funcname" );
	printf( "Function (%s, %s): Arg: (%s, %s) Arg 2: (%s, %s) Block: Tree (%s) L: (%s) R:(%s)\n", 
		func->returnType, func->functionName,
		func->argumentList->type, func->argumentList->name,
		func->argumentList->next->type, func->argumentList->next->name,
		func->block->callRoot->data, func->block->callRoot->left->data, func->block->callRoot->right->data );
	
	ProgramList_add( &plist, func, ProgramListNodeTypeFunction );
	printf( "Program: Function (%s, %s): Arg: (%s, %s) Arg 2: (%s, %s) Block: Tree (%s) L: (%s) R:(%s)\n", 
		((Function *)plist->data)->returnType, ((Function *)plist->data)->functionName,
		((Function *)plist->data)->argumentList->type, ((Function *)plist->data)->argumentList->name,
		((Function *)plist->data)->argumentList->next->type, ((Function *)plist->data)->argumentList->next->name,
		((Function *)plist->data)->block->callRoot->data, ((Function *)plist->data)->block->callRoot->left->data, ((Function *)plist->data)->block->callRoot->right->data );

	ProgramList_print( plist );

	ProgramList_delete( plist );
	printf("Deleted \n");

	Tree *testTree = NULL;
	printf( "Tree Test\n" );
	printf( "adding a\n" );
	Tree_add( &testTree, "a" );
	printf( "adding b\n" );
	Tree_add( &testTree, "c" );
	printf( "adding c\n" );
	Tree_add( &testTree, "b" );
	Tree_add( &testTree, "d" );
	Tree_add( &testTree, "e" );
	Tree_add( &testTree, "f" );
	Tree_print( testTree );
	printf("\nstrcmp %d\n", strcmp("c", "b") );

	return 0;
}


