/*
 * AST nodes representing declarations in the Oberon LLVM compiler.
 *
 * Created by Michael Grossniklaus on 3/7/18.
 */

#ifndef OBERON0C_DECLARATIONNODE_H
#define OBERON0C_DECLARATIONNODE_H


#include "Node.h"

#include <utility>
#include "TypeNode.h"
#include "ExpressionNode.h"

class TypeNode;

class DeclarationNode : public Node {

private:
    const std::string name_;
    TypeNode *type_;
    unsigned int level_;

public:
    explicit DeclarationNode(const NodeType nodeType, const FilePos &pos, std::string name, TypeNode *type) :
            Node(nodeType, pos), name_(std::move(name)), type_(type), level_() { };
    ~DeclarationNode() override = default;

    [[nodiscard]] std::string getName() const;

    void setType(TypeNode *type);
    [[nodiscard]] TypeNode * getType() const;

    void setLevel(unsigned int level);
    [[nodiscard]] unsigned int getLevel() const;

    void accept(NodeVisitor& visitor) override = 0;

    void print(std::ostream &stream) const override;

};


class ConstantDeclarationNode final : public DeclarationNode {

private:
    std::unique_ptr<ExpressionNode> value_;

public:
    explicit ConstantDeclarationNode(const FilePos &pos, std::string name, std::unique_ptr<ExpressionNode> value) :
            DeclarationNode(NodeType::constant, pos, std::move(name), nullptr),
            value_(std::move(value)) { };
    ~ConstantDeclarationNode() final = default;

    void setValue(std::unique_ptr<ExpressionNode> value);
    [[nodiscard]] ExpressionNode * getValue() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


class TypeDeclarationNode final : public DeclarationNode {

public:
    explicit TypeDeclarationNode(const FilePos &pos, std::string name, TypeNode *type) :
            DeclarationNode(NodeType::type_declaration, pos, std::move(name), type) { };
    ~TypeDeclarationNode() final = default;

    void accept(NodeVisitor& visitor) override;

    void print(std::ostream &stream) const final;

};


class VariableDeclarationNode final : public DeclarationNode {

public:
    explicit VariableDeclarationNode(const FilePos &pos, std::string name, TypeNode *type) :
            DeclarationNode(NodeType::variable, pos, std::move(name), type) { };
    ~VariableDeclarationNode() final = default;

    void accept(NodeVisitor& visitor) override;

};


class FieldNode final : public DeclarationNode {

public:
    explicit FieldNode(const FilePos &pos, std::string name, TypeNode *type) :
            DeclarationNode(NodeType::field, pos, std::move(name), type) { };
    ~FieldNode() final = default;

    void accept(NodeVisitor& visitor) override;

};


class ParameterNode final : public DeclarationNode {

private:
    bool var_;

public:
    explicit ParameterNode(const FilePos &pos, std::string name, TypeNode *type, bool var) :
            DeclarationNode(NodeType::parameter, pos, std::move(name), type), var_(var) { };
    ~ParameterNode() final = default;

    [[nodiscard]] bool isVar() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


#endif //OBERON0C_DECLARATIONNODE_H