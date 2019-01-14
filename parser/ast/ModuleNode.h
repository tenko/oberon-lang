/*
 * Header file of the AST module nodes used by the Oberon-0 compiler.
 *
 * Created by Michael Grossniklaus on 3/6/18.
 */

#ifndef OBERON0C_MODULENODE_H
#define OBERON0C_MODULENODE_H


#include <memory>
#include <string>
#include "BlockNode.h"
#include "ProcedureNode.h"

class ModuleNode final : public BlockNode {

private:
    std::string name_;
    std::vector<std::unique_ptr<ProcedureNode>> procedures_;

public:
    explicit ModuleNode(FilePos pos, const std::string &name, int level);
    ~ModuleNode() final;

    const std::string getName() const;

    void addProcedure(std::unique_ptr<ProcedureNode> procedure) final;
    ProcedureNode* getProcedure(size_t num) const final;
    size_t getProcedureCount() const final;

    void accept(NodeVisitor& visitor) final;

    void print(std::ostream &stream) const final;

};


#endif //OBERON0C_MODULENODE_H
