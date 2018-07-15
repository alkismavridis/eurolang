#pragma once



class EulScopeTest {

    public: static void declarationGetterTest(const std::string& t) {
        EulScope root(nullptr);
        EulScope child1(&root);
        EulScope child2(&root);
        EulScope grandChild(&child1);

        //1. Declare some variables to root
        root.declare("x", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("x"), 1));
        Assert::equals(1, root.getDeclarationCount(), t + "A1");

        root.declare("y", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("y"), 1));
        Assert::equals(2, root.getDeclarationCount(), t + "A2");


        //try the getters
        Assert::stringToken(root.get("x")->value, "x", t + "B1");
        Assert::stringToken(root.get("y")->value, "y", t + "B2");
        Assert::null(root.get("z"), t + "B3");

        //try the getters on the sub scopes. Those should give the same results
        Assert::stringToken(child1.get("x")->value, "x", t + "B4");
        Assert::stringToken(child1.get("y")->value, "y", t + "B5");
        Assert::null(child1.get("z"), t + "B6");

        Assert::stringToken(child2.get("x")->value, "x", t + "B7");
        Assert::stringToken(child2.get("y")->value, "y", t + "B8");
        Assert::null(child2.get("z"), t + "B9");

        Assert::stringToken(grandChild.get("x")->value, "x", t + "B10");
        Assert::stringToken(grandChild.get("y")->value, "y", t + "B11");
        Assert::null(grandChild.get("z"), t + "B12");


        //2. Declare some individual variables on scopes child1 and child2.
        child1.declare("child1_only", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("child1_only"), 1));
        Assert::equals(1, child1.getDeclarationCount(), t + "C1");

        child2.declare("child2_only", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("child2_only"), 1));
        Assert::equals(1, child2.getDeclarationCount(), t + "C2");


        //test getters again.
        Assert::stringToken(root.get("x")->value, "x", t + "D1");
        Assert::stringToken(root.get("y")->value, "y", t + "D2");
        Assert::null(root.get("child1_only"), t + "D3");
        Assert::null(root.get("child2_only"), t + "D4");
        Assert::null(root.get("z"), t + "D5");

        Assert::stringToken(child1.get("x")->value, "x", t + "D6");
        Assert::stringToken(child1.get("y")->value, "y", t + "D7");
        Assert::stringToken(child1.get("child1_only")->value, "child1_only", t + "D8");
        Assert::null(child1.get("child2_only"), t + "D9");
        Assert::null(child1.get("z"), t + "D10");

        Assert::stringToken(child2.get("x")->value, "x", t + "D11");
        Assert::stringToken(child2.get("y")->value, "y", t + "D12");
        Assert::null(child2.get("child1_only"), t + "D13");
        Assert::stringToken(child2.get("child2_only")->value, "child2_only", t + "D14");
        Assert::null(child2.get("z"), t + "D15");

        Assert::stringToken(grandChild.get("x")->value, "x", t + "D16");
        Assert::stringToken(grandChild.get("y")->value, "y", t + "D17");
        Assert::stringToken(grandChild.get("child1_only")->value, "child1_only", t + "D18");
        Assert::null(grandChild.get("child2_only"), t + "D19");
        Assert::null(grandChild.get("z"), t + "D20");
    }


    public: static void getOwnSymbolTest(const std::string& t) {
        EulScope root(nullptr);
        EulScope child1(&root);
        EulScope child2(&root);
        EulScope grandChild(&child1);

        //1. Declare some variables to root
        root.declare("x", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("x"), 1));
        Assert::equals(1, root.getDeclarationCount(), t + "A1");

        root.declare("y", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("y"), 1));
        Assert::equals(2, root.getDeclarationCount(), t + "A2");


        //try the getters
        Assert::stringToken(root.getOwnSymbol("x")->value, "x", t + "B1");
        Assert::stringToken(root.getOwnSymbol("y")->value, "y", t + "B2");
        Assert::null(root.getOwnSymbol("z"), t + "B3");

        //try the getters on the sub scopes. Those should give no result
        Assert::null(child1.getOwnSymbol("x"), t + "B4");
        Assert::null(child1.getOwnSymbol("y"), t + "B5");
        Assert::null(child1.getOwnSymbol("z"), t + "B6");

        Assert::null(child2.getOwnSymbol("x"), t + "B7");
        Assert::null(child2.getOwnSymbol("y"), t + "B8");
        Assert::null(child2.getOwnSymbol("z"), t + "B9");

        Assert::null(grandChild.getOwnSymbol("x"), t + "B10");
        Assert::null(grandChild.getOwnSymbol("y"), t + "B11");
        Assert::null(grandChild.getOwnSymbol("z"), t + "B12");


        //2. Declare some individual variables on scopes child1 and child2.
        child1.declare("child1_only", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("child1_only"), 1));
        Assert::equals(1, child1.getDeclarationCount(), t + "C1");

        child2.declare("child2_only", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("child2_only"), 1));
        Assert::equals(1, child2.getDeclarationCount(), t + "C2");


        //test getters again.
        Assert::stringToken(root.getOwnSymbol("x")->value, "x", t + "D1");
        Assert::stringToken(root.getOwnSymbol("y")->value, "y", t + "D2");
        Assert::null(root.getOwnSymbol("child1_only"), t + "D3");
        Assert::null(root.getOwnSymbol("child2_only"), t + "D4");
        Assert::null(root.getOwnSymbol("z"), t + "D5");

        Assert::null(child1.getOwnSymbol("x"), t + "D6");
        Assert::null(child1.getOwnSymbol("y"), t + "D7");
        Assert::stringToken(child1.getOwnSymbol("child1_only")->value, "child1_only", t + "D8");
        Assert::null(child1.getOwnSymbol("child2_only"), t + "D9");
        Assert::null(child1.getOwnSymbol("z"), t + "D10");

        Assert::null(child2.getOwnSymbol("x"), t + "D11");
        Assert::null(child2.getOwnSymbol("y"), t + "D12");
        Assert::null(child2.getOwnSymbol("child1_only"), t + "D13");
        Assert::stringToken(child2.getOwnSymbol("child2_only")->value, "child2_only", t + "D14");
        Assert::null(child2.getOwnSymbol("z"), t + "D15");

        Assert::null(grandChild.getOwnSymbol("x"), t + "D16");
        Assert::null(grandChild.getOwnSymbol("y"), t + "D17");
        Assert::null(grandChild.getOwnSymbol("child1_only"), t + "D18");
        Assert::null(grandChild.getOwnSymbol("child2_only"), t + "D19");
        Assert::null(grandChild.getOwnSymbol("z"), t + "D20");
    }

    public: static void declareTest(const std::string& t) {
            EulScope root(nullptr);
            EulScope child1(&root);


            //1. Declare some variables to root
            Assert::that( root.declare("x", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("x"), 1)), t + "A1" );
            Assert::equals(1, root.getDeclarationCount(), t + "A2");

            Assert::that( root.declare("y", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("y"), 1)), t + "A3" );
            Assert::equals(2, root.getDeclarationCount(), t + "A4");

            //2. Try to redefine those same symbols
            Assert::thatNot( root.declare("x", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("newX"), 1)), t + "B1" );
            Assert::equals(2, root.getDeclarationCount(), t + "B2");
            Assert::stringToken(root.getOwnSymbol("x")->value, "x", t + "B3");

            Assert::thatNot( root.declare("y", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("newY"), 1)), t + "B4" );
            Assert::equals(2, root.getDeclarationCount(), t + "B5");
            Assert::stringToken(root.getOwnSymbol("y")->value, "y", t + "B6");


            //3. Define those variables in a sub scope. This should be allowed.
            Assert::that( child1.declare("x", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("child1_X"), 1)), t + "C1" );
            Assert::equals(1, child1.getDeclarationCount(), t + "C2");

            Assert::that( child1.declare("y", new EulSymbol(yy::EulParser::token::VAR, nullptr, new EulStringToken("child1_Y"), 1)), t + "C3" );
            Assert::equals(2, child1.getDeclarationCount(), t + "C4");
    }


    public: static void runAll() {
        declarationGetterTest("EulScopeTest.declarationGetterTest ");
        getOwnSymbolTest("EulScopeTest.getOwnSymbolTest ");
        declareTest("EulScopeTest.declareTest ");
    }
};