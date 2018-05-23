#pragma once


void EulProgramTest_getAndCreate(char* t) {
    EulProgram program;
    EulProgram_init(&program);

    //test initial state
    assertIntEquals(0, EulNodeList_length(&program.sources), t, "A1");

    //test getting without creating while list is empty.
    assertNull( EulProgram_getSource(&program, "someFileName.eul", 0), t, "A2");
    assertIntEquals(0, EulNodeList_length(&program.sources), t, "A3");

    //test getOrCreate
    EulToken *firstFile = EulProgram_getSource(&program, "someFileName.eul", 1);
    assertNotNull(firstFile, t, "B1");
    assertIntEquals(1, EulNodeList_length(&program.sources), t, "B2");

    //get it with createFlag off.
    firstFile = EulProgram_getSource(&program, "someFileName.eul", 0);
    assertNotNull(firstFile, t, "C1");
    assertStringEquals("someFileName.eul", firstFile->value.asSourceFile->id, t, "C2");
    assertIntEquals(1, EulNodeList_length(&program.sources), t, "C3");

    //get it with createFlag on
    firstFile = EulProgram_getSource(&program, "someFileName.eul", 1);
    assertNotNull(firstFile, t, "D1");
    assertStringEquals("someFileName.eul", firstFile->value.asSourceFile->id, t, "D2");
    assertIntEquals(1, EulNodeList_length(&program.sources), t, "D3");

    //ask for a file that does not exists
    firstFile = EulProgram_getSource(&program, "someFileName2.eul", 0);
    assertNull(firstFile, t, "E1");
    assertIntEquals(1, EulNodeList_length(&program.sources), t, "E2");

    //create a second file
    EulToken* secondFile = EulProgram_getSource(&program, "someFileName2.eul", 1);
    assertNotNull(secondFile, t, "F1");
    assertStringEquals("someFileName2.eul", secondFile->value.asSourceFile->id, t, "F2");
    assertIntEquals(2, EulNodeList_length(&program.sources), t, "F3");

    //test getters
    firstFile = EulProgram_getSource(&program, "someFileName.eul", 1);
    assertNotNull(firstFile, t, "G1");
    assertStringEquals("someFileName.eul", firstFile->value.asSourceFile->id, t, "G2");

    firstFile = EulProgram_getSource(&program, "someFileName.eul", 0);
    assertNotNull(firstFile, t, "G3");
    assertStringEquals("someFileName.eul", firstFile->value.asSourceFile->id, t, "G4");

    secondFile = EulProgram_getSource(&program, "someFileName2.eul", 1);
    assertNotNull(secondFile, t, "G5");
    assertStringEquals("someFileName2.eul", secondFile->value.asSourceFile->id, t, "G6");

    secondFile = EulProgram_getSource(&program, "someFileName2.eul", 0);
    assertNotNull(secondFile, t, "G7");
    assertStringEquals("someFileName2.eul", secondFile->value.asSourceFile->id, t, "G8");

    assertIntEquals(2, EulNodeList_length(&program.sources), t, "G9");

    EulProgram_deinit(&program);
}

void EulProgramTest_nextPendingSource(char* t) {
    EulProgram program;
    EulProgram_init(&program);

    //add 3 files
    EulToken *file1 = EulProgram_getSource(&program, "someFileName1.eul", 1);
    EulToken *file2 = EulProgram_getSource(&program, "someFileName2.eul", 1);
    EulToken *file3 = EulProgram_getSource(&program, "someFileName3.eul", 1);
    assertNotNull(file1, t, "A1");
    assertNotNull(file2, t, "A2");
    assertNotNull(file3, t, "A3");
    assertIntEquals(3, EulNodeList_length(&program.sources), t, "A4");

    //test nextPending getter
    assertPtrEquals(file1, EulProgram_nextPendingSource(&program), t, "B1");

    file1->value.asSourceFile->isParsed = 1;
    assertPtrEquals(file2, EulProgram_nextPendingSource(&program), t, "B2");

    file2->value.asSourceFile->isParsed = 1;
    assertPtrEquals(file3, EulProgram_nextPendingSource(&program), t, "B3");

    file3->value.asSourceFile->isParsed = 1;
    assertNull(EulProgram_nextPendingSource(&program), t, "B4");

    EulProgram_deinit(&program);
}



void EulProgramTest_runAllTests() {
  EulProgramTest_getAndCreate("EulProgramTest_getAndCreate");
  EulProgramTest_nextPendingSource("EulProgramTest_nextPendingSource");
}
