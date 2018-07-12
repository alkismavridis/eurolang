//INCLUDE INTERNAL IMPLEMENTATIONS
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
