#pragma once




class EulParserTest {

    private: static void varDeclarationTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. One var per declaration
        std::stringstream stream = std::stringstream("var x=5; var y; var z:UInt16=7; const z = 8;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();

        //2. Parse the source file
        Assert::equals(EulTokenType::AST, file->statements->operator[](0)->getType(), t + "A2");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](0))->getAstType(), t + "A3");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](0))->getStatementType(), t + "A4");
        Assert::equals(yy::EulParser::token::VAR, ((VarDeclarationStatement*)file->statements->operator[](0))->varType, t + "A5");
        Assert::equals(1, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->size(), t + "A6");
        Assert::equals("x", ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->id->name, t + "A7");
        Assert::equals(EulTokenType::INT, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A8");
        Assert::equals(5, ((EulIntToken*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->value, t + "A9");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->varType, t + "A10");

        Assert::equals(EulTokenType::AST, file->statements->operator[](1)->getType(), t + "B1");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](1))->getAstType(), t + "B2");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](1))->getStatementType(), t + "B3");
        Assert::equals(yy::EulParser::token::VAR, ((VarDeclarationStatement*)file->statements->operator[](1))->varType, t + "B4");
        Assert::equals(1, ((VarDeclarationStatement*)file->statements->operator[](1))->declarations->size(), t + "B5");
        Assert::equals("y", ((VarDeclarationStatement*)file->statements->operator[](1))->declarations->operator[](0)->id->name, t + "B6");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](1))->declarations->operator[](0)->value, t + "B7");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](1))->declarations->operator[](0)->varType, t + "B8");


        Assert::equals(EulTokenType::AST, file->statements->operator[](2)->getType(), t + "C1");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](2))->getAstType(), t + "C2");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](2))->getStatementType(), t + "C3");
        Assert::equals(yy::EulParser::token::VAR, ((VarDeclarationStatement*)file->statements->operator[](2))->varType, t + "C4");
        Assert::equals(1, ((VarDeclarationStatement*)file->statements->operator[](2))->declarations->size(), t + "C5");
        Assert::equals("z", ((VarDeclarationStatement*)file->statements->operator[](2))->declarations->operator[](0)->id->name, t + "C6");
        Assert::equals(EulTokenType::INT, ((VarDeclarationStatement*)file->statements->operator[](2))->declarations->operator[](0)->value->getType(), t + "C7");
        Assert::equals(7, ((EulIntToken*)((VarDeclarationStatement*)file->statements->operator[](2))->declarations->operator[](0)->value)->value, t + "C8");
        Assert::eulType(((VarDeclarationStatement*)file->statements->operator[](2))->declarations->operator[](0)->varType, "UInt16", t + "C9");


        Assert::equals(EulTokenType::AST, file->statements->operator[](3)->getType(), t + "D1");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](3))->getAstType(), t + "D2");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](3))->getStatementType(), t + "D3");
        Assert::equals(yy::EulParser::token::CONST, ((VarDeclarationStatement*)file->statements->operator[](3))->varType, t + "D4");
        Assert::equals(1, ((VarDeclarationStatement*)file->statements->operator[](3))->declarations->size(), t + "D5");
        Assert::equals("z", ((VarDeclarationStatement*)file->statements->operator[](3))->declarations->operator[](0)->id->name, t + "D6"); //duplicate var declaration!
        Assert::equals(EulTokenType::INT, ((VarDeclarationStatement*)file->statements->operator[](3))->declarations->operator[](0)->value->getType(), t + "D7");
        Assert::equals(8, ((EulIntToken*)((VarDeclarationStatement*)file->statements->operator[](3))->declarations->operator[](0)->value)->value, t + "D8");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](3))->declarations->operator[](0)->varType, t + "D9");


        //3. Parse the source file
        compiler.clearErrors();
        stream = std::stringstream("var x=\"hello\", y:String, z='\\n'; ");
        file = compiler.program.getSource("myFile2.eul", 1);
        ctx.sourceFile = file;
        scanner.switch_streams(&stream);
        parser.parse();

        //4. Check the result
        Assert::equals(EulTokenType::AST, file->statements->operator[](0)->getType(), t + "E1");
        Assert::equals(EulAstType::STATEMENT, ((EulAst*)file->statements->operator[](0))->getAstType(), t + "E2");
        Assert::equals(EulStatementType::VAR_DECLARATION, ((EulStatement*)file->statements->operator[](0))->getStatementType(), t + "E3");
        Assert::equals(yy::EulParser::token::VAR, ((VarDeclarationStatement*)file->statements->operator[](0))->varType, t + "E4");
        Assert::equals(3, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->size(), t + "E5");

        Assert::equals("x", ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->id->name, t + "E6");
        Assert::equals(EulTokenType::STRING, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "E7");
        Assert::equals("hello", ((EulStringToken*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->value, t + "E8");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->varType, t + "E9");

        Assert::equals("y", ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](1)->id->name, t + "F1");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](1)->value, t + "F2");
        Assert::eulType(((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](1)->varType, "String", t + "F3");


        Assert::equals("z", ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](2)->id->name, t + "G1");
        Assert::equals(EulTokenType::CHAR, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](2)->value->getType(), t + "G2");
        Assert::equals('\n', ((EulCharToken*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](2)->value)->value, t + "G3");
        Assert::null(((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](2)->varType, t + "G4");
    }


    private: static void ltrSimpleExpressionTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x=\"5\"+y-x-7;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* inExp = (EulInfixExp*)exp;
        Assert::intToken(inExp->right, 7, 4, false, t + "B1");
        Assert::equals(yy::EulParser::token::MINUS, inExp->operatorType, t + "B2");

        inExp = (EulInfixExp*)(inExp->left);
        Assert::idToken(inExp->right, "x", t + "C1");
        Assert::equals(yy::EulParser::token::MINUS, inExp->operatorType, t + "C2");

        inExp = (EulInfixExp*)(inExp->left);
        Assert::idToken(inExp->right, "y", t + "D1");
        Assert::equals(yy::EulParser::token::PLUS, inExp->operatorType, t + "D2");
        Assert::stringToken(inExp->left, "5", t + "D3");
    }

    private: static void rtlSimpleExpressionTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= \"5\" = y += x /= 7u1;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* inExp = (EulInfixExp*)exp;
        Assert::stringToken(inExp->left, "5", t + "B1");
        Assert::equals(yy::EulParser::token::ASSIGN, inExp->operatorType, t + "B2");

        inExp = (EulInfixExp*)(inExp->right);
        Assert::idToken(inExp->left, "y", t + "C1");
        Assert::equals(yy::EulParser::token::ASSIGN_PLUS, inExp->operatorType, t + "C2");

        inExp = (EulInfixExp*)(inExp->right);
        Assert::idToken(inExp->left, "x", t + "D1");
        Assert::equals(yy::EulParser::token::ASSIGN_DIV, inExp->operatorType, t + "D2");
        Assert::intToken(inExp->right, 7, 1, true, t + "D3");
    }

    private: static void ltrMixedPrioritiesTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= 1 || 4 == 5 + 8*10 - x.t.g * 5;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* inExp = (EulInfixExp*)exp;

        //3. Assert tree
        Assert::intToken(inExp->left, 1, 4, false, t + "B1");
        Assert::equals(yy::EulParser::token::OR, inExp->operatorType, t + "B2");

        inExp = (EulInfixExp*)(inExp->right);
        Assert::intToken(inExp->left, 4, 4, false, t + "C1");
        Assert::equals(yy::EulParser::token::EQUALS, inExp->operatorType, t + "C2");

        inExp = Assert::infixExp(inExp->right, t + "D1");
        EulInfixExp* currentSearching = inExp; //we back it up, so we return later to assert the right part of it.

        inExp = Assert::infixExp(inExp->left, t + "D2");
        Assert::equals(yy::EulParser::token::PLUS, inExp->operatorType, t + "D3");

        Assert::intToken(inExp->left, 5, 4, false, t + "D4");
        inExp = Assert::infixExp(inExp->right, t + "D5");
        Assert::intToken(inExp->left, 8, 4, false, t + "D7");
        Assert::equals(yy::EulParser::token::STAR, inExp->operatorType, t + "D6");
        Assert::intToken(inExp->right, 10, 4, false, t + "D8");

        Assert::equals(yy::EulParser::token::MINUS, currentSearching->operatorType, t + "E1");
        inExp = Assert::infixExp(currentSearching->right, t + "E2");

        currentSearching = inExp; //save it for checking its right part later
        inExp = Assert::infixExp(currentSearching->left, t + "E2");
        inExp = Assert::infixExp(inExp->left, t + "E3");

        Assert::idToken(inExp->left, "x", t + "F1");
        Assert::equals(yy::EulParser::token::DOT, inExp->operatorType, t + "F2");
        Assert::idToken(inExp->right, "t", t + "F3");

        inExp = Assert::infixExp(currentSearching->left, t + "G1");
        Assert::equals(yy::EulParser::token::DOT, inExp->operatorType, t + "G3");
        Assert::idToken(inExp->right, "g", t + "G3");

        inExp = currentSearching;
        Assert::equals(yy::EulParser::token::STAR, inExp->operatorType, t + "H1");
        Assert::intToken(inExp->right, 5, 4, false, t + "H2");
    }

    private: static void prefixExpTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= x * -y + ~++z;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* level1 = (EulInfixExp*)exp; //save it for lated checks on its right side
        Assert::equals(yy::EulParser::token::PLUS, level1->operatorType, t + "C4");

        EulInfixExp* currentInf = Assert::infixExp(level1->left, t + "B1");
        Assert::idToken(currentInf->left, "x", t + "B2");
        Assert::equals(yy::EulParser::token::STAR, currentInf->operatorType, t + "B3");

        EulPrefixExp* currentPref = Assert::prefixExp(currentInf->right, t + "C1");
        Assert::equals(yy::EulParser::token::MINUS, currentPref->operatorType, t + "C2");
        Assert::idToken(currentPref->exp, "y", t + "C3");

        currentPref = Assert::prefixExp(level1->right, t + "D1");
        Assert::equals(yy::EulParser::token::TILDE, currentPref->operatorType, t + "D2");
        currentPref = Assert::prefixExp(currentPref->exp, t + "D3");
        Assert::equals(yy::EulParser::token::INCREASE, currentPref->operatorType, t + "D4");
        Assert::idToken(currentPref->exp, "z", t + "D5");
    }



    private: static void suffixExpTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= x * y-- + z++;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");

        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* level1 = (EulInfixExp*)exp; //save it for later checks on its right side
        EulInfixExp* currentInf = Assert::infixExp(level1->left, t + "B1");
        Assert::idToken(currentInf->left, "x", t + "B2");
        Assert::equals(yy::EulParser::token::STAR, currentInf->operatorType, t + "B3");
        EulSuffixExp* currentPref = Assert::suffixExp(currentInf->right, t + "C1");

        Assert::equals(yy::EulParser::token::DECREASE, currentPref->operatorType, t + "C2");
        Assert::idToken(currentPref->exp, "y", t + "C3");
        Assert::equals(yy::EulParser::token::PLUS, level1->operatorType, t + "C4");


        currentPref = Assert::suffixExp(level1->right, t + "D1");
        Assert::equals(yy::EulParser::token::INCREASE, currentPref->operatorType, t + "D2");
        Assert::idToken(currentPref->exp, "z", t + "D3");
    }

    private: static void infixParenthesisTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= x*(y+1);");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* infixExp = (EulInfixExp*)exp; //save it for later checks on its right side
        Assert::idToken(infixExp->left, "x", t + "B1");
        Assert::equals(yy::EulParser::token::STAR, infixExp->operatorType, t + "B2");
        infixExp = Assert::infixExp(infixExp->right, t + "B3");

        Assert::idToken(infixExp->left, "y", t + "C1");
        Assert::equals(yy::EulParser::token::PLUS, infixExp->operatorType, t + "C2");
        Assert::intToken(infixExp->right, 1, 4, false, t + "C3");
    }

    private: static void prefixParenthesisTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= --(x+y);");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::PREFIX_EXP, exp->getExpressionType(), t + "A3");

        EulPrefixExp* topLevel = (EulPrefixExp*)exp; //save it for later checks on its right side
        Assert::equals(yy::EulParser::token::DECREASE, topLevel->operatorType, t + "B2");
        EulInfixExp* infixExp = Assert::infixExp(topLevel->exp, t + "B3");

        Assert::idToken(infixExp->left, "x", t + "C1");
        Assert::equals(yy::EulParser::token::PLUS, infixExp->operatorType, t + "C2");
        Assert::idToken(infixExp->right, "y", t + "C3");
    }



    private: static void suffixParenthesisTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= (x+y)++;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::SUFFIX_EXP, exp->getExpressionType(), t + "A3");

        EulSuffixExp* topLevel = (EulSuffixExp*)exp; //save it for later checks on its right side
        Assert::equals(yy::EulParser::token::INCREASE, topLevel->operatorType, t + "B2");
        EulInfixExp* infixExp = Assert::infixExp(topLevel->exp, t + "B3");

        Assert::idToken(infixExp->left, "x", t + "C1");
        Assert::equals(yy::EulParser::token::PLUS, infixExp->operatorType, t + "C2");
        Assert::idToken(infixExp->right, "y", t + "C3");
    }

    private: static void simpleFunctionCallTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= y();");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::FUNCTION_CALL, exp->getExpressionType(), t + "A3");

        EulFunctionCallExp* funcCall = (EulFunctionCallExp*)exp; //save it for later checks on its right side
        Assert::idToken(funcCall->func, "y", t + "B1");
        Assert::null(funcCall->params, t + "B2");
    }

    private: static void functionCallTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= a.b(5, f(6u)) - 3*x(1)();");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* root = (EulInfixExp*)exp; //save it for later checks on its right side

        Assert::equals(yy::EulParser::token::MINUS, root->operatorType, t + "B1");
        EulInfixExp* rootL = Assert::infixExp(root->left, t+"B2");
        Assert::equals(yy::EulParser::token::DOT, rootL->operatorType, t + "B3");
        Assert::idToken(rootL->left, "a", t + "B3");

        EulFunctionCallExp* rootLR = Assert::funcCall(rootL->right, t+"B4");
        Assert::idToken(rootLR->func, "b", t + "B5");
        Assert::equals(2, rootLR->params->size(), t + "B6");
        Assert::intToken(rootLR->params->at(0), 5, 4, false, t + "B7");

        EulFunctionCallExp* rootLR2 = Assert::funcCall(rootLR->params->at(1), t+"B8");
        Assert::idToken(rootLR2->func, "f", t + "B9");
        Assert::equals(1, rootLR2->params->size(), t + "B10");
        Assert::intToken(rootLR2->params->at(0), 6, 4, true, t + "B11");

        //Test right part: 3*x(1)(2)
        EulInfixExp* rootR = Assert::infixExp(root->right, t+"C1");
        Assert::intToken(rootR->left, 3, 4, false, t+"C2");
        EulFunctionCallExp* rootRR = Assert::funcCall(rootR->right, t+"C3");
        Assert::null(rootRR->params, t + "C4");

        EulFunctionCallExp* rootRR2 = Assert::funcCall(rootRR->func, t+"C5");
        Assert::idToken(rootRR2->func, "x", t + "C6");
        Assert::equals(1, rootRR2->params->size(), t + "C7");
        Assert::intToken(rootRR2->params->at(0), 1, 4, false, t + "C8");
    }


    private: static void arrayAccessTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x= a.b[5] - 3*x(1)[y];");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert expression tree
        Assert::equals(EulTokenType::AST, ((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value->getType(), t + "A1");
        Assert::equals(EulAstType::EXPRESSION, ((EulAst*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value)->getAstType(), t + "A2");
        EulExpression *exp = (EulExpression*)((VarDeclarationStatement*)file->statements->operator[](0))->declarations->operator[](0)->value;
        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), t + "A3");

        EulInfixExp* root = (EulInfixExp*)exp; //save it for later checks on its right side

        Assert::equals(yy::EulParser::token::MINUS, root->operatorType, t + "B1");
        EulInfixExp* rootL = Assert::infixExp(root->left, t+"B2");
        Assert::equals(yy::EulParser::token::DOT, rootL->operatorType, t + "B3");
        Assert::idToken(rootL->left, "a", t + "B3");

        EulArrayAccessExp* rootLR = Assert::arrayAccess(rootL->right, t+"B4");
        Assert::idToken(rootLR->obj, "b", t + "B5");
        Assert::intToken(rootLR->index, 5, 4, false, t + "B7");

        //Test right part: 3*x(1)[y]
        EulInfixExp* rootR = Assert::infixExp(root->right, t+"C1");
        Assert::intToken(rootR->left, 3, 4, false, t+"C2");
        EulArrayAccessExp* rootRR = Assert::arrayAccess(rootR->right, t+"C3");

        EulFunctionCallExp* rootRR2 = Assert::funcCall(rootRR->obj, t+"C5");
        Assert::idToken(rootRR2->func, "x", t + "C6");
        Assert::equals(1, rootRR2->params->size(), t + "C7");
        Assert::intToken(rootRR2->params->at(0), 1, 4, false, t + "C8");
    }

    private: static void expStatementTest(const std::string& t) {
        Compiler compiler(0);
        EulSourceFile *file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file);

        //1. Equal priority, ltr expressions
        std::stringstream stream = std::stringstream("var x=5; x=x*6; print(x);");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();


        //2. Assert first statement
        Assert::equals(3, file->statements->size(), t + "A1");
        EulStatement *stmt = Assert::statement(file->statements->operator[](0), t + "A2");
        Assert::equals(EulStatementType::VAR_DECLARATION, stmt->getStatementType(), t + "A3");

        //3. Assert second statement: x=x*6;
        stmt = Assert::statement(file->statements->operator[](1), t + "B1");
        Assert::equals(EulStatementType::EXPRESSION_STATEMENT, stmt->getStatementType(), t + "B2");
        Assert::infixExp( ((EulExpStatement*)stmt)->exp, t + "B3");

        //4. Assert print instruction
        stmt = Assert::statement(file->statements->operator[](2), t + "C1");
        Assert::equals(EulStatementType::EXPRESSION_STATEMENT, stmt->getStatementType(), t + "C2");
        Assert::funcCall( ((EulExpStatement*)stmt)->exp, t + "C3");
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
    }
};

