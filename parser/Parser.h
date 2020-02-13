/*
 * Header of the parser class used by the Oberon-0 compiler.
 *
 * Created by Michael Grossniklaus on 2/2/18.
 */

#ifndef OBERON0C_PARSER_H
#define OBERON0C_PARSER_H


#include <memory>
#include <vector>
#include <set>
#include "../scanner/Scanner.h"
#include "../util/Logger.h"
#include "ast/Node.h"
#include "ast/LiteralNode.h"
#include "ast/ExpressionNode.h"
#include "ast/TypeNode.h"
#include "ast/ArrayTypeNode.h"
#include "ast/RecordTypeNode.h"
#include "ast/ProcedureNode.h"
#include "ast/ModuleNode.h"
#include "ast/StatementNode.h"
#include "ast/StatementSequenceNode.h"
#include "ast/ReferenceNode.h"
#include "ast/CallNode.h"
#include "symbol/SymbolTable.h"

class Parser {

private:
    Scanner *scanner_;
    Logger *logger_;
    std::unique_ptr<const Token> token_;
    std::unique_ptr<SymbolTable> symbols_;

    const std::string ident();
    std::unique_ptr<ModuleNode> module();
    void declarations(BlockNode *block);
    void const_declarations(BlockNode *block);
    void type_declarations(BlockNode *block);
    void var_declarations(BlockNode *block);
    void procedure_declaration(BlockNode *block);
    std::unique_ptr<ExpressionNode> expression();
    std::unique_ptr<ExpressionNode> simple_expression();
    std::unique_ptr<ExpressionNode> term();
    std::unique_ptr<ExpressionNode> factor();
    TypeNode* type(BlockNode *block);
    ArrayTypeNode* array_type(BlockNode *block);
    RecordTypeNode* record_type(BlockNode *block);
    void field_list(BlockNode *block, RecordTypeNode *record);
    void ident_list(std::vector<std::string> &idents);
    std::unique_ptr<ProcedureNode> procedure_heading();
    void procedure_body(ProcedureNode *proc);
    void formal_parameters(ProcedureNode *proc);
    void fp_section(ProcedureNode *proc);
    void statement_sequence(StatementSequenceNode* statements);
    std::unique_ptr<StatementNode> statement();
    std::unique_ptr<StatementNode> assignment(std::unique_ptr<ReferenceNode> lvalue);
    void procedure_call(CallNode *call);
    std::unique_ptr<StatementNode> if_statement();
    std::unique_ptr<StatementNode> loop_statement();
    std::unique_ptr<StatementNode> while_statement();
    std::unique_ptr<StatementNode> repeat_statement();
    std::unique_ptr<StatementNode> for_statement();
    void actual_parameters(CallNode *call);
    TypeNode* selector(ReferenceNode *ident, const TypeNode *type);

    std::unique_ptr<LiteralNode> fold(const ExpressionNode *expr) const;
    int foldNumber(const ExpressionNode *expr) const;
    bool foldBoolean(const ExpressionNode *expr) const;
    const std::string foldString(const ExpressionNode *expr) const;

    bool checkActualParameter(const ProcedureNode *proc, size_t num, const ExpressionNode *expr);

    void resync(std::set<TokenType> types);

public:
    explicit Parser(Scanner *scanner, Logger *logger);
    ~Parser();
    std::unique_ptr<ModuleNode> parse();

};

#endif //OBERON0C_PARSER_H
