/*
 * Parser of the Oberon LLVM compiler.
 *
 * Created by Michael Grossniklaus on 2/2/18.
 */

#ifndef OBERON0C_PARSER_H
#define OBERON0C_PARSER_H


#include <memory>
#include <set>
#include <vector>

#include "scanner/Scanner.h"
#include "logging/Logger.h"
#include "data/ast/Node.h"
#include "data/ast/Ident.h"
#include "data/ast/ExpressionNode.h"
#include "data/ast/TypeNode.h"
#include "data/ast/ArrayTypeNode.h"
#include "data/ast/RecordTypeNode.h"
#include "data/ast/ProcedureNode.h"
#include "data/ast/PointerTypeNode.h"
#include "data/ast/ModuleNode.h"
#include "data/ast/StatementNode.h"
#include "data/ast/StatementSequenceNode.h"
#include "data/ast/NodeReference.h"
#include "data/symtab/SymbolTable.h"
#include "compiler/CompilerFlags.h"
#include "data/ast/ASTContext.h"
#include "sema/Sema.h"

using std::set;
using std::unique_ptr;
using std::vector;

class Parser {

private:
    CompilerFlags *flags_;
    Scanner *scanner_;
    Sema *sema_;
    Logger *logger_;
    unique_ptr<const Token> token_;

    unique_ptr<Ident> ident();
    unique_ptr<QualIdent> qualident();
    unique_ptr<Designator> designator();
    unique_ptr<Selector> selector();
    bool maybe_typeguard();
    unique_ptr<IdentDef> identdef(bool checkAlphaNum = true);
    void ident_list(vector<unique_ptr<Ident>> &idents);

    unique_ptr<ModuleNode> module();

    void import_list(vector<unique_ptr<ImportNode>> &);
    void import(vector<unique_ptr<ImportNode>> &);

    void declarations(vector<unique_ptr<ConstantDeclarationNode>> &,
                      vector<unique_ptr<TypeDeclarationNode>> &,
                      vector<unique_ptr<VariableDeclarationNode>> &,
                      vector<unique_ptr<ProcedureNode>> &);
    void const_declarations(vector<unique_ptr<ConstantDeclarationNode>> &);
    void type_declarations(vector<unique_ptr<TypeDeclarationNode>> &);
    void var_declarations(vector<unique_ptr<VariableDeclarationNode>> &);
    void procedure_declaration(vector<unique_ptr<ProcedureNode>> &);

    unique_ptr<ExpressionNode> expression();
    unique_ptr<ExpressionNode> simple_expression();
    unique_ptr<ExpressionNode> term();
    unique_ptr<ExpressionNode> factor();
    unique_ptr<ExpressionNode> basic_factor();

    TypeNode* type(Ident * = nullptr);

    ArrayTypeNode* array_type(Ident * = nullptr);

    RecordTypeNode* record_type(Ident * = nullptr);
    void field_list(vector<unique_ptr<FieldNode>> &);

    PointerTypeNode* pointer_type(Ident * = nullptr);

    ProcedureTypeNode* procedure_signature(Ident * = nullptr);
    unique_ptr<StatementSequenceNode> procedure_body(vector<unique_ptr<ConstantDeclarationNode>> &,
                                                     vector<unique_ptr<TypeDeclarationNode>> &,
                                                     vector<unique_ptr<VariableDeclarationNode>> &,
                                                     vector<unique_ptr<ProcedureNode>> &);
    void formal_parameters(vector<std::unique_ptr<ParameterNode>> &, bool &);
    void fp_section(vector<std::unique_ptr<ParameterNode>> &, bool &);

    unique_ptr<StatementSequenceNode> statement_sequence();
    unique_ptr<StatementNode> statement();
    unique_ptr<StatementNode> assignment(unique_ptr<ValueReferenceNode>);
    unique_ptr<StatementNode> if_statement();
    unique_ptr<StatementNode> loop_statement();
    unique_ptr<StatementNode> while_statement();
    unique_ptr<StatementNode> repeat_statement();
    unique_ptr<StatementNode> for_statement();
    void actual_parameters(ActualParameters *params);

    bool assertToken(const Token *token, TokenType expected);
    bool assertOberonIdent(const Ident *ident);

    void resync(set<TokenType> types);

public:
    explicit Parser(CompilerFlags *flags, Scanner *scanner, Sema *sema, Logger *logger) :
            flags_(flags), scanner_(scanner), sema_(sema), logger_(logger), token_() { };
    ~Parser() = default;

    ModuleNode *parse(ASTContext *context);

};


#endif //OBERON0C_PARSER_H
