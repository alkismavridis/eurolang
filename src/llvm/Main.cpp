#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

using namespace llvm;



//region UTILS
void makeMain(Module* module, IRBuilder<>* builder) {
    //1. Setup function
    Function* mainFunc = (Function*)module->getOrInsertFunction ("main", IntegerType::get(module->getContext(), 32), NULL);
    BasicBlock *block = BasicBlock::Create(module->getContext(), "entry", mainFunc);
    builder->SetInsertPoint(block);

    //2. add the commands
    builder->CreateRet(
        ConstantInt::get(IntegerType::get(module->getContext(), 32), 42, true)
    );
}



void emmitObjCode(Module* module) {
    auto TargetTriple = sys::getDefaultTargetTriple();

    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target) {
      errs() << Error;
      return;
    }


    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    module->setDataLayout(TargetMachine->createDataLayout());
    module->setTargetTriple(TargetTriple);



    auto Filename = "output.o";
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC, sys::fs::F_None);

    if (EC) {
      errs() << "Could not open file: " << EC.message();
      return;
    }

    legacy::PassManager pass;
    auto FileType = TargetMachine::CodeGenFileType::CGFT_ObjectFile;

    if (TargetMachine->addPassesToEmitFile(pass, dest, FileType)) {
      errs() << "TargetMachine can't emit a file of this type";
      return;
    }

    pass.run(*module);
    dest.flush();
}

void omitIRAssembly(Module* module) {
    std::error_code code;
    raw_fd_ostream out("./testOut.txt", code, sys::fs::OpenFlags::F_None);
    module->print(out, nullptr);
}
//endregion



int main() {
    static LLVMContext context;
    static std::unique_ptr<Module> dummyModule;
    static IRBuilder<> builder(context);


    // Make the module, which holds all the code.
    dummyModule = llvm::make_unique<Module>("main22", context);

    //TODO dummy
    makeMain(dummyModule.get(), &builder);
    dummyModule->getOrInsertGlobal("myGlob", Type::getInt64Ty(context));
    dummyModule->getOrInsertGlobal("myGlob2", Type::getInt32Ty(context));

    // Print out all of the generated code.
    emmitObjCode(dummyModule.get());
    //omitIRAssembly(dummyModule.get());

    return 0;
}