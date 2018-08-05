//INCLUDE INTERNAL IMPLEMENTATIONS
#pragma once
#include "./EulError/EulError.impl.h"




//region LIFE CYCLE
Compiler::Compiler(void (*onError)(Compiler* ths)) {
    this->onError = onError;
    this->currentSource = nullptr;
}

Compiler::~Compiler() {
    this->clearErrors();
}


void Compiler::reset() {
    //reset variables
    this->buffer.clear();
    this->currentSource = 0;

    //clear errors
    this->clearErrors();

    //reset program
    this->program.reset();
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
    EulParsingContext ctx(this, target);
    EulScanner scanner(input);
    yy::EulParser parser(scanner, &ctx);

    //3. Parse the source files
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
    //1. Setup llvm engine.
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    llvm::LLVMContext llvmCtx;
    llvm::Module globalModule("entryPointModule", llvmCtx);

    EulCodeGenContext ctx(this, llvmCtx, &globalModule, nullptr);

    //2. Setup entry point and main function
    auto sources = this->program.sources;
    EulSourceFile* entryPoint = this->program.getEntryPoint();
    this->program.declareClibSymbols(&ctx);
    this->program.makeEntryPoint(&ctx);
    this->program.makeMain(&ctx);


    //3. Pre parse
    for (auto const& source : sources) source.second->doASTPreParsing(&ctx);

    //4. Parse and omit the code
    for (auto const& source : sources) source.second->parseAST(&ctx);

    //5. Add return statement, just in case none was created already.
    auto zero = llvm::ConstantInt::get(llvm::IntegerType::get(llvmCtx, 32), 0, true);
    ctx.builder.CreateRet(zero);

    //6. Perform the llvm spells.
    this->program.emmitIRAssembly(&ctx, outputFileName+"_IR");
    this->program.emmitObjCode(&ctx, outputFileName);


    //dummyModule->getOrInsertGlobal("myGlob", llvm::Type::getInt64Ty(context));
    //dummyModule->getOrInsertGlobal("myGlob2", llvm::Type::getInt32Ty(context));
}
//endregion