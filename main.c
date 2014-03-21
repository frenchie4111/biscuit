#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "tokenizer.h"
#include "programlist.h"

void pointerCheck( List *token ) {
	if( ! strcmp( token->next->data, "*" ) ) {
		List_combine( token );
	}
}

ArgumentListNode *ArgumentListNode_generate( List **token ) {
	//TODO: Add errors
	printf("node created");
	pointerCheck( (*token) );
	char *argumentType = (*token)->data;
	List_next( token );
	char *argumentName = (*token)->data;
	List_next( token );
	if( (*token) && !strcmp( (*token)->data, "," ) ) {
		List_next( token );
	}
	printf("node created\n");
	return ArgumentListNode_new( argumentType, argumentName );
}

ArgumentList *ArgumentList_generate( List **token ) {
	ArgumentList *argumentList = NULL;
	if( strcmp( (*token)->data, "(" ) ) {
		// Error
		printf("\tError (\n");
		return NULL;
	} else {
		List_next( token );
	}
	printf( "Token %s\n", (*token)->data );
	while( strcmp( (*token)->data, ")" ) ) { // Arguments
		printf("\tArguments %s\n", (*token)->data);
		ArgumentList_addNode( &argumentList, ArgumentListNode_generate( token ) );
	}
	List_next( token );
	return argumentList;
}

Line *Line_generate( List **token ) {
	Tree *callTree = NULL;
	while( strcmp( (*token)->data, ";" ) ) {
		Tree_add( &callTree, (*token)->data );
		List_next( token );
	}
	if( !strcmp( (*token)->data, ";" ) )
		List_next(token);
	return Line_new( callTree );
}

Block *Block_generate( List **token ) {
	Block *block = NULL;
	if( strcmp( (*token)->data, "{" ) ) {
		printf("\tError {\n");
		return NULL;
	} else {
		List_next( token );
	}

	while( strcmp( (*token)->data, "}" ) ) {
		Block_addLine( &block, Line_generate( token ) );
	}
	return block;
}

Function *Function_generate( List **token ) {
	pointerCheck( (*token) );
	

	char *returnType = (*token)->data;
	List_next( token );
	char *functionName = (*token)->data;
	List_next( token );

	printf( "Return Type: %s, Function Name: %s Next %s\n", returnType, functionName, (*token)->data );

	ArgumentList *argumentList = ArgumentList_generate( token );

	Block *block = Block_generate( token );

	return Function_new( argumentList, block, returnType, functionName );
}

ProgramListNodeType findTokenType( ListNode *token ) {
	return ProgramListNodeTypeFunction;
}

ProgramList *createProgramList( List *tokens ) {
	ProgramList *program = NULL;
	ListNode *currentToken = tokens;

	while( currentToken ) {
		void *currentData;

		ProgramListNodeType currentType = findTokenType( currentToken );
		switch( currentType ) {
			case(ProgramListNodeTypeFunction):
				currentData = (void *)Function_generate( &currentToken );
				break;
			case(ProgramListNodeTypeVariable):
				break;
			default:
				// Error message
				return NULL;
				break;
		}

		ProgramList_add( &program, currentData, currentType );
		List_next( &currentToken );
	}

	return program;
}

void compile_file( const char *fileName ) {
	printf("Compiling %s\n", fileName);
	
	ListNode *tokens = tokenize_file( fileName );
	
	List_print( tokens );

	ProgramList *programList = createProgramList( tokens );

	ProgramList_print( programList );

	ProgramList_delete( programList );
	List_delete( tokens );
}

int main(int argc, const char *argv[]) {
	if( argc > 1 ) {
		for( int i = 1; i < argc; i++ ) {
			compile_file( argv[i] );
		}
	} else {
		printf( "No Input Files\n" );
	}
}
