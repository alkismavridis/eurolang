#pragma once



void NodeTest_testAppendToNode(char* t) {
  //create a couple of entities
  EulNode node;
  node.next = 0;
  EulToken *tok1 = malloc(sizeof(EulToken));
  EulToken *tok2 = malloc(sizeof(EulToken));

  //test current state
  assertNull(node.next, t, "A1");

  //append once node
  EulNode_push(&node, tok1);
  assertNotNull(node.next, t, "B1");
  assertPtrEquals(tok1, node.next->value, t, "B2");
  assertNull(node.next->next, t, "B3");

  //append one more
  EulNode_push(node.next, tok2);
  assertNotNull(node.next, t, "C1");
  assertPtrEquals(tok1, node.next->value, t, "C2");
  assertNotNull(node.next->next, t, "C3");
  assertPtrEquals(tok2, node.next->next->value, t, "C4");
  assertNull(node.next->next->next, t, "C5");

  //clean up
  free(tok1);
  free(tok2);
}


void NodeTest_runAllTests() {
  NodeTest_testAppendToNode("NodeTest_testAppendToNode");
}
