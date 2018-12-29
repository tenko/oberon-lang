/*
 * Implementation of the AST record type nodes used by the Oberon-0 compiler.
 *
 * Created by Michael Grossniklaus on 2/9/18.
 */
#include "RecordTypeNode.h"

RecordTypeNode::RecordTypeNode(const FilePos pos) : TypeNode(NodeType::record_type, pos, 0), fields_() {
}

RecordTypeNode::~RecordTypeNode() = default;

void RecordTypeNode::addType(std::unique_ptr<TypeNode> type) {
    types_.push_back(std::move(type));
}

void RecordTypeNode::addField(std::unique_ptr<FieldNode> field) {
    fields_.push_back(std::move(field));
}

int RecordTypeNode::getSize() const {
    int size = 0;
    for (auto&& itr : fields_) {
        size += itr->getType()->getSize();
    }
    return size;
}

const FieldNode* RecordTypeNode::getField(const std::string& name) const {
    for (auto&& itr : fields_) {
        if (itr->getName() == name) {
            return itr.get();
        }
    }
    return nullptr;
}

void RecordTypeNode::print(std::ostream& stream) const {
    stream << "RECORD ";

}