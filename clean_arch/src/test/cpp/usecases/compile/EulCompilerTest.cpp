#include <functional>
#include <list>

#include "model/error/EulException.h"
#include "usecases/compile/AstProvider.h"
#include "usecases/compile/CodeGenerator.h"
#include "usecases/compile/CompileOptions.h"
#include "usecases/compile/EulCompiler.h"
#include "model/error/EulLogger.h"

#include "test_utils/Assert.h"
#include "EulCompilerTest.h"


using namespace std;


//SECTIONS UTILS
AstProvider getDummyAstProvider(string* paramCapturer, bool* calledFlag, bool logsError, bool throwsError) {
    return [=](const string& fileName, EulLogger* log) -> unique_ptr<const AstRoot> {
        if (calledFlag != nullptr) {
            *calledFlag = true;
        }

        if (paramCapturer != nullptr) {
            *paramCapturer = fileName;
        }

        if (throwsError) {
            throw EulException("DummyException", "AST provider fatal error", AstLocation(1,2));
        }

        if(logsError) {
            log->error(EulException("DummyException", "AST provider error", AstLocation(1,2)));
        }

        return nullptr;
    };
}

CodeGenerator getDummyCodeGenerator(bool* calledFlag, bool logsError, bool throwsError) {
    return [=](const AstRoot* ast, const AstMetadata* astMetadata, EulLogger* log) -> void {
        if (calledFlag != nullptr) {
            *calledFlag = true;
        }

        if (throwsError) {
            throw EulException("DummyError", "CodeGen fatal error", AstLocation(1,2));
        }

        if(logsError) {
            log->error(EulException("DummyException", "CodeGen error", AstLocation(1,2)));
        }
    };
}

struct TestLogger : public EulLogger {
    list<const string> errorMessages;

    void error(const EulException& ex) {
        errorMessages.push_back(ex.message);
    }

    bool hasErrors() {
        return !errorMessages.empty();
    }
};

CompileOptions makeDummyOptions() {
    return CompileOptions("MyFile.eul");
}



//SECTION TESTS
void compileShouldCallAstProviderWithProperArguments(UnitTest* t) {
    bool astProviderCalled = false;
    string fileName = "";

    CompileOptions options = makeDummyOptions();
    AstProvider prov = getDummyAstProvider(&fileName, &astProviderCalled, false, false);
    CodeGenerator codeGen = getDummyCodeGenerator(nullptr, false, false);
    TestLogger log;

    EulCompiler compiler(&options, prov, codeGen, &log);
    compiler.compile();

    Assert::that(astProviderCalled, t, "1");
    Assert::equals(fileName, "MyFile.eul", t, "2");
}

void compileShouldStopOnAstProviderFatalError(UnitTest* t) {
    bool astProviderCalled = false;
    bool codeGenCalled = false;

    CompileOptions options = makeDummyOptions();
    AstProvider prov = getDummyAstProvider(nullptr, &astProviderCalled, false, true);
    CodeGenerator codeGen = getDummyCodeGenerator(&codeGenCalled, false, false);
    TestLogger log;


    EulCompiler compiler(&options, prov, codeGen, &log);
    compiler.compile();

    Assert::that(astProviderCalled, t, "1");
    Assert::thatNot(codeGenCalled, t, "2");
    Assert::equals(1, log.errorMessages.size(), t, "3");
    Assert::equals("AST provider fatal error", log.errorMessages.front(), t, "4");
}

void compileShouldStopOnAstProviderRegularError(UnitTest* t) {
    bool astProviderCalled = false;
    bool codeGenCalled = false;

    CompileOptions options = makeDummyOptions();
    AstProvider prov = getDummyAstProvider(nullptr, &astProviderCalled, true, false);
    CodeGenerator codeGen = getDummyCodeGenerator(&codeGenCalled, false, false);
    TestLogger log;


    EulCompiler compiler(&options, prov, codeGen, &log);
    compiler.compile();

    Assert::that(astProviderCalled, t, "1");
    Assert::thatNot(codeGenCalled, t, "2");
    Assert::equals(1, log.errorMessages.size(), t, "3");
    Assert::equals("AST provider error", log.errorMessages.front(), t, "4");
}

void compileShouldLogCodeGenFatalError(UnitTest* t) {
    bool codeGenCalled = false;

    CompileOptions options = makeDummyOptions();
    AstProvider prov = getDummyAstProvider(nullptr, nullptr, false, false);
    CodeGenerator codeGen = getDummyCodeGenerator(&codeGenCalled, false, true);
    TestLogger log;


    EulCompiler compiler(&options, prov, codeGen, &log);
    compiler.compile();

    Assert::that(codeGenCalled, t, "codeGenWasCalled");
    Assert::equals(1, log.errorMessages.size(), t, "hasOneError");
    Assert::equals("CodeGen fatal error", log.errorMessages.front(), t, "mes");
}

void compileShouldLogCodeGenRegularError(UnitTest* t) {
    bool codeGenCalled = false;

    CompileOptions options = makeDummyOptions();
    AstProvider prov = getDummyAstProvider(nullptr, nullptr, false, false);
    CodeGenerator codeGen = getDummyCodeGenerator(&codeGenCalled, true, false);
    TestLogger log;


    EulCompiler compiler(&options, prov, codeGen, &log);
    compiler.compile();

    Assert::that(codeGenCalled, t, "codeGenWasCalled");
    Assert::equals(1, log.errorMessages.size(), t, "hasOneError");
    Assert::equals("CodeGen error", log.errorMessages.front(), t, "mes");
}

void EulCompilerTest::runAll() {
    this
        ->logStart()
        ->run("compileShouldCallAstProviderWithProperArguments", compileShouldCallAstProviderWithProperArguments)
        ->run("compileShouldStopOnAstProviderFatalError", compileShouldStopOnAstProviderFatalError)
        ->run("compileShouldStopOnAstProviderRegularError", compileShouldStopOnAstProviderRegularError)
        ->run("compileShouldLogCodeGenFatalError", compileShouldLogCodeGenFatalError)
        ->run("compileShouldLogCodeGenRegularError", compileShouldLogCodeGenRegularError)
        ->todo("What if Analyzer produces fatal error?")
        ->todo("What if Analyzer produces regular error?")
        ;
}
