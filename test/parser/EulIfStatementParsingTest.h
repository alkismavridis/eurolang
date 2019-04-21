#pragma once



class EulIfStatementParsingTest {

    public: static void singleIfTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Simple if statment
        std::stringstream stream = std::stringstream(" var v1; if isTrue { var v2; return v2; } var v1b;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();

        //2. Assert AST
        Assert::equals(3, file->statements->size(), t + "A1 statement count");
        Assert::varDeclarationStatement(file->statements->at(0).get(), t + "A2 pre-if statement");
        Assert::varDeclarationStatement(file->statements->at(2).get(), t + "A3 post-if statement");
        auto asIfStmt = Assert::ifStatement(file->statements->at(1).get(), t + "A4 is if statement");
        Assert::idToken(asIfStmt->ifSection.expression.get(), "isTrue", t + "A5 condition");
        Assert::equals(2, asIfStmt->ifSection.block->statements->size(), t + "A6 statement count");
        Assert::varDeclarationStatement(asIfStmt->ifSection.block->statements->at(0).get(), t + "A7 nested statement1");
        auto asRetStmt = Assert::returnStatement(asIfStmt->ifSection.block->statements->at(1).get(), t + "A8 nested statement2");
        Assert::null(asIfStmt->elseIfs.get(), t + "A9 there are no else ifs");
        Assert::null(asIfStmt->elseSection.get(), t + "A10 there is no else");

        //3. Assert scopes
        Assert::notNull(asIfStmt->ifSection.block->scope.get(), t + "B1 scope not null");
        Assert::equals(file->scope.get(), asIfStmt->ifSection.block->scope->superScope.get(), t + "B2 a new scope is created, and has the proper super scope");
        Assert::notNull(file->scope->getOwnSymbol("v1").get(), t+"B3");
        Assert::notNull(file->scope->getOwnSymbol("v1b").get(), t+"B4");
        Assert::notNull(asIfStmt->ifSection.block->scope->getOwnSymbol("v2").get(), t+"B5 var is declared on if-scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1").get(), t+"B6 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1b").get(), t+"B7 parent scope is not the if scope");
        Assert::null(file->scope->getOwnSymbol("v2").get(), t+"B8 var inside if is not on parent scope");

        auto asId = Assert::idToken(asRetStmt->exp.get(), "v2", t+"B9");
        Assert::equals(asIfStmt->ifSection.block->scope.get(), asId->scope.get(), t+"B10 id inside the if-scope uses the if-scope");
    }


    public: static void ifElseTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Simple if statment
        std::stringstream stream = std::stringstream(" var v1; if isTrue { var v2; return v2; }\nelse {var v3; return v3;} var v1b;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();

        //2. Check if block
        Assert::equals(3, file->statements->size(), t + "A1 statement count");
        Assert::varDeclarationStatement(file->statements->at(0).get(), t + "A2 pre-if statement");
        Assert::varDeclarationStatement(file->statements->at(2).get(), t + "A3 post-if statement");
        auto asIfStmt = Assert::ifStatement(file->statements->at(1).get(), t + "A4 is if statement");
        Assert::idToken(asIfStmt->ifSection.expression.get(), "isTrue", t + "A5 condition");
        Assert::equals(2, asIfStmt->ifSection.block->statements->size(), t+"A6 statement count");
        Assert::varDeclarationStatement(asIfStmt->ifSection.block->statements->at(0).get(), t + "A7 nested statement1");
        auto asRetStmt = Assert::returnStatement(asIfStmt->ifSection.block->statements->at(1).get(), t + "A8 nested statement2");
        Assert::null(asIfStmt->elseIfs.get(), t + "A9 there are no else ifs");

        //3. Check else block
        Assert::notNull(asIfStmt->elseSection.get(), t + "B1 there is else");
        Assert::equals(2, asIfStmt->elseSection->statements->size(), t+"B2 statement count");
        Assert::varDeclarationStatement(asIfStmt->elseSection->statements->at(0).get(), t + "B3 nested statement1");
        auto asRetStmt2 = Assert::returnStatement(asIfStmt->elseSection->statements->at(1).get(), t + "B4 nested statement2");

        //4. Assert parent scope
        Assert::notNull(file->scope->getOwnSymbol("v1").get(), t+"C1");
        Assert::notNull(file->scope->getOwnSymbol("v1b").get(), t+"C2");
        Assert::null(file->scope->getOwnSymbol("v2").get(), t+"C3 var inside if is not on parent scope");
        Assert::null(file->scope->getOwnSymbol("v3").get(), t+"C4 var inside else is not on parent scope");

        //5. Check if scope
        Assert::notNull(asIfStmt->ifSection.block->scope.get(), t + "D1 if-scope not null");
        Assert::equals(file->scope.get(), asIfStmt->ifSection.block->scope->superScope.get(), t + "D2 a new scope is created in if, and has the proper super scope");
        Assert::notNull(asIfStmt->ifSection.block->scope->getOwnSymbol("v2").get(), t+"D3 var is declared on if-scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1").get(), t+"D4 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1b").get(), t+"D5 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v3").get(), t+"D6 else scope is not the if scope");
        auto asId = Assert::idToken(asRetStmt->exp.get(), "v2", t+"D7");
        Assert::equals(asIfStmt->ifSection.block->scope.get(), asId->scope.get(), t+"D8 id inside the if-scope uses the if-scope");

        //5. Check else scope
        Assert::notNull(asIfStmt->elseSection->scope.get(), t + "E1 else-scope not null");
        Assert::equals(file->scope.get(), asIfStmt->elseSection->scope->superScope.get(), t + "E2 a new scope is created in else, and has the proper super scope");
        Assert::notNull(asIfStmt->elseSection->scope->getOwnSymbol("v3").get(), t+"E3 var is declared on else-scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v1").get(), t+"E4 parent scope is not the else scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v1b").get(), t+"E5 parent scope is not the else scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v2").get(), t+"E6 else scope is not the if scope");
        asId = Assert::idToken(asRetStmt2->exp.get(), "v3", t+"E7");
        Assert::equals(asIfStmt->elseSection->scope.get(), asId->scope.get(), t+"E8 id inside the else-scope uses the else-scope");
    }

    public: static void ifElseTestWithoutBlock(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Simple if statment
        std::stringstream stream = std::stringstream(" var v1; if isTrue { var v2; return v2; }\nelse var v3; var v1b;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();

        //2. Check if block
        Assert::equals(3, file->statements->size(), t + "A1 statement count");
        Assert::varDeclarationStatement(file->statements->at(0).get(), t + "A2 pre-if statement");
        Assert::varDeclarationStatement(file->statements->at(2).get(), t + "A3 post-if statement");
        auto asIfStmt = Assert::ifStatement(file->statements->at(1).get(), t + "A4 is if statement");
        Assert::idToken(asIfStmt->ifSection.expression.get(), "isTrue", t + "A5 condition");
        Assert::equals(2, asIfStmt->ifSection.block->statements->size(), t+"A6 statement count");
        Assert::varDeclarationStatement(asIfStmt->ifSection.block->statements->at(0).get(), t + "A7 nested statement1");
        auto asRetStmt = Assert::returnStatement(asIfStmt->ifSection.block->statements->at(1).get(), t + "A8 nested statement2");
        Assert::null(asIfStmt->elseIfs.get(), t + "A9 there are no else ifs");

        //3. Check else block
        Assert::notNull(asIfStmt->elseSection.get(), t + "B1 there is else");
        Assert::equals(1, asIfStmt->elseSection->statements->size(), t+"B2 statement count");
        Assert::varDeclarationStatement(asIfStmt->elseSection->statements->at(0).get(), t + "B3 nested statement1");

        //4. Assert parent scope
        Assert::notNull(file->scope->getOwnSymbol("v1").get(), t+"C1");
        Assert::notNull(file->scope->getOwnSymbol("v1b").get(), t+"C2");
        Assert::null(file->scope->getOwnSymbol("v2").get(), t+"C3 var inside if is not on parent scope");
        Assert::null(file->scope->getOwnSymbol("v3").get(), t+"C4 var inside else is not on parent scope");

        //5. Check if scope
        Assert::notNull(asIfStmt->ifSection.block->scope.get(), t + "D1 if-scope not null");
        Assert::equals(file->scope.get(), asIfStmt->ifSection.block->scope->superScope.get(), t + "D2 a new scope is created in if, and has the proper super scope");
        Assert::notNull(asIfStmt->ifSection.block->scope->getOwnSymbol("v2").get(), t+"D3 var is declared on if-scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1").get(), t+"D4 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1b").get(), t+"D5 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v3").get(), t+"D6 else scope is not the if scope");
        auto asId = Assert::idToken(asRetStmt->exp.get(), "v2", t+"D7");
        Assert::equals(asIfStmt->ifSection.block->scope.get(), asId->scope.get(), t+"D8 id inside the if-scope uses the if-scope");

        //5. Check else scope
        Assert::notNull(asIfStmt->elseSection->scope.get(), t + "E1 else-scope not null");
        Assert::equals(file->scope.get(), asIfStmt->elseSection->scope->superScope.get(), t + "E2 a new scope is created in else, and has the proper super scope");
        Assert::notNull(asIfStmt->elseSection->scope->getOwnSymbol("v3").get(), t+"E3 var is declared on else-scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v1").get(), t+"E4 parent scope is not the else scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v1b").get(), t+"E5 parent scope is not the else scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v2").get(), t+"E6 else scope is not the if scope");
    }


    public: static void ifWithTwoElseIfs(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Simple if statment
        std::stringstream stream = std::stringstream(" var v1; if isOne { var v2; return v2; }\nelse  \t if isTwo { var v3; return v3; }\n else  \t if isThree { var v4; return v4; }\n var v1b;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();

        //2. Check if block
        Assert::equals(3, file->statements->size(), t + "A1 statement count");
        Assert::varDeclarationStatement(file->statements->at(0).get(), t + "A2 pre-if statement");
        Assert::varDeclarationStatement(file->statements->at(2).get(), t + "A3 post-if statement");
        auto asIfStmt = Assert::ifStatement(file->statements->at(1).get(), t + "A4 is if statement");
        Assert::idToken(asIfStmt->ifSection.expression.get(), "isOne", t + "A5 condition");
        Assert::equals(2, asIfStmt->ifSection.block->statements->size(), t+"A6 statement count");
        Assert::varDeclarationStatement(asIfStmt->ifSection.block->statements->at(0).get(), t + "A7 nested statement1");
        auto asRetStmt = Assert::returnStatement(asIfStmt->ifSection.block->statements->at(1).get(), t + "A8 nested statement2");
        Assert::null(asIfStmt->elseSection.get(), t + "A9 there is no else");

        //3. Check first else-if block
        Assert::notNull(asIfStmt->elseIfs.get(), t + "B1 there are else ifs");
        Assert::equals(2, asIfStmt->elseIfs->size(), t + "B2 there are 2 else ifs");
        Assert::idToken(asIfStmt->elseIfs->at(0)->expression.get(), "isTwo", t + "B3 condition");
        Assert::equals(2, asIfStmt->elseIfs->at(0)->block->statements->size(), t+"B4 statement count");
        Assert::varDeclarationStatement(asIfStmt->elseIfs->at(0)->block->statements->at(0).get(), t + "B5 nested statement1");
        auto asRetStmt2 = Assert::returnStatement(asIfStmt->elseIfs->at(0)->block->statements->at(1).get(), t + "A8 nested statement2");

        //4. Check second else-if block
        Assert::idToken(asIfStmt->elseIfs->at(1)->expression.get(), "isThree", t + "C1 condition");
        Assert::equals(2, asIfStmt->elseIfs->at(1)->block->statements->size(), t+"C2 statement count");
        Assert::varDeclarationStatement(asIfStmt->elseIfs->at(1)->block->statements->at(0).get(), t + "C3 nested statement1");
        auto asRetStmt3 = Assert::returnStatement(asIfStmt->elseIfs->at(1)->block->statements->at(1).get(), t + "C4 nested statement2");


        //5. Assert parent scope
        Assert::notNull(file->scope->getOwnSymbol("v1").get(), t+"D1");
        Assert::notNull(file->scope->getOwnSymbol("v1b").get(), t+"D2");
        Assert::null(file->scope->getOwnSymbol("v2").get(), t+"D3 var inside if is not on parent scope");
        Assert::null(file->scope->getOwnSymbol("v3").get(), t+"D4 var inside first else-if is not on parent scope");
        Assert::null(file->scope->getOwnSymbol("v4").get(), t+"D5 var inside second else-if is not on parent scope");

        //6. Check if scope
        Assert::notNull(asIfStmt->ifSection.block->scope.get(), t + "E1 if-scope not null");
        Assert::equals(file->scope.get(), asIfStmt->ifSection.block->scope->superScope.get(), t + "E2 a new scope is created in if, and has the proper super scope");
        Assert::notNull(asIfStmt->ifSection.block->scope->getOwnSymbol("v2").get(), t+"E3 var is declared on if-scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1").get(), t+"E4 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1b").get(), t+"E5 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v3").get(), t+"E6 first else-if scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v4").get(), t+"E7 second else-if scope is not the if scope");
        auto asId = Assert::idToken(asRetStmt->exp.get(), "v2", t+"E8");
        Assert::equals(asIfStmt->ifSection.block->scope.get(), asId->scope.get(), t+"E9 id inside the if-scope uses the if-scope");

        //7. Check first else-if scope
        Assert::notNull(asIfStmt->elseIfs->at(0)->block->scope.get(), t + "F1 first else-if-scope is not null");
        Assert::equals(file->scope.get(), asIfStmt->elseIfs->at(0)->block->scope->superScope.get(), t + "F2 a new scope is created in first else-if, and has the proper super scope");
        Assert::notNull(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v3").get(), t+"F3 var is declared on first else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v1").get(), t+"F4 parent scope is not the first else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v1b").get(), t+"F5 parent scope is not the first else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v2").get(), t+"F6 first else-if-scope is not the if scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v4").get(), t+"F7 first else-if-scope is not the second else-if-scope");
        asId = Assert::idToken(asRetStmt2->exp.get(), "v3", t+"F8");
        Assert::equals(asIfStmt->elseIfs->at(0)->block->scope.get(), asId->scope.get(), t+"F9 id inside the first-else-if-scope uses the first-else-if-scope");

        //8. Check second else-if scope
        Assert::notNull(asIfStmt->elseIfs->at(1)->block->scope.get(), t + "G1 second else-if-scope is not null");
        Assert::equals(file->scope.get(), asIfStmt->elseIfs->at(1)->block->scope->superScope.get(), t + "G2 a new scope is created in second else-if, and has the proper super scope");
        Assert::notNull(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v4").get(), t+"G3 var is declared on second else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v1").get(), t+"G4 parent scope is not the second else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v1b").get(), t+"G5 parent scope is not the second else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v2").get(), t+"G6 second else-if-scope is not the if scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v3").get(), t+"G7 second else-if-scope is not the first else-if-scope");
        asId = Assert::idToken(asRetStmt3->exp.get(), "v4", t+"G8");
        Assert::equals(asIfStmt->elseIfs->at(1)->block->scope.get(), asId->scope.get(), t+"G9 id inside the second-else-if-scope uses the second-else-if-scope");
    }

    public: static void ifWithTwoElseIfsAndElse(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Simple if statment
        std::stringstream stream = std::stringstream(" var v1; if isOne { var v2; return v2; }\nelse  \t if isTwo { var v3; return v3; }\n else  \t if isThree { var v4; return v4; }\n else var v5; var v1b;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();

        //2. Check if block
        Assert::equals(3, file->statements->size(), t + "A1 statement count");
        Assert::varDeclarationStatement(file->statements->at(0).get(), t + "A2 pre-if statement");
        Assert::varDeclarationStatement(file->statements->at(2).get(), t + "A3 post-if statement");
        auto asIfStmt = Assert::ifStatement(file->statements->at(1).get(), t + "A4 is if statement");
        Assert::idToken(asIfStmt->ifSection.expression.get(), "isOne", t + "A5 condition");
        Assert::equals(2, asIfStmt->ifSection.block->statements->size(), t+"A6 statement count");
        Assert::varDeclarationStatement(asIfStmt->ifSection.block->statements->at(0).get(), t + "A7 nested statement1");
        auto asRetStmt = Assert::returnStatement(asIfStmt->ifSection.block->statements->at(1).get(), t + "A8 nested statement2");

        //3. Check first else-if block
        Assert::notNull(asIfStmt->elseIfs.get(), t + "B1 there are else ifs");
        Assert::equals(2, asIfStmt->elseIfs->size(), t + "B2 there are 2 else ifs");
        Assert::idToken(asIfStmt->elseIfs->at(0)->expression.get(), "isTwo", t + "B3 condition");
        Assert::equals(2, asIfStmt->elseIfs->at(0)->block->statements->size(), t+"B4 statement count");
        Assert::varDeclarationStatement(asIfStmt->elseIfs->at(0)->block->statements->at(0).get(), t + "B5 nested statement1");
        auto asRetStmt2 = Assert::returnStatement(asIfStmt->elseIfs->at(0)->block->statements->at(1).get(), t + "A8 nested statement2");

        //4. Check second else-if block
        Assert::idToken(asIfStmt->elseIfs->at(1)->expression.get(), "isThree", t + "C1 condition");
        Assert::equals(2, asIfStmt->elseIfs->at(1)->block->statements->size(), t+"C2 statement count");
        Assert::varDeclarationStatement(asIfStmt->elseIfs->at(1)->block->statements->at(0).get(), t + "C3 nested statement1");
        auto asRetStmt3 = Assert::returnStatement(asIfStmt->elseIfs->at(1)->block->statements->at(1).get(), t + "C4 nested statement2");

        //5. Check else statement
        Assert::notNull(asIfStmt->elseSection.get(), t + "D1 there is else");
        Assert::equals(1, asIfStmt->elseSection->statements->size(), t+"D2 statement count");
        Assert::varDeclarationStatement(asIfStmt->elseSection->statements->at(0).get(), t + "D3 nested statement1");


        //6. Assert parent scope
        Assert::notNull(file->scope->getOwnSymbol("v1").get(), t+"E1");
        Assert::notNull(file->scope->getOwnSymbol("v1b").get(), t+"E2");
        Assert::null(file->scope->getOwnSymbol("v2").get(), t+"E3 var inside if is not on parent scope");
        Assert::null(file->scope->getOwnSymbol("v3").get(), t+"E4 var inside first else-if is not on parent scope");
        Assert::null(file->scope->getOwnSymbol("v4").get(), t+"E5 var inside second else-if is not on parent scope");
        Assert::null(file->scope->getOwnSymbol("v5").get(), t+"E5 var inside else is not on parent scope");

        //7. Check if scope
        Assert::notNull(asIfStmt->ifSection.block->scope.get(), t + "F1 if-scope not null");
        Assert::equals(file->scope.get(), asIfStmt->ifSection.block->scope->superScope.get(), t + "F2 a new scope is created in if, and has the proper super scope");
        Assert::notNull(asIfStmt->ifSection.block->scope->getOwnSymbol("v2").get(), t+"F3 var is declared on if-scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1").get(), t+"F4 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v1b").get(), t+"F5 parent scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v3").get(), t+"F6 first else-if scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v4").get(), t+"F7 second else-if scope is not the if scope");
        Assert::null(asIfStmt->ifSection.block->scope->getOwnSymbol("v5").get(), t+"F8 else scope is not the if scope");
        auto asId = Assert::idToken(asRetStmt->exp.get(), "v2", t+"F9");
        Assert::equals(asIfStmt->ifSection.block->scope.get(), asId->scope.get(), t+"F10 id inside the if-scope uses the if-scope");

        //8. Check first else-if scope
        Assert::notNull(asIfStmt->elseIfs->at(0)->block->scope.get(), t + "G1 first else-if-scope is not null");
        Assert::equals(file->scope.get(), asIfStmt->elseIfs->at(0)->block->scope->superScope.get(), t + "G2 a new scope is created in first else-if, and has the proper super scope");
        Assert::notNull(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v3").get(), t+"G3 var is declared on first else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v1").get(), t+"G4 parent scope is not the first else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v1b").get(), t+"G5 parent scope is not the first else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v2").get(), t+"G6 first else-if-scope is not the if scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v4").get(), t+"G7 first else-if-scope is not the second else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(0)->block->scope->getOwnSymbol("v5").get(), t+"G8 first else-if-scope is not the else-scope");
        asId = Assert::idToken(asRetStmt2->exp.get(), "v3", t+"G9");
        Assert::equals(asIfStmt->elseIfs->at(0)->block->scope.get(), asId->scope.get(), t+"G10 id inside the first-else-if-scope uses the first-else-if-scope");

        //9. Check second else-if scope
        Assert::notNull(asIfStmt->elseIfs->at(1)->block->scope.get(), t + "H1 second else-if-scope is not null");
        Assert::equals(file->scope.get(), asIfStmt->elseIfs->at(1)->block->scope->superScope.get(), t + "H2 a new scope is created in second else-if, and has the proper super scope");
        Assert::notNull(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v4").get(), t+"H3 var is declared on second else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v1").get(), t+"H4 parent scope is not the second else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v1b").get(), t+"H5 parent scope is not the second else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v2").get(), t+"H6 second else-if-scope is not the if scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v3").get(), t+"H7 second else-if-scope is not the first else-if-scope");
        Assert::null(asIfStmt->elseIfs->at(1)->block->scope->getOwnSymbol("v5").get(), t+"H8 second else-if-scope is not the else-scope");
        asId = Assert::idToken(asRetStmt3->exp.get(), "v4", t+"H9");
        Assert::equals(asIfStmt->elseIfs->at(1)->block->scope.get(), asId->scope.get(), t+"H10 id inside the second-else-if-scope uses the second-else-if-scope");

        //10. Check the else scope
        Assert::notNull(asIfStmt->elseSection->scope.get(), t + "J1 else-scope not null");
        Assert::equals(file->scope.get(), asIfStmt->elseSection->scope->superScope.get(), t + "J2 a new scope is created in else, and has the proper super scope");
        Assert::notNull(asIfStmt->elseSection->scope->getOwnSymbol("v5").get(), t+"J3 var is declared on else-scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v1").get(), t+"J4 parent scope is not the else scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v1b").get(), t+"J5 parent scope is not the else scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v2").get(), t+"J6 else scope is not the if scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v3").get(), t+"J7 else scope is not the first else-if scope");
        Assert::null(asIfStmt->elseSection->scope->getOwnSymbol("v4").get(), t+"J8 else scope is not the second else-if scope");
    }


    public: static void runAll() {
        singleIfTest("EulIfStatementParsingTest.singleIfTest ");
        ifElseTest("EulIfStatementParsingTest.ifElseTest ");
        ifElseTestWithoutBlock("EulIfStatementParsingTest.ifElseTestWithoutBlock ");
        ifWithTwoElseIfs("EulIfStatementParsingTest.ifWithTwoElseIfs ");
        ifWithTwoElseIfsAndElse("EulIfStatementParsingTest.ifWithTwoElseIfsAndElse ");
    }
};
