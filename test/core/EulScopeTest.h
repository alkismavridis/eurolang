#pragma once



class EulScopeTest {

    public: static void declarationGetterTest(const std::string& t) {
        EulScope root(nullptr);
        EulScope child1(&root);
        EulScope child2(&root);
        EulScope grandChild(&child1);

        //1. Declare some variables to root
        root.declare("x", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("x")));
        Assert::equals(1, root.getDeclarationCount(), t + "A1");

        root.declare("y", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("y")));
        Assert::equals(2, root.getDeclarationCount(), t + "A2");


        //try the getters
        Assert::stringToken(root.get("x")->value.get(), "x", t + "B1");
        Assert::stringToken(root.get("y")->value.get(), "y", t + "B2");
        Assert::null(root.get("z").get(), t + "B3");

        //try the getters on the sub scopes. Those should give the same results
        Assert::stringToken(child1.get("x")->value.get(), "x", t + "B4");
        Assert::stringToken(child1.get("y")->value.get(), "y", t + "B5");
        Assert::null(child1.get("z").get(), t + "B6");

        Assert::stringToken(child2.get("x")->value.get(), "x", t + "B7");
        Assert::stringToken(child2.get("y")->value.get(), "y", t + "B8");
        Assert::null(child2.get("z").get(), t + "B9");

        Assert::stringToken(grandChild.get("x")->value.get(), "x", t + "B10");
        Assert::stringToken(grandChild.get("y")->value.get(), "y", t + "B11");
        Assert::null(grandChild.get("z").get(), t + "B12");


        //2. Declare some individual variables on scopes child1 and child2.
        child1.declare("child1_only", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("child1_only")));
        Assert::equals(1, child1.getDeclarationCount(), t + "C1");

        child2.declare("child2_only", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("child2_only")));
        Assert::equals(1, child2.getDeclarationCount(), t + "C2");


        //test getters again.
        Assert::stringToken(root.get("x")->value.get(), "x", t + "D1");
        Assert::stringToken(root.get("y")->value.get(), "y", t + "D2");
        Assert::null(root.get("child1_only").get(), t + "D3");
        Assert::null(root.get("child2_only").get(), t + "D4");
        Assert::null(root.get("z").get(), t + "D5");

        Assert::stringToken(child1.get("x")->value.get(), "x", t + "D6");
        Assert::stringToken(child1.get("y")->value.get(), "y", t + "D7");
        Assert::stringToken(child1.get("child1_only")->value.get(), "child1_only", t + "D8");
        Assert::null(child1.get("child2_only").get(), t + "D9");
        Assert::null(child1.get("z").get(), t + "D10");

        Assert::stringToken(child2.get("x")->value.get(), "x", t + "D11");
        Assert::stringToken(child2.get("y")->value.get(), "y", t + "D12");
        Assert::null(child2.get("child1_only").get(), t + "D13");
        Assert::stringToken(child2.get("child2_only")->value.get(), "child2_only", t + "D14");
        Assert::null(child2.get("z").get(), t + "D15");

        Assert::stringToken(grandChild.get("x")->value.get(), "x", t + "D16");
        Assert::stringToken(grandChild.get("y")->value.get(), "y", t + "D17");
        Assert::stringToken(grandChild.get("child1_only")->value.get(), "child1_only", t + "D18");
        Assert::null(grandChild.get("child2_only").get(), t + "D19");
        Assert::null(grandChild.get("z").get(), t + "D20");
    }

    public: static void declareFromStatementTest(const std::string& t) {
        //1. Declare one symbol.
        EulScope scope(nullptr);
        scope.declare("x", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("x")));

        //2. Create a var declaration statement.
        VarDeclarationStatement declStatement =  VarDeclarationStatement(
            yy::EulParser::token::CONST,
            std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>()
        );
        declStatement.declarations->push_back(std::make_shared<VarDeclaration>(
            std::make_shared<EulIdToken>("a", &scope),
            nullptr,
            nullptr
        ));
        declStatement.declarations->push_back(std::make_shared<VarDeclaration>(
            std::make_shared<EulIdToken>("b", &scope),
            nullptr,
            nullptr
        ));

        //3. Add the statement into the scope.
        scope.declare(&declStatement);

        //4. Test result
        Assert::equals(3, scope.getDeclarationCount(), t + "A1");
        Assert::notNull(scope.get("x").get(), t + "A2");
        Assert::notNull(scope.get("a").get(), t + "A3");
        Assert::notNull(scope.get("b").get(), t + "A4");
    }


    public: static void getOwnSymbolTest(const std::string& t) {
        EulScope root(nullptr);
        EulScope child1(&root);
        EulScope child2(&root);
        EulScope grandChild(&child1);

        //1. Declare some variables to root
        root.declare("x", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("x")));
        Assert::equals(1, root.getDeclarationCount(), t + "A1");

        root.declare("y", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("y")));
        Assert::equals(2, root.getDeclarationCount(), t + "A2");


        //try the getters
        Assert::stringToken(root.getOwnSymbol("x")->value.get(), "x", t + "B1");
        Assert::stringToken(root.getOwnSymbol("y")->value.get(), "y", t + "B2");
        Assert::null(root.getOwnSymbol("z").get(), t + "B3");

        //try the getters on the sub scopes. Those should give no result
        Assert::null(child1.getOwnSymbol("x").get(), t + "B4");
        Assert::null(child1.getOwnSymbol("y").get(), t + "B5");
        Assert::null(child1.getOwnSymbol("z").get(), t + "B6");

        Assert::null(child2.getOwnSymbol("x").get(), t + "B7");
        Assert::null(child2.getOwnSymbol("y").get(), t + "B8");
        Assert::null(child2.getOwnSymbol("z").get(), t + "B9");

        Assert::null(grandChild.getOwnSymbol("x").get(), t + "B10");
        Assert::null(grandChild.getOwnSymbol("y").get(), t + "B11");
        Assert::null(grandChild.getOwnSymbol("z").get(), t + "B12");


        //2. Declare some individual variables on scopes child1 and child2.
        child1.declare("child1_only", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("child1_only")));
        Assert::equals(1, child1.getDeclarationCount(), t + "C1");

        child2.declare("child2_only", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("child2_only")));
        Assert::equals(1, child2.getDeclarationCount(), t + "C2");


        //test getters again.
        Assert::stringToken(root.getOwnSymbol("x")->value.get(), "x", t + "D1");
        Assert::stringToken(root.getOwnSymbol("y")->value.get(), "y", t + "D2");
        Assert::null(root.getOwnSymbol("child1_only").get(), t + "D3");
        Assert::null(root.getOwnSymbol("child2_only").get(), t + "D4");
        Assert::null(root.getOwnSymbol("z").get(), t + "D5");

        Assert::null(child1.getOwnSymbol("x").get(), t + "D6");
        Assert::null(child1.getOwnSymbol("y").get(), t + "D7");
        Assert::stringToken(child1.getOwnSymbol("child1_only")->value.get(), "child1_only", t + "D8");
        Assert::null(child1.getOwnSymbol("child2_only").get(), t + "D9");
        Assert::null(child1.getOwnSymbol("z").get(), t + "D10");

        Assert::null(child2.getOwnSymbol("x").get(), t + "D11");
        Assert::null(child2.getOwnSymbol("y").get(), t + "D12");
        Assert::null(child2.getOwnSymbol("child1_only").get(), t + "D13");
        Assert::stringToken(child2.getOwnSymbol("child2_only")->value.get(), "child2_only", t + "D14");
        Assert::null(child2.getOwnSymbol("z").get(), t + "D15");

        Assert::null(grandChild.getOwnSymbol("x").get(), t + "D16");
        Assert::null(grandChild.getOwnSymbol("y").get(), t + "D17");
        Assert::null(grandChild.getOwnSymbol("child1_only").get(), t + "D18");
        Assert::null(grandChild.getOwnSymbol("child2_only").get(), t + "D19");
        Assert::null(grandChild.getOwnSymbol("z").get(), t + "D20");
    }

    public: static void declareTest(const std::string& t) {
        EulScope root(nullptr);
        EulScope child1(&root);

        //1. Declare some variables to root
        Assert::that( root.declare("x", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("x"))), t + "A1" );
        Assert::equals(1, root.getDeclarationCount(), t + "A2");

        Assert::that( root.declare("y", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("y"))), t + "A3" );
        Assert::equals(2, root.getDeclarationCount(), t + "A4");

        //2. Try to redefine those same symbols
        try {
            Assert::thatNot( root.declare("x", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("newX"))), t + "B1" );
            Assert::fail(t + " B1: Exception expected due to redefinition of symbol, but none was thrown");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, "B1_code");
            Assert::equals("Symbol x already defined on this scope.", e.message, "B1_message");
        }
        Assert::equals(2, root.getDeclarationCount(), t + "B2");
        Assert::stringToken(root.getOwnSymbol("x")->value.get(), "x", t + "B3");

        //3. Define those variables in a sub scope. This should be allowed.
        Assert::that( child1.declare("x", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("child1_X"))), t + "C1" );
        Assert::equals(1, child1.getDeclarationCount(), t + "C2");

        Assert::that( child1.declare("y", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("child1_Y"))), t + "C3" );
        Assert::equals(2, child1.getDeclarationCount(), t + "C4");
    }

    public: static void getOwnSymbolAsTypeTest(const std::string& t) {
        EulScope root(nullptr);

        //1. Declare one type and one non type.
        auto type = std::make_shared<EulIntegerType>(32, false);
        root.declare("someType", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, type));
        root.declare("notAType", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("123")));

        //2. Get the type
        auto fetched = root.getOwnSymbolAsType("someType");
        Assert::equals(fetched, type.get(), t+"A1");

        //3. Try getting as a type something that is not a type.
        try {
            auto thisWillCrash = root.getOwnSymbolAsType("notAType");
            Assert::fail("Exception expected due to accessing a non-type symbol as a type, but non was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Type not found: notAType", e.message, t+"B2");
        }

        //4. Try accessing a non existing symbol.
        try {
            auto thisWillCrash = root.getOwnSymbolAsType("iDoNotExist");
            Assert::fail("Exception expected due to accessing a non-type symbol as a type, but non was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"C1");
            Assert::equals("Type not found: iDoNotExist", e.message, t+"C2");
        }
    }



    public: static void resetTest(const std::string& t) {
        //1. Create a couple of declarations
        EulScope root(nullptr);
        Assert::that( root.declare("x", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("x"))), t + "A1" );
        Assert::equals(1, root.getDeclarationCount(), t + "A1");

        Assert::that( root.declare("y", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringToken>("y"))), t + "A3" );
        Assert::equals(2, root.getDeclarationCount(), t + "A2");

        //2. reset the scope
        root.reset();
        Assert::equals(0, root.getDeclarationCount(), t + "A3");
    }


    public: static void runAll() {
        declarationGetterTest("EulScopeTest.declarationGetterTest ");
        declareFromStatementTest("EulScopeTest.declareFromStatementTest ");
        getOwnSymbolTest("EulScopeTest.getOwnSymbolTest ");
        declareTest("EulScopeTest.declareTest ");
        resetTest("EulScopeTest.resetTest ");
        getOwnSymbolAsTypeTest("EulScopeTest.getOwnSymbolAsTypeTest ");
    }
};