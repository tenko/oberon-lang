/*
 * AST node representing a module in the Oberon LLVM compiler.
 *
 * Created by Michael Grossniklaus on 3/6/18.
 */

#ifndef OBERON0C_MODULENODE_H
#define OBERON0C_MODULENODE_H


#include <memory>
#include <string>
#include <vector>

#include "BlockNode.h"
#include "ImportNode.h"

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

class ModuleNode final : public DeclarationNode, public BlockNode {

private:
    std::string alias_;
    vector<unique_ptr<ImportNode>> imports_;

public:
    // ctor for use in sema / parser
    ModuleNode(const FilePos &pos,
               unique_ptr<Ident> name,
               vector<unique_ptr<ImportNode>> imports,
               vector<unique_ptr<ConstantDeclarationNode>> consts,
               vector<unique_ptr<TypeDeclarationNode>> types,
               vector<unique_ptr<VariableDeclarationNode>> vars,
               vector<unique_ptr<ProcedureNode>> procs,
               unique_ptr<StatementSequenceNode> stmts) :
            DeclarationNode(NodeType::module, pos, std::move(name), nullptr),
            BlockNode(std::move(consts), std::move(types), std::move(vars), std::move(procs), std::move(stmts)),
            alias_(), imports_(std::move(imports)) {};
    // ctor for use in symbol importer
    explicit ModuleNode(unique_ptr<Ident> name,
                        vector<unique_ptr<ConstantDeclarationNode>> consts,
                        vector<unique_ptr<TypeDeclarationNode>> types,
                        vector<unique_ptr<VariableDeclarationNode>> vars,
                        vector<unique_ptr<ProcedureNode>> procs) :
            DeclarationNode(NodeType::module, EMPTY_POS, std::move(name), nullptr),
            BlockNode(std::move(consts), std::move(types), std::move(vars), std::move(procs), make_unique<StatementSequenceNode>(EMPTY_POS)),
            alias_(), imports_() {};
    ~ModuleNode() override = default;

    [[nodiscard]] NodeType getNodeType() const override {
        return DeclarationNode::getNodeType();
    }

    void setAlias(string alias);
    [[nodiscard]] string getAlias() const;

    void addImport(unique_ptr<ImportNode> import);
    [[nodiscard]] ImportNode* getImport(size_t num) const;
    [[nodiscard]] size_t getImportCount() const;


    void accept(NodeVisitor& visitor) override;
    void print(std::ostream &stream) const override;

};


#endif //OBERON0C_MODULENODE_H
