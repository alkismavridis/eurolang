#include <stdlib.h>
#include "EulNodeList.h"



//region NODE
void EulNode_push(EulNode* this, EulToken* value) {
  this->next = malloc( sizeof(EulNode) );
  this->next->next = 0;
  this->next->value = value;
}
//endregion




//region NODE LIST
void EulNodeList_init(EulNodeList* this) {
  this->first = 0;
  this->last = 0;
}

/**
  frees memory resources for all nodes on the list.
  IMPORTANT NOTE: it does NOT frees or deinits the tokens themselves.
*/
void EulNodeList_deinit(EulNodeList* this) {
  EulNode* current = this->first;
  while(current) {
    EulNode* next = current->next;
    free(current);
    current = next;
  }
}

void EulNodeList_push(EulNodeList* this, EulToken* value) {
    //create a node
    EulNode* newNode = malloc(sizeof(EulNode));
    newNode->next = 0;
    newNode->value = value;

    //update first element, if needed
    if (this->first==0) this->first = newNode;

    //update the last element, adding the node on the list
    if (this->last!=0) this->last->next = newNode;
    this->last = newNode;
}


void EulNodeList_unshift(EulNodeList* this, EulToken* value) {
    //create a node
    EulNode* newNode = malloc(sizeof(EulNode));
    newNode->next = this->first;
    newNode->value = value;

    //update last element, if needed
    if (this->last==0) this->last = newNode;

    //update the first element, adding the node on the list
    this->first = newNode;
}


/** Returns the length of this list. */
int EulNodeList_length(EulNodeList* this) {
  int ret = 0;
  EulNode* current = this->first;
  while(current) {
    ret++;
    current = current->next;
  }

  return ret;
}
//endregion