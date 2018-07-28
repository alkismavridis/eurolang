//INCLUDE INTERNAL IMPLEMENTATIONS
#pragma once
#include "./EulError/EulError.impl.h"




//region LIFE CYCLE
Compiler::Compiler(void (*onError)(Compiler* ths)) {
    this->onError = onError;
    this->currentSource = nullptr;
    this->codeGen = new EulCodeGenContext(this->program.llvmContext, this->program.globalModule);
}

Compiler::~Compiler() {
    this->clearErrors();
    delete this->codeGen;
}


void Compiler::reset() {
    //reset variables
    this->buffer.clear();
    this->currentSource = 0;

    //clear errors
    this->clearErrors();

    //reset program
    this->program.reset();

    delete this->codeGen;
    this->codeGen = new EulCodeGenContext(this->program.llvmContext, this->program.globalModule);
}
//endregion




//region API
/**
    This assumes that target is one of this.program.sources elements.
    input is the actual file.
    This function does NOT check the existence of the file. This should be done
    by the caller function.
*/
void Compiler::compile(EulSourceFile *target, std::istream *input) {
    //1. Update currentSource
    this->currentSource = target;

    //2. Setup a scanner and a parser
    EulParsingContext ctx(this, this->codeGen, target);
    EulScanner scanner(input);
    yy::EulParser parser(scanner, &ctx);

    //3. Parse the source file
    parser.parse();

    //4. Done. mark the file as Parsed
    this->currentSource->isParsed = 1;
}

/**
    Convenience method. Accepts a file name instead of an EulSourceFile.
    Has the same effect as its counterpart compile(EulSourceFile *target, std::istream *input).
*/
void Compiler::compile(const std::string& sourceName, std::istream *input) {
    EulSourceFile* sourceFile = this->program.getSource(sourceName, true);
    this->compile(sourceFile, input);
}
//endregion




//region ERROR RELATED ACTIONS
void Compiler::addError(const EulError& error) {
    this->errors.push_back(new EulError(error.type, error.message));
    if (this->onError != 0) this->onError(this);
}


void Compiler::addError(int errorType, const std::string& message) {
    this->errors.push_back(new EulError(errorType, message));
    if (this->onError != 0) this->onError(this);
}

void Compiler::clearErrors() {
  for (auto const& e : this->errors) delete e;
  this->errors.clear();
}
//endregion




//region EMMITING OUTPUT
void Compiler::produceOutput(const std::string& outputFileName) {
    auto sources = this->program.sources;


    //1. Setup entry point and main function
    EulSourceFile* entryPoint = this->program.getEntryPoint();
    this->program.makeMain(this->program.globalModule, &this->codeGen->builder);


    //1. Pre parse
    for (auto const& source : sources) source.second->doASTPreParsing(this->codeGen);

    //2. Parse and omit the code
    for (auto const& source : sources) source.second->parseAST(this->codeGen);

    //3. Add return statement, just in case none was created already.
    auto zero = llvm::ConstantInt::get(llvm::IntegerType::get(*this->program.llvmContext, 32), 0, true);
    this->codeGen->builder.CreateRet(zero);

    //4. Prform the llvm spells.
    this->program.emmitIRAssembly(this->program.globalModule, outputFileName+"_IR");
    this->program.emmitObjCode(this->program.globalModule, outputFileName);


    //dummyModule->getOrInsertGlobal("myGlob", llvm::Type::getInt64Ty(context));
    //dummyModule->getOrInsertGlobal("myGlob2", llvm::Type::getInt32Ty(context));
}
//endregion