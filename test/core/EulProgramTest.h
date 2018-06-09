#pragma once



class EulProgramTest {

    //region SOURCE FILE ACCESSING
    public: void static getAndCreateTest(const std::string& t) {
        EulProgram program;

        //test initial state
        Assert::equals(0, program.sources.size(), t + "A1");

        //test getting without creating while list is empty.
        Assert::null( program.getSource("someFileName.eul", 0), t + "A2");
        Assert::equals(0, program.sources.size(), t + "A3");

        //test getOrCreate
        EulSourceFile *firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile, t +"B1");
        Assert::equals(1, program.sources.size(), t + "B2");

        //get it with createFlag off.
        firstFile = program.getSource("someFileName.eul", 0);
        Assert::notNull(firstFile, t + "C1");
        Assert::equals("someFileName.eul", firstFile->id, t + "C2");
        Assert::equals(1, program.sources.size(), t + "C3");

        //get it with createFlag on
        firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile, t + "D1");
        Assert::equals("someFileName.eul", firstFile->id, t + "D2");
        Assert::equals(1, program.sources.size(), t + "D3");

        //ask for a file that does not exists
        firstFile = program.getSource("someFileName2.eul", 0);
        Assert::null(firstFile, t + "E1");
        Assert::equals(1, program.sources.size(), t + "E2");

        //create a second file
        EulSourceFile* secondFile = program.getSource("someFileName2.eul", 1);
        Assert::notNull(secondFile, t + "F1");
        Assert::equals("someFileName2.eul", secondFile->id, t + "F2");
        Assert::equals(2, program.sources.size(), t + "F3");

        //test getters
        firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile, t + "G1");
        Assert::equals("someFileName.eul", firstFile->id, t + "G2");

        firstFile = program.getSource("someFileName.eul", 0);
        Assert::notNull(firstFile, t + "G3");
        Assert::equals("someFileName.eul", firstFile->id, t + "G4");

        secondFile = program.getSource("someFileName2.eul", 1);
        Assert::notNull(secondFile, t + "G5");
        Assert::equals("someFileName2.eul", secondFile->id, t + "G6");

        secondFile = program.getSource("someFileName2.eul", 0);
        Assert::notNull(secondFile, t + "G7");
        Assert::equals("someFileName2.eul", secondFile->id, t + "G8");

        Assert::equals(2, program.sources.size(), t + "G9");
    }

    public: void static nextPendingSourceTest(const std::string& t) {
        EulProgram program;

        //add 3 files
        EulSourceFile *file1 = program.getSource("someFileName1.eul", 1);
        EulSourceFile *file2 = program.getSource("someFileName2.eul", 1);
        EulSourceFile *file3 = program.getSource("someFileName3.eul", 1);
        Assert::notNull(file1, t + "A1");
        Assert::notNull(file2, t + "A2");
        Assert::notNull(file3, t + "A3");
        Assert::equals(3, program.sources.size(), t + "A4");

        //test nextPending getter
        Assert::equals(file1, program.nextPendingSource(), t + "B1");

        file1->isParsed = 1;
        Assert::equals(file2, program.nextPendingSource(), t + "B2");

        file2->isParsed = 1;
        Assert::equals(file3, program.nextPendingSource(), t + "B3");

        file3->isParsed = 1;
        Assert::null(program.nextPendingSource(), t + "B4");
    }
    //endregion



    public: static void runAll() {
      getAndCreateTest("EulProgramTest.getAndCreate ");
      nextPendingSourceTest("EulProgramTest.nextPendingSourceTest ");
    }
};