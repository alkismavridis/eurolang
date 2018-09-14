#pragma once



class EulProgramTest {

    //region SOURCE FILE ACCESSING
    public: void static getAndCreateTest(const std::string& t) {
        EulProgram program;

        //test initial state
        Assert::equals(0, program.sources.size(), t + "A1");

        //test getting without creating while list is empty.
        Assert::null( program.getSource("someFileName.eul", 0).get(), t + "A2");
        Assert::equals(0, program.sources.size(), t + "A3");

        //test getOrCreate
        auto firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile.get(), t +"B1");
        Assert::equals(1, program.sources.size(), t + "B2");

        //get it with createFlag off.
        firstFile = program.getSource("someFileName.eul", 0);
        Assert::notNull(firstFile.get(), t + "C1");
        Assert::equals("someFileName.eul", firstFile->id, t + "C2");
        Assert::equals(1, program.sources.size(), t + "C3");

        //get it with createFlag on
        firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile.get(), t + "D1");
        Assert::equals("someFileName.eul", firstFile->id, t + "D2");
        Assert::equals(1, program.sources.size(), t + "D3");

        //ask for a file that does not exists
        firstFile = program.getSource("someFileName2.eul", 0);
        Assert::null(firstFile.get(), t + "E1");
        Assert::equals(1, program.sources.size(), t + "E2");

        //create a second file
        auto secondFile = program.getSource("someFileName2.eul", 1);
        Assert::notNull(secondFile.get(), t + "F1");
        Assert::equals("someFileName2.eul", secondFile->id, t + "F2");
        Assert::equals(2, program.sources.size(), t + "F3");

        //test getters
        firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile.get(), t + "G1");
        Assert::equals("someFileName.eul", firstFile->id, t + "G2");

        firstFile = program.getSource("someFileName.eul", 0);
        Assert::notNull(firstFile.get(), t + "G3");
        Assert::equals("someFileName.eul", firstFile->id, t + "G4");

        secondFile = program.getSource("someFileName2.eul", 1);
        Assert::notNull(secondFile.get(), t + "G5");
        Assert::equals("someFileName2.eul", secondFile->id, t + "G6");

        secondFile = program.getSource("someFileName2.eul", 0);
        Assert::notNull(secondFile.get(), t + "G7");
        Assert::equals("someFileName2.eul", secondFile->id, t + "G8");

        Assert::equals(2, program.sources.size(), t + "G9");
    }

    public: void static nextPendingSourceTest(const std::string& t) {
        EulProgram program;

        //add 3 files
        auto file1 = program.getSource("someFileName1.eul", 1);
        auto file2 = program.getSource("someFileName2.eul", 1);
        auto file3 = program.getSource("someFileName3.eul", 1);
        Assert::notNull(file1.get(), t + "A1");
        Assert::notNull(file2.get(), t + "A2");
        Assert::notNull(file3.get(), t + "A3");
        Assert::equals(3, program.sources.size(), t + "A4");

        //test nextPending getter
        Assert::equals(file1.get(), program.nextPendingSource().get(), t + "B1");

        file1->isParsed = 1;
        Assert::equals(file2.get(), program.nextPendingSource().get(), t + "B2");

        file2->isParsed = 1;
        Assert::equals(file3.get(), program.nextPendingSource().get(), t + "B3");

        file3->isParsed = 1;
        Assert::null(program.nextPendingSource().get(), t + "B4");
    }

    public: static void getEntryPointTest(const std::string& t) {
        EulProgram program;

        //1. Get the entry point. null should be returned at this point.
        Assert::null(program.getEntryPoint().get(), t+"A1");

        //2. Declare 3 files. The first one must be the entry point
        auto file1 = program.getSource("someFileName1.eul", 1);
        auto file2 = program.getSource("someFileName2.eul", 1);
        auto file3 = program.getSource("someFileName3.eul", 1);
        Assert::equals(file1.get(), program.getEntryPoint().get(), t+"A2");

        //3. Check that this is not influenced by parsed flags etc.
        file1->isParsed = 1;
        Assert::equals(file1.get(), program.getEntryPoint().get(), t+"A3");
        file2->isParsed = 1;
        Assert::equals(file1.get(), program.getEntryPoint().get(), t+"A4");
        file3->isParsed = 1;
        Assert::equals(file1.get(), program.getEntryPoint().get(), t+"A5");
    }
    //endregion


    public: static void globalsInitTest(const std::string& t) {
        EulProgram program;

        //1. Check that native types are initialized.
        Assert::notNull(program.nativeTypes.int32Type.get(), t+"A1");
        Assert::notNull(program.nativeTypes.uint64Type.get(), t+"A2");
        Assert::notNull(program.nativeTypes.stringType.get(), t+"A3");

        //2. Check that symbols are inserted into the scope
        Assert::equals(program.globalScope->getOwnSymbolAsType("Int32"), program.nativeTypes.int32Type.get(), t+"B1");
        Assert::equals(program.globalScope->getOwnSymbolAsType("UInt64"), program.nativeTypes.uint64Type.get(), t+"B2");
        Assert::equals(program.globalScope->getOwnSymbolAsType("String"), program.nativeTypes.stringType.get(), t+"B3");
    }

    public: static void resetTest(const std::string& t) {
        EulProgram program;

        //1. Add 2 source files and some symbols on the global scope
        auto file1 = program.getSource("someFileName1.eul", 1);
        auto file2 = program.getSource("someFileName2.eul", 1);
        program.globalScope->declare("someNewSymbol", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("123")));

        Assert::notNull(program.getSource("someFileName1.eul", 0).get(), t+"A1");
        Assert::notNull(program.globalScope->getOwnSymbol("someNewSymbol").get(), t+"A2");
        Assert::notNull(program.globalScope->getOwnSymbol("Int32").get(), t+"A3");


        //2. Reset. Source files and the "someNewSymbol" symbol should disappear.
        program.reset();
        Assert::null(program.getSource("someFileName1.eul", 0).get(), t+"B1");
        Assert::null(program.globalScope->getOwnSymbol("someNewSymbol").get(), t+"B2");
        Assert::notNull(program.globalScope->getOwnSymbol("Int32").get(), t+"B3"); //Native types should be still here.
    }



    public: static void runAll() {
      getAndCreateTest("EulProgramTest.getAndCreate ");
      nextPendingSourceTest("EulProgramTest.nextPendingSourceTest ");
      getEntryPointTest("EulProgramTest.getEntryPointTest ");
      globalsInitTest("EulProgramTest.globalsInitTest ");
      resetTest("EulProgramTest.resetTest ");
    }
};