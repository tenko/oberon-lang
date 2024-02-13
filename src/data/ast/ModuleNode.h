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

class ModuleNode final : public BlockNode {

private:
    std::string alias_;
    vector<unique_ptr<ImportNode>> imports_;

public:
    // ctor for use in sema / parser
    ModuleNode(const FilePos &pos, unique_ptr<Ident> name, vector<unique_ptr<ImportNode>> imports) :
            BlockNode(NodeType::module, pos, make_unique<IdentDef>(name->start(), name->end(), name->name()), nullptr),
            alias_(), imports_(std::move(imports)) {};
    // ctor for use in symbol importer
    explicit ModuleNode(unique_ptr<Ident> name) :
            BlockNode(NodeType::module, EMPTY_POS, make_unique<IdentDef>(name->start(), name->end(), name->name()), nullptr),
            alias_(), imports_() {};
    ~ModuleNode() override = default;

    void setAlias(string alias);
    [[nodiscard]] string getAlias() const;

    void addImport(unique_ptr<ImportNode> import);
    [[nodiscard]] ImportNode* getImport(size_t num) const;
    [[nodiscard]] size_t getImportCount() const;


    void accept(NodeVisitor& visitor) override;
    void print(std::ostream &stream) const override;

};


#endif //OBERON0C_MODULENODE_H
