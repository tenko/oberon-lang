/*
 * AST nodes representing unary and binary expressions in the Oberon LLVM compiler.
 *
 * Created by Michael Grossniklaus on 2/15/18.
 */

#ifndef OBERON0C_EXPRESSIONNODE_H
#define OBERON0C_EXPRESSIONNODE_H


#include "Node.h"
#include "TypeNode.h"
#include "BasicTypeNode.h"

enum class OperatorType : char {
    EQ, NEQ, LT, GT, GEQ, LEQ,
    TIMES, DIV, MOD, PLUS, MINUS,
    AND, OR, NOT,
    NEG
};

std::ostream& operator<<(std::ostream &stream, const OperatorType &op);

class ExpressionNode : public Node {

public:
    explicit ExpressionNode(const NodeType type, const FilePos &pos) : Node(type, pos) { };
    ~ExpressionNode() override = 0;

    [[nodiscard]] virtual bool isConstant() const = 0;
    [[nodiscard]] virtual TypeNode* getType() const = 0;

    void accept(NodeVisitor& visitor) override = 0;

};


class UnaryExpressionNode final : public ExpressionNode {

private:
    OperatorType op_;
    std::unique_ptr<ExpressionNode> expr_;

public:
    UnaryExpressionNode(const FilePos &pos, OperatorType op, std::unique_ptr<ExpressionNode> expr) :
            ExpressionNode(NodeType::unary_expression, pos), op_(op), expr_(std::move(expr)) { };
    ~UnaryExpressionNode() final = default;

    [[nodiscard]] bool isConstant() const final;
    [[nodiscard]] TypeNode* getType() const final;

    [[nodiscard]] OperatorType getOperator() const;

    void setExpression(std::unique_ptr<ExpressionNode> expr);
    [[nodiscard]] ExpressionNode* getExpression() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


class BinaryExpressionNode final : public ExpressionNode {

private:
    OperatorType op_;
    std::unique_ptr<ExpressionNode> lhs_, rhs_;

public:
    BinaryExpressionNode(const FilePos &pos, OperatorType op,
                         std::unique_ptr<ExpressionNode> lhs, std::unique_ptr<ExpressionNode> rhs) :
            ExpressionNode(NodeType::binary_expression, pos),
            op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) { };
    ~BinaryExpressionNode() final = default;

    [[nodiscard]] bool isConstant() const final;
    [[nodiscard]] TypeNode* getType() const final;

    [[nodiscard]] OperatorType getOperator() const;

    void setLeftExpression(std::unique_ptr<ExpressionNode> expr);
    [[nodiscard]] ExpressionNode* getLeftExpression() const;

    void setRightExpression(std::unique_ptr<ExpressionNode> expr);
    [[nodiscard]] ExpressionNode* getRightExpression() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


class LiteralNode : public ExpressionNode {

private:
    BasicTypeNode *type_;

public:
    explicit LiteralNode(const NodeType nodeType, const FilePos &pos, BasicTypeNode *type) :
            ExpressionNode(nodeType, pos), type_(type) { };
    ~LiteralNode() override = default;

    void accept(NodeVisitor& visitor) override = 0;

    [[nodiscard]] bool isConstant() const final;
    [[nodiscard]] BasicTypeNode* getType() const final;
};


class BooleanLiteralNode final : public LiteralNode {

private:
    bool value_;

public:
    explicit BooleanLiteralNode(const FilePos &pos, bool value) :
            LiteralNode(NodeType::boolean, pos, BasicTypeNode::BOOLEAN), value_(value) { };
    ~BooleanLiteralNode() final = default;

    [[nodiscard]] bool getValue() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


class IntegerLiteralNode final : public LiteralNode {

private:
    int value_;

public:
    explicit IntegerLiteralNode(const FilePos &pos, int value) :
            LiteralNode(NodeType::integer, pos, BasicTypeNode::INTEGER), value_(value) { };
    ~IntegerLiteralNode() final = default;

    [[nodiscard]] int getValue() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


class StringLiteralNode final : public LiteralNode {

private:
    std::string value_;

public:
    explicit StringLiteralNode(const FilePos &pos, std::string value) :
            LiteralNode(NodeType::string, pos, BasicTypeNode::STRING), value_(std::move(value)) { };
    ~StringLiteralNode() final = default;

    [[nodiscard]] std::string getValue() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


#endif //OBERON0C_EXPRESSIONNODE_H