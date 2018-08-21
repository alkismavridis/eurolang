#pragma once




class EulParserTest {

    private: static void varDeclarationTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. One var per declaration
        std::stringstream stream = std::stringstream("var x=5; var y; var z:UInt16=7; const z2 = 8;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert AST
        Assert::equals(EulTokenType::AST, file->statements->operator[](0)->getType(), t + "A2");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](0).get())->getAstType(), t + "A3");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](0).get())->getStatementType(), t + "A4");
        Assert::equals(yy::EulParser::token::VAR, ((VarDeclarationStatement*)file->statements->operator[](0).get())->varType, t + "A5");
        Assert::equals(1, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->size(), t + "A6");
        Assert::equals("x", ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->id->name, t + "A7");
        Assert::equals(EulTokenType::INT, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A8");
        Assert::equals(5, ((EulIntToken*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->value, t + "A9");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->varType.get(), t + "A10");

        Assert::equals(EulTokenType::AST, file->statements->operator[](1)->getType(), t + "B1");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](1).get())->getAstType(), t + "B2");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](1).get())->getStatementType(), t + "B3");
        Assert::equals(yy::EulParser::token::VAR, ((VarDeclarationStatement*)file->statements->operator[](1).get())->varType, t + "B4");
        Assert::equals(1, ((VarDeclarationStatement*)file->statements->operator[](1).get())->declarations->size(), t + "B5");
        Assert::equals("y", ((VarDeclarationStatement*)file->statements->operator[](1).get())->declarations->operator[](0)->id->name, t + "B6");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](1).get())->declarations->operator[](0)->value.get(), t + "B7");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](1).get())->declarations->operator[](0)->varType.get(), t + "B8");


        Assert::equals(EulTokenType::AST, file->statements->operator[](2)->getType(), t + "C1");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](2).get())->getAstType(), t + "C2");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](2).get())->getStatementType(), t + "C3");
        Assert::equals(yy::EulParser::token::VAR, ((VarDeclarationStatement*)file->statements->operator[](2).get())->varType, t + "C4");
        Assert::equals(1, ((VarDeclarationStatement*)file->statements->operator[](2).get())->declarations->size(), t + "C5");
        Assert::equals("z", ((VarDeclarationStatement*)file->statements->operator[](2).get())->declarations->operator[](0)->id->name, t + "C6");
        Assert::equals(EulTokenType::INT, ((VarDeclarationStatement*)file->statements->operator[](2).get())->declarations->operator[](0)->value->getType(), t + "C7");
        Assert::equals(7, ((EulIntToken*)((VarDeclarationStatement*)file->statements->operator[](2).get())->declarations->operator[](0)->value.get())->value, t + "C8");
        Assert::equals(((VarDeclarationStatement*)file->statements->operator[](2).get())->declarations->operator[](0)->varType.get(), compiler.program.nativeTypes.uint16Type.get(), t + "C9");


        Assert::equals(EulTokenType::AST, file->statements->operator[](3)->getType(), t + "D1");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](3).get())->getAstType(), t + "D2");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](3).get())->getStatementType(), t + "D3");
        Assert::equals(yy::EulParser::token::CONST, ((VarDeclarationStatement*)file->statements->operator[](3).get())->varType, t + "D4");
        Assert::equals(1, ((VarDeclarationStatement*)file->statements->operator[](3).get())->declarations->size(), t + "D5");
        Assert::equals("z2", ((VarDeclarationStatement*)file->statements->operator[](3).get())->declarations->operator[](0)->id->name, t + "D6");
        Assert::equals(EulTokenType::INT, ((VarDeclarationStatement*)file->statements->operator[](3).get())->declarations->operator[](0)->value->getType(), t + "D7");
        Assert::equals(8, ((EulIntToken*)((VarDeclarationStatement*)file->statements->operator[](3).get())->declarations->operator[](0)->value.get())->value, t + "D8");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](3).get())->declarations->operator[](0)->varType.get(), t + "D9");

        //3. Parse the source file
        compiler.clearErrors();
        stream = std::stringstream("var x=\"hello\", y:Int64, z='\\n'; ");
        file = compiler.program.getSource("myFile2.eul", 1);
        ctx.sourceFile = file.get();
        ctx.currentScope = &file->scope;
        scanner.switch_streams(&stream);
        parser.parse();

        //4. Check the result
        Assert::equals(EulTokenType::AST, file->statements->operator[](0)->getType(), t + "E1");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](0).get())->getAstType(), t + "E2");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](0).get())->getStatementType(), t + "E3");
        Assert::equals(yy::EulParser::token::VAR, ((VarDeclarationStatement*)file->statements->operator[](0).get())->varType, t + "E4");
        Assert::equals(3, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->size(), t + "E5");

        Assert::equals("x", ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->id->name, t + "E6");
        Assert::equals(EulTokenType::STRING, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "E7");
        Assert::equals("hello", ((EulStringToken*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->value, t + "E8");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->varType.get(), t + "E9");

        Assert::equals("y", ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](1)->id->name, t + "F1");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](1)->value.get(), t + "F2");
        Assert::equals(((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](1)->varType.get(), compiler.program.nativeTypes.int64Type.get(), t + "F3");


        Assert::equals("z", ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](2)->id->name, t + "G1");
        Assert::equals(EulTokenType::CHAR, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](2)->value->getType(), t + "G2");
        Assert::equals('\n', ((EulCharToken*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](2)->value.get())->value, t + "G3");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](2)->varType.get(), t + "G4");
    }


    private: static void ltrSimpleExpressionTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x=\"5\"+y-x-7;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* inExp = (EulInfixExp*)exp;
        Assert::intToken(inExp->right.get(), 7, 32, false, t + "B1");
        Assert::equals(&EUL_OPERATORS.minusOperator, inExp->oper, t + "B2");

        inExp = (EulInfixExp*)(inExp->left.get());
        Assert::idToken(inExp->right.get(), "x", t + "C1");
        Assert::equals(&EUL_OPERATORS.minusOperator, inExp->oper, t + "C2");

        inExp = (EulInfixExp*)(inExp->left.get());
        Assert::idToken(inExp->right.get(), "y", t + "D1");
        Assert::equals(&EUL_OPERATORS.plusOperator, inExp->oper, t + "D2");
        Assert::stringToken(inExp->left.get(), "5", t + "D3");
    }

    private: static void rtlSimpleExpressionTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= \"5\" = y += x /= 7u1;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* inExp = (EulInfixExp*)exp;
        Assert::stringToken(inExp->left.get(), "5", t + "B1");
        Assert::equals(&EUL_OPERATORS.assignOperator, inExp->oper, t + "B2");

        inExp = (EulInfixExp*)(inExp->right.get());
        Assert::idToken(inExp->left.get(), "y", t + "C1");
        Assert::equals(&EUL_OPERATORS.assignPlusOperator, inExp->oper, t + "C2");

        inExp = (EulInfixExp*)(inExp->right.get());
        Assert::idToken(inExp->left.get(), "x", t + "D1");
        Assert::equals(&EUL_OPERATORS.assignDivOperator, inExp->oper, t + "D2");
        Assert::intToken(inExp->right.get(), 7, 1, true, t + "D3");
    }

    private: static void ltrMixedPrioritiesTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= 1 || 4 == 5 + 8*10 - x.t.g * 5;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* inExp = (EulInfixExp*)exp;

        //3. Assert tree
        Assert::intToken(inExp->left.get(), 1, 32, false, t + "B1");
        Assert::equals(&EUL_OPERATORS.orOperator, inExp->oper, t + "B2");

        inExp = (EulInfixExp*)(inExp->right.get());
        Assert::intToken(inExp->left.get(), 4, 32, false, t + "C1");
        Assert::equals(&EUL_OPERATORS.equalsOperator, inExp->oper, t + "C2");

        inExp = Assert::infixExp(inExp->right.get(), t + "D1");
        EulInfixExp* currentSearching = inExp; //we back it up, so we return later to assert the right part of it.

        inExp = Assert::infixExp(inExp->left.get(), t + "D2");
        Assert::equals(&EUL_OPERATORS.plusOperator, inExp->oper, t + "D3");

        Assert::intToken(inExp->left.get(), 5, 32, false, t + "D4");
        inExp = Assert::infixExp(inExp->right.get(), t + "D5");
        Assert::intToken(inExp->left.get(), 8, 32, false, t + "D7");
        Assert::equals(&EUL_OPERATORS.starOperator, inExp->oper, t + "D6");
        Assert::intToken(inExp->right.get(), 10, 32, false, t + "D8");

        Assert::equals(&EUL_OPERATORS.minusOperator, currentSearching->oper, t + "E1");
        inExp = Assert::infixExp(currentSearching->right.get(), t + "E2");

        currentSearching = inExp; //save it for checking its right part later
        inExp = Assert::infixExp(currentSearching->left.get(), t + "E2");
        inExp = Assert::infixExp(inExp->left.get(), t + "E3");

        Assert::idToken(inExp->left.get(), "x", t + "F1");
        Assert::equals(&EUL_OPERATORS.dotOperator, inExp->oper, t + "F2");
        Assert::idToken(inExp->right.get(), "t", t + "F3");

        inExp = Assert::infixExp(currentSearching->left.get(), t + "G1");
        Assert::equals(&EUL_OPERATORS.dotOperator, inExp->oper, t + "G3");
        Assert::idToken(inExp->right.get(), "g", t + "G3");

        inExp = currentSearching;
        Assert::equals(&EUL_OPERATORS.starOperator, inExp->oper, t + "H1");
        Assert::intToken(inExp->right.get(), 5, 32, false, t + "H2");
    }

    private: static void prefixExpTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= x * -y + ~++z;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* level1 = (EulInfixExp*)exp; //save it for lated checks on its right side
        Assert::equals(&EUL_OPERATORS.plusOperator, level1->oper, t + "C4");

        EulInfixExp* currentInf = Assert::infixExp(level1->left.get(), t + "B1");
        Assert::idToken(currentInf->left.get(), "x", t + "B2");
        Assert::equals(&EUL_OPERATORS.starOperator, currentInf->oper, t + "B3");

        EulPrefixExp* currentPref = Assert::prefixExp(currentInf->right.get(), t + "C1");
        Assert::equals(&EUL_OPERATORS.minusOperator, currentPref->oper, t + "C2");
        Assert::idToken(currentPref->exp.get(), "y", t + "C3");

        currentPref = Assert::prefixExp(level1->right.get(), t + "D1");
        Assert::equals(&EUL_OPERATORS.tildeOperator, currentPref->oper, t + "D2");
        currentPref = Assert::prefixExp(currentPref->exp.get(), t + "D3");
        Assert::equals(&EUL_OPERATORS.increaseOperator, currentPref->oper, t + "D4");
        Assert::idToken(currentPref->exp.get(), "z", t + "D5");
    }



    private: static void suffixExpTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= x * y-- + z++;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* level1 = (EulInfixExp*)exp; //save it for later checks on its right side
        EulInfixExp* currentInf = Assert::infixExp(level1->left.get(), t + "B1");
        Assert::idToken(currentInf->left.get(), "x", t + "B2");
        Assert::equals(&EUL_OPERATORS.starOperator, currentInf->oper, t + "B3");
        EulSuffixExp* currentPref = Assert::suffixExp(currentInf->right.get(), t + "C1");

        Assert::equals(&EUL_OPERATORS.decreaseOperator, currentPref->oper, t + "C2");
        Assert::idToken(currentPref->exp.get(), "y", t + "C3");
        Assert::equals(&EUL_OPERATORS.plusOperator, level1->oper, t + "C4");


        currentPref = Assert::suffixExp(level1->right.get(), t + "D1");
        Assert::equals(&EUL_OPERATORS.increaseOperator, currentPref->oper, t + "D2");
        Assert::idToken(currentPref->exp.get(), "z", t + "D3");
    }

    private: static void infixParenthesisTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= x*(y+1);");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* infixExp = (EulInfixExp*)exp; //save it for later checks on its right side
        Assert::idToken(infixExp->left.get(), "x", t + "B1");
        Assert::equals(&EUL_OPERATORS.starOperator, infixExp->oper, t + "B2");
        infixExp = Assert::infixExp(infixExp->right.get(), t + "B3");

        Assert::idToken(infixExp->left.get(), "y", t + "C1");
        Assert::equals(&EUL_OPERATORS.plusOperator, infixExp->oper, t + "C2");
        Assert::intToken(infixExp->right.get(), 1, 32, false, t + "C3");
    }

    private: static void prefixParenthesisTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= --(x+y);");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::PREFIX_EXP, exp->getExpressionType(), t + "A3");

        EulPrefixExp* topLevel = (EulPrefixExp*)exp; //save it for later checks on its right side
        Assert::equals(&EUL_OPERATORS.decreaseOperator, topLevel->oper, t + "B2");
        EulInfixExp* infixExp = Assert::infixExp(topLevel->exp.get(), t + "B3");

        Assert::idToken(infixExp->left.get(), "x", t + "C1");
        Assert::equals(&EUL_OPERATORS.plusOperator, infixExp->oper, t + "C2");
        Assert::idToken(infixExp->right.get(), "y", t + "C3");
    }



    private: static void suffixParenthesisTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= (x+y)++;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::SUFFIX_EXP, exp->getExpressionType(), t + "A3");

        EulSuffixExp* topLevel = (EulSuffixExp*)exp; //save it for later checks on its right side
        Assert::equals(&EUL_OPERATORS.increaseOperator, topLevel->oper, t + "B2");
        EulInfixExp* infixExp = Assert::infixExp(topLevel->exp.get(), t + "B3");

        Assert::idToken(infixExp->left.get(), "x", t + "C1");
        Assert::equals(&EUL_OPERATORS.plusOperator, infixExp->oper, t + "C2");
        Assert::idToken(infixExp->right.get(), "y", t + "C3");
    }

    private: static void simpleFunctionCallTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= y();");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::FUNCTION_CALL, exp->getExpressionType(), t + "A3");

        EulFunctionCallExp* funcCall = (EulFunctionCallExp*)exp; //save it for later checks on its right side
        Assert::idToken(funcCall->func.get(), "y", t + "B1");
        Assert::null(funcCall->params.get(), t + "B2");
    }

    private: static void functionCallTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= a.b(5, f(6u)) - 3*x(1)();");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* root = (EulInfixExp*)exp; //save it for later checks on its right side

        Assert::equals(&EUL_OPERATORS.minusOperator, root->oper, t + "B1");
        EulInfixExp* rootL = Assert::infixExp(root->left.get(), t+"B2");
        Assert::equals(&EUL_OPERATORS.dotOperator, rootL->oper, t + "B3");
        Assert::idToken(rootL->left.get(), "a", t + "B3");

        EulFunctionCallExp* rootLR = Assert::funcCall(rootL->right.get(), t+"B4");
        Assert::idToken(rootLR->func.get(), "b", t + "B5");
        Assert::equals(2, rootLR->params->size(), t + "B6");
        Assert::intToken(rootLR->params->at(0).get(), 5, 32, false, t + "B7");

        EulFunctionCallExp* rootLR2 = Assert::funcCall(rootLR->params->at(1).get(), t+"B8");
        Assert::idToken(rootLR2->func.get(), "f", t + "B9");
        Assert::equals(1, rootLR2->params->size(), t + "B10");
        Assert::intToken(rootLR2->params->at(0).get(), 6, 32, true, t + "B11");

        //Test right part: 3*x(1)(2)
        EulInfixExp* rootR = Assert::infixExp(root->right.get(), t+"C1");
        Assert::intToken(rootR->left.get(), 3, 32, false, t+"C2");
        EulFunctionCallExp* rootRR = Assert::funcCall(rootR->right.get(), t+"C3");
        Assert::null(rootRR->params.get(), t + "C4");

        EulFunctionCallExp* rootRR2 = Assert::funcCall(rootRR->func.get(), t+"C5");
        Assert::idToken(rootRR2->func.get(), "x", t + "C6");
        Assert::equals(1, rootRR2->params->size(), t + "C7");
        Assert::intToken(rootRR2->params->at(0).get(), 1, 32, false, t + "C8");
    }


    private: static void arrayAccessTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= a.b[5] - 3*x(1)[y];");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get())->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0).get())->declarations->operator[](0)->value.get();
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* root = (EulInfixExp*)exp; //save it for later checks on its right side

        Assert::equals(&EUL_OPERATORS.minusOperator, root->oper, t + "B1");
        EulInfixExp* rootL = Assert::infixExp(root->left.get(), t+"B2");
        Assert::equals(&EUL_OPERATORS.dotOperator, rootL->oper, t + "B3");
        Assert::idToken(rootL->left.get(), "a", t + "B3");

        EulArrayAccessExp* rootLR = Assert::arrayAccess(rootL->right.get(), t+"B4");
        Assert::idToken(rootLR->obj.get(), "b", t + "B5");
        Assert::intToken(rootLR->index.get(), 5, 32, false, t + "B7");

        //Test right part: 3*x(1)[y]
        EulInfixExp* rootR = Assert::infixExp(root->right.get(), t+"C1");
        Assert::intToken(rootR->left.get(), 3, 32, false, t+"C2");
        EulArrayAccessExp* rootRR = Assert::arrayAccess(rootR->right.get(), t+"C3");

        EulFunctionCallExp* rootRR2 = Assert::funcCall(rootRR->obj.get(), t+"C5");
        Assert::idToken(rootRR2->func.get(), "x", t + "C6");
        Assert::equals(1, rootRR2->params->size(), t + "C7");
        Assert::intToken(rootRR2->params->at(0).get(), 1, 32, false, t + "C8");
    }

    private: static void expStatementTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x=5; x=x*6; print(x);");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert first statement
        Assert::equals(3, file->statements->size(), t + "A1");
        EulStatement *stmt = Assert::statement(file->statements->operator[](0).get(), t + "A2");
        Assert::equals(EulStatementType::VAR_DECLARATION, stmt->getStatementType(), t + "A3");

        //3. Assert second statement: x=x*6;
        stmt = Assert::statement(file->statements->operator[](1).get(), t + "B1");
        Assert::equals(EulStatementType::EXPRESSION_STATEMENT, stmt->getStatementType(), t + "B2");
        Assert::infixExp( ((EulExpStatement*)stmt)->exp.get(), t + "B3");

        //4. Assert print instruction
        stmt = Assert::statement(file->statements->operator[](2).get(), t + "C1");
        Assert::equals(EulStatementType::EXPRESSION_STATEMENT, stmt->getStatementType(), t + "C2");
        Assert::funcCall( ((EulExpStatement*)stmt)->exp.get(), t + "C3");
    }


    private: static void returnStatementTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("return; return 1+x;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert first statement
        Assert::equals(2, file->statements->size(), t + "A1");
        ReturnStatement *stmt = Assert::returnStatement(file->statements->operator[](0).get(), t + "A2");
        Assert::null(stmt->exp.get(), t + "A3");

        //2. Assert second statement
        stmt = Assert::returnStatement(file->statements->operator[](1).get(), t + "B1");
        Assert::notNull(stmt->exp.get(), t + "B2");
        EulInfixExp* exp = Assert::infixExp(stmt->exp.get(), t + "B3");
        Assert::equals(&EUL_OPERATORS.plusOperator, exp->oper, t + "B4");
        Assert::intToken(exp->left.get(), 1, 32, false, t + "B5");
        Assert::idToken(exp->right.get(), "x", t + "B6");
    }



    public: static void runAll() {
        varDeclarationTest("EulParserTest.varDeclarationTest ");
        ltrSimpleExpressionTest("EulParserTest.ltrSimpleExpressionTest ");
        rtlSimpleExpressionTest("EulParserTest.rtlSimpleExpressionTest ");

        ltrMixedPrioritiesTest("EulParserTest.ltrMixedPrioritiesTest ");

        prefixExpTest("EulParserTest.prefixExpTest ");
        suffixExpTest("EulParserTest.suffixExpTest ");

        infixParenthesisTest("EulParserTest.infixParenthesisTest ");
        prefixParenthesisTest("EulParserTest.prefixParenthesisTest ");
        suffixParenthesisTest("EulParserTest.suffixParenthesisTest ");

        simpleFunctionCallTest("EulParserTest.simpleFunctionCallTest ");
        functionCallTest("EulParserTest.functionCallTest ");
        arrayAccessTest("EulParserTest.arrayAccessTest ");
        expStatementTest("EulParserTest.expStatementTest ");
        returnStatementTest("EulParserTest.returnStatementTest ");
    }
};

