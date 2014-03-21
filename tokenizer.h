#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include "list.h"

int is_seperator( char c );

ListNode *tokenize_file( const char *fileName );

#endif