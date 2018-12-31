/*
 * Header file of the AST array type nodes used by the Oberon-0 compiler.
 *
 * Created by Michael Grossniklaus on 2/9/18.
 */

#ifndef OBERON0C_ARRAYTYPESYMBOL_H
#define OBERON0C_ARRAYTYPESYMBOL_H


#include <memory>
#include "TypeNode.h"

class ArrayTypeNode final : public TypeNode {

private:
    const int dim_;
    TypeNode* memberType_;

public:
    explicit ArrayTypeNode(FilePos pos, int dim, TypeNode* memberType);
    ~ArrayTypeNode() final;

    int getDimension() const;
    TypeNode* getMemberType() const;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


#endif //OBERON0C_ARRAYTYPESYMBOL_H
