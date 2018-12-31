/*
 * Header file of the AST parameter declaration nodes used by the Oberon-0 compiler.
 *
 * Created by Michael Grossniklaus on 3/5/18.
 */

#ifndef OBERON0C_PARAMETERNODE_H
#define OBERON0C_PARAMETERNODE_H


#include <memory>
#include <string>
#include "NamedValueNode.h"
#include "TypeNode.h"

class ParameterNode final : public NamedValueNode {

private:
    bool var_;

public:
    explicit ParameterNode(FilePos pos, const std::string &name, TypeNode *type, bool var);
    ~ParameterNode() final;

    bool isVar() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


#endif //OBERON0C_PARAMETERNODE_H
