#pragma once



//region I HATE THAT I HAVE TO DO THIS
typedef struct EulToken EulToken;
typedef struct EulNode EulNode;
//endregion




//region DEFINITIONS
typedef struct EulNode {
	EulNode *next;
	EulToken *value;
} EulNode;

typedef struct EulNodeList EulNodeList;
typedef struct EulNodeList {
	EulNode *first;
	EulNode *last;
} EulNodeList;
//endregion




//region NODE FUNCTIONS
void EulNode_push(EulNode* this, EulToken* value);
//void EulNode_init(EulToken* this, EulToken* child);
//void EulNode_deinit(EulToken* this);
//endregion




//region NODE LIST
void EulNodeList_init(EulNodeList* this);
void EulNodeList_deinit(EulNodeList* this);
void EulNodeList_push(EulNodeList* this, EulToken* value);
void EulNodeList_unshift(EulNodeList* this, EulToken* value);
int EulNodeList_length(EulNodeList* this);
//endregion