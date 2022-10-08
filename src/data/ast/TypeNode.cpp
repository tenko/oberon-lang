/*
 * AST node representing a type in the Oberon LLVM compiler.
 *
 * Created by Michael Grossniklaus on 2/8/18.
 */

#include "TypeNode.h"

Ident *TypeNode::getIdentifier() const {
    return ident_;
}

TypeKind TypeNode::kind() const {
    return kind_;
}

void TypeNode::setSize(unsigned int size) {
    size_ = size;
}

unsigned int TypeNode::getSize() const {
    return size_;
}

bool TypeNode::isAnonymous() const {
    return anon_;
}

void TypeNode::setRef(int ref) {
    ref_ = ref;
}

int TypeNode::getRef() const {
    return ref_;
}