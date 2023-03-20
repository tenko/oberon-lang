/*
 * Implementation of a simple compiler based on the LLVM compiler infrastructure.
 *
 * Created by Michael Grossniklaus on 2/29/20.
 */

#ifndef OBERON_LANG_LLVMCODEGEN_H
#define OBERON_LANG_LLVMCODEGEN_H


#include <boost/filesystem.hpp>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Target/TargetMachine.h>
#include "analyzer/Analyzer.h"
#include "codegen/CodeGen.h"
#include "logging/Logger.h"

using namespace llvm;

class LLVMCodeGen final : public CodeGen {

private:
    Logger *logger_;
    OutputFileType type_;
    LLVMContext ctx_;
    PassBuilder pb_;
    llvm::OptimizationLevel lvl_;
    TargetMachine *tm_;

    void emit(Module *module, boost::filesystem::path path, OutputFileType type);

public:
    explicit LLVMCodeGen(Logger *logger);
    ~LLVMCodeGen() override = default;

    std::string getDescription() final;

    void configure(CompilerFlags *flags) final;

    void generate(Node *ast, boost::filesystem::path path) final;

};


#endif //OBERON_LANG_LLVMCODEGEN_H
