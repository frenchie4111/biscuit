#ifndef _PROGRAMLIST_H_
#define _PROGRAMLIST_H_

#define TN_MAX_DATA (80)

typedef struct TreeNode {
	char *data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef TreeNode Tree;

TreeNode *TreeNode_new( char *data );

void Tree_add( Tree **tree, char *data );

void TreeNode_delete( TreeNode *node );
void Tree_delete( Tree *root );

void Tree_print( Tree *root );

typedef struct Line {
	struct Line *next;
	Tree *callRoot;
} Line;

typedef Line Block;

Line *Line_new( Tree *callRoot );

void Block_addLine( Line **root, Line *line );
void Block_add( Line **root, Tree *callRoot );

void Line_delete( Line *line );
void Block_delete( Block *block );


#define ALN_MAX_TYPE (80)
#define ALN_MAX_NAME (80)

typedef struct ArgumentListNode {
	struct ArgumentListNode *next;
	char *type;
	char *name;
} ArgumentListNode;

typedef ArgumentListNode ArgumentList;

ArgumentListNode *ArgumentListNode_new( char *type, char *name );

void ArgumentList_addNode( ArgumentList **root, ArgumentListNode *newNode );
void ArgumentList_add( ArgumentList **root, char *type, char *name );

void ArgumentListNode_delete( ArgumentListNode *node );
void ArgumentList_delete( ArgumentList *root );

#define F_RETURNTYPE_MAX (80)
#define F_FUNCTIONNAME_MAX (80)

typedef struct Function {
	ArgumentList *argumentList;
	Block *block;
	char *returnType;
	char *functionName;
} Function;

Function *Function_new( ArgumentList *argumentList, Block *block, char *returnType, char *functionName );

void Function_delete( Function *function );

typedef enum ProgramListNodeType {
	ProgramListNodeTypeFunction,
	ProgramListNodeTypeVariable
} ProgramListNodeType;

typedef struct ProgramListNode {
	struct ProgramListNode *next;
	void *data;
	ProgramListNodeType type;
} ProgramListNode;

typedef ProgramListNode ProgramList;

ProgramListNode *ProgramListNode_new( void *data, ProgramListNodeType type );

void ProgramList_add( ProgramList **root, void *data, ProgramListNodeType type );

void ProgramListNode_delete( ProgramListNode *node );
void ProgramList_delete( ProgramList *program );

void ProgramList_print( ProgramList *program );

#endif