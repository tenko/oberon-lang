//
// Created by Michael Grossniklaus on 10/23/22.
//

#ifndef OBERON_LANG_PREDEFINEDPROCEDURE_H
#define OBERON_LANG_PREDEFINEDPROCEDURE_H


#include <llvm/IR/IRBuilder.h>
#include "OberonSystem.h"

using namespace llvm;

class PredefinedProcedure : public ProcedureNode {

protected:
    void setSignature(std::vector<std::pair<TypeNode*, bool>> params, TypeNode *ret);

public:
    explicit PredefinedProcedure(std::string name) : ProcedureNode(EMPTY_POS, std::make_unique<Ident>(name)) {};
    ~PredefinedProcedure() override;

    virtual void setup(OberonSystem *system) = 0;
    [[nodiscard]] virtual Value *call(IRBuilder<> *builder, Module *module, std::vector<Value *> params) = 0;

    [[nodiscard]] bool isPredefined() const override {
        return true;
    }

};


class New final : public PredefinedProcedure {

public:
    explicit New() : PredefinedProcedure(NAME) {};
    ~New() override = default;

    void setup(OberonSystem *system) override;
    Value *call(IRBuilder<> *builder, Module *module, std::vector<Value *> params) override;

    static const std::string NAME;

};


#endif //OBERON_LANG_PREDEFINEDPROCEDURE_H
