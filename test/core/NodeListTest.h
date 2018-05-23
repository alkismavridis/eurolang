#pragma once


void NodeListTest_testInit(char* t) {
  EulNodeList list;
  EulNodeList_init(&list);
  assertNull(list.first, t, "A1");
  assertNull(list.last, t, "A2");

  //change the first and last elements
  EulNode node1;
  EulNode node2;
  list.first = &node1;
  list.last = &node2;
  assertNotNull(list.first, t, "B1");
  assertNotNull(list.last, t, "B2");

  //init again. they should become null.
  EulNodeList_init(&list);
  assertNull(list.first, t, "C1");
  assertNull(list.last, t, "C2");
}

void NodeListTest_testPush(char* t) {
    //start with an empty list
    EulNodeList list;
    EulNodeList_init(&list);
    assertNull(list.first, t, "A1");
    assertNull(list.last, t, "A2");
    assertIntEquals(0, EulNodeList_length(&list), t, "A2");

    //add one token
    EulToken tok;
    EulNodeList_push(&list, &tok);
    assertPtrEquals(&tok, list.first->value, t, "B1");
    assertPtrEquals(&tok, list.last->value, t, "B2");
    assertNull(list.first->next, t, "B3");
    assertNull(list.last->next, t, "B4");
    assertIntEquals(1, EulNodeList_length(&list), t, "B5");

    //add one more
    EulToken tok2;
    EulNodeList_push(&list, &tok2);
    assertPtrEquals(&tok, list.first->value, t, "C1");
    assertPtrEquals(&tok2, list.first->next->value, t, "C2");
    assertPtrEquals(&tok2, list.last->value, t, "C3");
    assertNull(list.last->next, t, "C4");
    assertIntEquals(2, EulNodeList_length(&list), t, "C5");

    //add a third one
    EulToken tok3;
    EulNodeList_push(&list, &tok3);
    assertPtrEquals(&tok, list.first->value, t, "D1");
    assertPtrEquals(&tok2, list.first->next->value, t, "D2");
    assertPtrEquals(&tok3, list.first->next->next->value, t, "D3");
    assertPtrEquals(&tok3, list.last->value, t, "D4");
    assertNull(list.last->next, t, "D5");
    assertIntEquals(3, EulNodeList_length(&list), t, "D6");

    //clean up
    EulNodeList_deinit(&list);
}

void NodeListTest_testUnshift(char* t) {
    //start with an empty list
    EulNodeList list;
    EulNodeList_init(&list);
    assertNull(list.first, t, "A1");
    assertNull(list.last, t, "A2");
    assertIntEquals(0, EulNodeList_length(&list), t, "A2");

    //add one token
    EulToken tok;
    EulNodeList_unshift(&list, &tok);
    assertPtrEquals(&tok, list.first->value, t, "B1");
    assertPtrEquals(&tok, list.last->value, t, "B2");
    assertNull(list.first->next, t, "B3");
    assertNull(list.last->next, t, "B4");
    assertIntEquals(1, EulNodeList_length(&list), t, "B2");

    //add one more
    EulToken tok2;
    EulNodeList_unshift(&list, &tok2);
    assertPtrEquals(&tok2, list.first->value, t, "C1");
    assertPtrEquals(&tok, list.first->next->value, t, "C2");
    assertPtrEquals(&tok, list.last->value, t, "C3");
    assertNull(list.last->next, t, "C4");
    assertIntEquals(2, EulNodeList_length(&list), t, "C5");

    //add a third one
    EulToken tok3;
    EulNodeList_unshift(&list, &tok3);
    assertPtrEquals(&tok3, list.first->value, t, "D1");
    assertPtrEquals(&tok2, list.first->next->value, t, "D2");
    assertPtrEquals(&tok, list.first->next->next->value, t, "D3");
    assertPtrEquals(&tok, list.last->value, t, "D4");
    assertNull(list.last->next, t, "D5");
    assertIntEquals(3, EulNodeList_length(&list), t, "D6");

    //clean up
    EulNodeList_deinit(&list);
}


void NodeListTest_testAppendToNode(char* t) {
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



void NodeListTest_runAllTests() {
  NodeListTest_testAppendToNode("NodeListTest_testAppendToNode");
  NodeListTest_testInit("NodeListTest_testInit");
  NodeListTest_testPush("NodeListTest_testPush");
  NodeListTest_testUnshift("NodeListTest_testUnshift");
}
