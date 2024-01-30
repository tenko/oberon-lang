//
// Created by Michael Grossniklaus on 1/28/24.
//

#include "ASTContext.h"
#include <memory>

using std::make_unique;

Node *ASTContext::getTranslationUnit() {
    return unit_.get();
}

void ASTContext::setTranslationUnit(unique_ptr<Node> unit) {
    unit_ = std::move(unit);
}

ArrayTypeNode *ASTContext::getOrInsertArrayType(Ident *ident, unsigned int dimension, TypeNode *memberType) {
    for (auto &type : array_ts_) {
        if (type->getMemberType() == memberType && type->getDimension() == dimension) {
            return type.get();
        }
    }
    auto type = make_unique<ArrayTypeNode>(ident, dimension, memberType);
    auto res = type.get();
    array_ts_.push_back(std::move(type));
    return res;
}

RecordTypeNode *ASTContext::getOrInsertRecordType(Ident *ident, vector<unique_ptr<FieldNode>> fields) {
    auto type = make_unique<RecordTypeNode>(ident, std::move(fields));
    auto res = type.get();
    record_ts_.push_back(std::move(type));
    return res;
}

PointerTypeNode *ASTContext::getOrInsertPointerType(Ident *ident, TypeNode *base) {
    auto type = make_unique<PointerTypeNode>(ident, base);
    auto res = type.get();
    pointer_ts_.push_back(std::move(type));
    return res;
}

ProcedureTypeNode *ASTContext::getOrInsertProcedureNode(Ident *ident, vector<unique_ptr<ParameterNode>> params, TypeNode *ret) {
    auto type = make_unique<ProcedureTypeNode>(ident, std::move(params), ret);
    auto res = type.get();
    procedure_ts.push_back(std::move(type));
    return res;
}

TypeReferenceNode *ASTContext::getOrInsertTypeReference(unique_ptr<QualIdent> ident) {
    auto ref = make_unique<TypeReferenceNode>(EMPTY_POS, std::move(ident));
    auto res = ref.get();
    references_.push_back(std::move(ref));
    return res;
}