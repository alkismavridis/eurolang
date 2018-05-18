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
  assertPtrEquals(&tok, list.last->value, t, "B1");
  assertIntEquals(1, EulNodeList_length(&list), t, "B2");

  //add one more
  EulToken tok2;
  EulNodeList_push(&list, &tok2);
  assertPtrEquals(&tok, list.first->value, t, "C1");
  assertPtrEquals(&tok2, list.first->next->value, t, "C2");
  assertPtrEquals(&tok2, list.last->value, t, "C3");
  assertIntEquals(2, EulNodeList_length(&list), t, "C4");

  //add a third one
  EulToken tok3;
  EulNodeList_push(&list, &tok3);
  assertPtrEquals(&tok, list.first->value, t, "D1");
  assertPtrEquals(&tok2, list.first->next->value, t, "D2");
  assertPtrEquals(&tok3, list.first->next->next->value, t, "D3");
  assertPtrEquals(&tok3, list.last->value, t, "D4");
  assertIntEquals(3, EulNodeList_length(&list), t, "D5");

  //clean up
  EulNodeList_deinitAllNodes(&list);
}



void NodeListTest_runAllTests() {
  NodeListTest_testInit("NodeListTest_testInit");
  NodeListTest_testPush("NodeListTest_testPush");
}
