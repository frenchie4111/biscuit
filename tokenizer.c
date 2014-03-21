#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "tokenizer.h"

#define MAX_TOKEN (80)

char *token_seperators = "{};()+-*/[]&,\"'<>.\\";
char *non_token_seperators = " \n\t";

static int is_token_seperator( char c ) {
	for( int i = 0; token_seperators[i] != '\0'; i++ ) {
		if( c == token_seperators[i] ) {
			return 1;
		}
	}
	return 0;
}

int is_seperator( char c ) {
	for( int i = 0; non_token_seperators[i] != '\0'; i++ ) {
		if( c == non_token_seperators[i] ) {
			return 1;
		}
	}
	return is_token_seperator( c );
}

/**
 * @returns Root node of token list
 */
ListNode *tokenize_file( const char *fileName ) {
	FILE *fp = fopen( fileName, "r" );
	ListNode *rootNode = NULL;

	if( fp != NULL ) {
		char current_char = fgetc( fp );

		char *current_token;
		int current_token_i = 0;

		while( current_char != EOF ) {
			printf("%c", current_char );
			current_token = (char *) malloc( sizeof( char ) * MAX_TOKEN );

			if( is_seperator( current_char ) ) {
				if( current_token_i > 0 ) {
					current_token[current_token_i] = '\0';
					List_add( &rootNode, current_token );
				}

				if( is_token_seperator( current_char ) ) {
					current_token[0] = current_char;
					current_token[1] = '\0';
					List_add( &rootNode, current_token );
				}
				current_token_i = 0;
			}
			else {
				current_token[current_token_i] = current_char;
				current_token_i++;
			}

			current_char = fgetc( fp );
			free( current_token );
		}
	}
	else {
		printf("File %s failed to open\n", fileName);
	}

	fclose( fp );
	return rootNode;
}