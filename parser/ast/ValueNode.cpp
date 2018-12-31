/*
 * Implementation of the AST constant nodes used by the Oberon-0 compiler.
 *
 * Created by Michael Grossniklaus on 2/19/18.
 */


#include "ValueNode.h"

ValueNode::ValueNode(const NodeType nodeType, const FilePos pos, BasicTypeNode *type) :
        ExpressionNode(nodeType, pos), type_(type) {
}

ValueNode::~ValueNode() = default;

bool ValueNode::isConstant() const {
    return true;
}

BasicTypeNode* ValueNode::getType() const {
    return type_;
}
