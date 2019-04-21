#pragma once



class EulWhileStatementParsingTest {

    public: static void parseWhileTest(const std::string& t) {
        Compiler compiler(0);
        auto file = compiler.program.getSource("myFile1.eul", 1);
        EulParsingContext ctx(&compiler, file.get());

        //1. Simple while case
        std::stringstream stream = std::stringstream(" var v1; while isTrue { var v2; return v2; } var v1b;");
        EulScanner scanner(&stream);
        yy::EulParser parser(scanner, &ctx);
        parser.parse();

        //2. Assert AST
        Assert::equals(3, file->statements->size(), t + "A1 statement count");
        Assert::varDeclarationStatement(file->statements->at(0).get(), t + "A2 pre-while statement");
        Assert::varDeclarationStatement(file->statements->at(2).get(), t + "A3 post-while statement");
        auto asWhileStmt = Assert::whileStatement(file->statements->at(1).get(), t + "A4 is while statement");
        Assert::idToken(asWhileStmt->expBlock.expression.get(), "isTrue", t + "A5 condition");
        Assert::equals(2, asWhileStmt->expBlock.block->statements->size(), t + "A6 statement count");
        Assert::varDeclarationStatement(asWhileStmt->expBlock.block->statements->at(0).get(), t + "A7 nested statement1");
        auto asRetStmt = Assert::returnStatement(asWhileStmt->expBlock.block->statements->at(1).get(), t + "A8 nested statement2");

        //3. Assert scopes
        Assert::notNull(asWhileStmt->expBlock.block->scope.get(), t + "B1 scope not null");
        Assert::equals(file->scope.get(), asWhileStmt->expBlock.block->scope->superScope.get(), t + "B2 a new scope is created, and has the proper super scope");
        Assert::notNull(file->scope->getOwnSymbol("v1").get(), t+"B3");
        Assert::notNull(file->scope->getOwnSymbol("v1b").get(), t+"B4");
        Assert::notNull(asWhileStmt->expBlock.block->scope->getOwnSymbol("v2").get(), t+"B5 var is declared on while-scope");
        Assert::null(asWhileStmt->expBlock.block->scope->getOwnSymbol("v1").get(), t+"B6 parent scope is not the while scope");
        Assert::null(asWhileStmt->expBlock.block->scope->getOwnSymbol("v1b").get(), t+"B7 parent scope is not the while scope");
        Assert::null(file->scope->getOwnSymbol("v2").get(), t+"B8 var inside while is not on parent scope");

        auto asId = Assert::idToken(asRetStmt->exp.get(), "v2", t+"B9");
        Assert::equals(asWhileStmt->expBlock.block->scope.get(), asId->scope.get(), t+"B10 id inside the while-scope uses the while-scope");
    }


    public: static void runAll() {
        parseWhileTest("EulWhileStatementParsingTest.parseWhileTest ");
    }
};
