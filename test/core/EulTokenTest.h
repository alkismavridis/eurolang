class EulTokenTest {



    //region CHAR TOKENS
    public: static void charTokenTest(const std::string& t) {
        Compiler comp(0);

        //1. check one char long
        std::string str = "'a'";
        EulCharToken tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "A1");
        Assert::equals('a', tok.value, t + "A2");
        Assert::equals(8, tok.size, t + "A3");

        str = "'~'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "A4");
        Assert::equals('~', tok.value, t + "A5");
        Assert::equals(8, tok.size, t + "A6");


        //2. check two chars long
        str = "'ϋ'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "B1");
        Assert::equals(0xcf8b, tok.value, t + "B2");
        Assert::equals(16, tok.size, t + "B3");

        str = "'ώ'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "C1");
        Assert::equals(0xcf8e, tok.value, t + "C2");
        Assert::equals(16, tok.size, t + "C3");

        str = "'π'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "D1");
        Assert::equals(0xcf80, tok.value, t + "D2");
        Assert::equals(16, tok.size, t + "D3");

        str = "'ü'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "F1");
        Assert::equals(0xc3bc, tok.value, t + "F2");
        Assert::equals(16, tok.size, t + "F3");

        //3. check 4 bytes long unicodes
        str = "'𠜎'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "G1");
        Assert::equalsUnsigned(0xf0a09c8e, tok.value, t + "G2");
        Assert::equals(32, tok.size, t + "G3");

        str = "'𡇙'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "H1");
        Assert::equalsUnsigned(0xf0a18799, tok.value, t + "H2");
        Assert::equals(32, tok.size, t + "H3");

        str = "'😌'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "I1");
        Assert::equalsUnsigned(0xf09f988c, tok.value, t + "I2");
        Assert::equals(32, tok.size, t + "I3");

        str = "'🙋'";
        tok = EulCharToken(str.c_str(), str.length(), &comp);
        Assert::equals(0, comp.errors.size(), t + "J1");
        Assert::equalsUnsigned(0xf09f998b, tok.value, t + "J2");
        Assert::equals(32, tok.size, t + "J3");


        //check type getter
        Assert::equals(tok.getType(), CHAR, t+"K1");
    }
    //endregion




    //region FLOAT TESTS
    public: static void floatTokenTest(const std::string& t) {

        //1. test case where int and decimal parst are present
        char str[] = "1.2";
        EulFloatToken tok = EulFloatToken(str);
        Assert::equals(1.2, tok.value, 0.0001, t + "A1");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "A2");

        char str2[] = "0.0";
        tok = EulFloatToken(str2);
        Assert::equals(0.0, tok.value, 0.0001, t + "A3");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "A4");

        char str3[] = "5.0";
        tok = EulFloatToken(str3);
        Assert::equals(5.0, tok.value, 0.0001, t + "A5");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "A6");

        char str4[] = "0.7";
        tok = EulFloatToken(str4);
        Assert::equals(0.7, tok.value, 0.0001, t + "A7");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "A8");


        //2. int part missing, or float part missing
        char str5[] = "0.";
        tok = EulFloatToken(str5);
        Assert::equals(0.0, tok.value, 0.0001, t + "B1");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "B2");

        char str6[] = "234.0";
        tok = EulFloatToken(str6);
        Assert::equals(234.0, tok.value, 0.0001, t + "B3");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "B4");

        char str7[] = ".0";
        tok = EulFloatToken(str7);
        Assert::equals(0.0, tok.value, 0.0001, t + "B5");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "B6");

        char str8[] = ".536";
        tok = EulFloatToken(str8);
        Assert::equals(0.536, tok.value, 0.0001, t + "B7");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "B8");


        //3. casting with size
        char str9[] = "0f4";
        tok = EulFloatToken(str9);
        Assert::equals(0, tok.value, 0.0001, t + "C1");
        Assert::equals(4, tok.size, t + "C2");

        char str10[] = "1f32";
        tok = EulFloatToken(str10);
        Assert::equals(1, tok.value, 0.0001, t + "C3");
        Assert::equals(32, tok.size, t + "C4");

        char str11[] = "1.4f32";
        tok = EulFloatToken(str11);
        Assert::equals(1.4, tok.value, 0.0001, t + "C5");
        Assert::equals(32, tok.size, t + "C6");

        char str12[] = ".4f12";
        tok = EulFloatToken(str12);
        Assert::equals(0.4, tok.value, 0.0001, t + "C7");
        Assert::equals(12, tok.size, t + "C8");

        char str13[] = "3.3f15";
        tok = EulFloatToken(str13);
        Assert::equals(3.3, tok.value, 0.0001, t + "C9");
        Assert::equals(15, tok.size, t + "C10");


        //4. casting default size      0f 1f+1.f .4f = 3.3f"
        char str14[] = "0f";
        tok = EulFloatToken(str14);
        Assert::equals(0, tok.value, 0.0001, t + "D1");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D2");

        char str15[] = "1f";
        tok = EulFloatToken(str15);
        Assert::equals(1, tok.value, 0.0001, t + "D3");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D4");

        char str16[] = "2.f";
        tok = EulFloatToken(str16);
        Assert::equals(2.0, tok.value, 0.0001, t + "D5");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D6");

        char str17[] = ".4f";
        tok = EulFloatToken(str17);
        Assert::equals(0.4, tok.value, 0.0001, t + "D7");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D8");

        char str18[] = "3.3f";
        tok = EulFloatToken(str18);
        Assert::equals(3.3, tok.value, 0.0001, t + "D7");
        Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D8");


        //check type getter
        Assert::equals(tok.getType(), FLOAT, t+"E1");

    }
    //endregion



    //region ID TESTS
    public: static void idTokenTest(const std::string& t) {
        EulScope scope(nullptr);

        std::string str = "someName";
        EulIdToken tok = EulIdToken(str.c_str(), str.length(), &scope);
        Assert::equals("someName", tok.name, t+"A1");
        Assert::equals(&scope, tok.scope, t+"A1_scope");

        str = "someOtherName";
        EulIdToken tok2 = EulIdToken(str.c_str(), str.length(), &scope);
        Assert::equals("someOtherName", tok2.name, t+"A2");
        Assert::equals(&scope, tok2.scope, t+"A2_scope");

        //check that first token did not change
        Assert::equals("someName", tok.name, t+"A3");

        //check type getter
        Assert::equals(tok.getType(), ID, t+"A4");
    }
    //endregion




    //region INT TESTS
    public: static void intTokenTest(const std::string& t) {
        //1. test int literals without qualifiers
        char str[] = "123";
        EulIntToken tok = EulIntToken(str);
        Assert::equals(123, tok.value, t + "A1");
        Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "A2");
        Assert::thatNot(tok.isUnsigned, t + "A3");

        char str2[] = "0";
        tok = EulIntToken(str2);
        Assert::equals(0, tok.value, t + "A4");
        Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "A5");
        Assert::thatNot(tok.isUnsigned, t + "A6");


        //2. test int literals with signed/unsigned qualifiers
        char str3[] = "55u";
        tok = EulIntToken(str3);
        Assert::equals(55, tok.value, t + "B1");
        Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "B2");
        Assert::that(tok.isUnsigned, t + "B3");

        char str4[] = "0u";
        tok = EulIntToken(str4);
        Assert::equals(0, tok.value, t + "B4");
        Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "B5");
        Assert::that(tok.isUnsigned, t + "B6");

        char str5[] = "55s";
        tok = EulIntToken(str5);
        Assert::equals(55, tok.value, t + "B7");
        Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "B8");
        Assert::thatNot(tok.isUnsigned, t + "B9");

        char str6[] = "0s";
        tok = EulIntToken(str6);
        Assert::equals(0, tok.value, t + "B10");
        Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "B11");
        Assert::thatNot(tok.isUnsigned, t + "B12");

        //3. test int literals with signed/unsigned qualifiers and sizes
        char str7[] = "55u12";
        tok = EulIntToken(str7);
        Assert::equals(55, tok.value, t + "C1");
        Assert::equals(12, tok.size, t + "C2");
        Assert::that(tok.isUnsigned, t + "C3");

        char str8[] = "0u6";
        tok = EulIntToken(str8);
        Assert::equals(0, tok.value, t + "C4");
        Assert::equals(6, tok.size, t + "C5");
        Assert::that(tok.isUnsigned, t + "C6");

        char str9[] = "55s123";
        tok = EulIntToken(str9);
        Assert::equals(55, tok.value, t + "C7");
        Assert::equals(123, tok.size, t + "C8");
        Assert::thatNot(tok.isUnsigned, t + "C9");

        char str10[] = "0s55";
        tok = EulIntToken(str10);
        Assert::equals(0, tok.value, t + "C10");
        Assert::equals(55, tok.size, t + "C11");
        Assert::thatNot(tok.isUnsigned, t + "C12");


        //check type getter
        Assert::equals(tok.getType(), INT, t+"D1");
    }
    //endregion




    //region STRING TESTS
    public: static void stringTokenTest(const std::string& t) {
        std::string str = "someName";
        EulStringToken tok = EulStringToken(str);
        Assert::equals("someName", tok.value, t+"A1");

        str = "someOtherName";
        EulStringToken tok2 = EulStringToken(str);
        Assert::equals("someOtherName", tok2.value, t+"A2");

        //check that first token did not change
        Assert::equals("someName", tok.value, t+"A3");


        //check type getter
        Assert::equals(tok.getType(), STRING, t+"A4");
    }
    //endregion



    public: static void runAll() {
        charTokenTest("EulTokenTest.charTokenTest ");
        floatTokenTest("EulTokenTest.floatTokenTest ");
        idTokenTest("EulTokenTest.idTokenTest ");
        intTokenTest("EulTokenTest.intTokenTest ");
        stringTokenTest("EulTokenTest.stringTokenTest ");
    }
};