#pragma once

class EulAstTest {



    //region TYPE TESTS
    public: static void isEulTypeTest(const std::string& t) {
        //1. Test a couple of positive cases
        EulType type = EulIntegerType(64, true);
        Assert::that(EulType::isEulType(&type), t+"A1");

        EulNamedType type2 = EulNamedType("SomeCoolType");
        Assert::that(EulType::isEulType(&type2), t+"A2");

        EulPointerType type3 = EulPointerType(&type, 1);
        Assert::that(EulType::isEulType(&type3), t+"A3");

        //2. Test a negative case: not a AST
        EulStringToken notAType1 = EulStringToken("123");
        Assert::thatNot(EulType::isEulType(&notAType1), t+"A4");

        //3. Test a negative case: AST, but not a EulType
        ReturnStatement notAType2 = ReturnStatement(std::make_shared<EulStringToken>("456"));
        Assert::thatNot(EulType::isEulType(&notAType2), t+"A5");
    }

    public: static void getPointerTo(const std::string& t) {
        //1. Create a type to point to.
        auto type = std::make_shared<EulIntegerType>(64, true);

        //2. Mate the pointer
        EulPointerType ptrType = EulPointerType(type.get(), 4);

        //3. Make assertions
        Assert::equals(type.get(), ptrType.contentType, t+"A1");
        Assert::equals(4, ptrType.depth, t+"A2");
        Assert::equals(POINTER_TYPE, ptrType.getTypeEnum(), t+"A3");
    }
    //endregion



    public: static void runAll() {
        isEulTypeTest("EulAstTest.isEulTypeTest ");
        getPointerTo("EulAstTest.getPointerTo ");
    }
};