#ifndef __CPY_PARSER_HPP__
#define __CPY_PARSER_HPP__

#include <vector>
#include <stack>

#include "tokens.hpp"
#include "grammar_tree.hpp"
#include "errors.hpp"
#include "transaction.hpp"

namespace cpy {

class parser {
public:

    /**
    * @brief construct a new parser
    *
    * @param m_tokens the tokens to parse
    */
    explicit parser(const std::vector<token>& t_tokens);

    /**
    * @brief parse the tokens
    *
    * @return the root node of the constructed AST
    */
    [[nodiscard]] std::optional<NodeProgram> parse();

    /**
    * @brief print the errors of the error handlers
    *
    * @param t_out the output stream to print to
    */
    inline void print_errors(std::ostream& t_out = std::cerr) const { m_error_handler.print_errors(t_out); }

    /**
    * @brief clear the errors from the error handler
    */
    inline void clear_errors() { m_error_handler.clear_errors(); }

    /**
    * @brief returns the errors from the error handler
    *
    * @return std::vector<error> the errors
    */
    [[nodiscard]] inline std::vector<error> get_errors() const { return m_error_handler.get_errors(); }

    /**
    * @brief returns whether or not the error handler has errors
    *
    * @return bool whether or not the error handler has errors
    */
    [[nodiscard]] inline bool has_errors() const { return m_error_handler.has_errors(); }

private:

    std::optional<NodeProgram> parse_program();
    std::optional<NodeScope> parse_scope(bool require_curlys = true);
    std::optional<NodeStatment> parse_statment();
    std::optional<NodeExpression> parse_expression();
    std::optional<NodeAssigment> parse_assigment();
    std::optional<NodeIdentifier> parse_identifier();
    std::optional<NodeLiteral> parse_literal();
    std::optional<NodeLiteralInteger> parse_literal_integer();
    std::optional<NodeLiteralFloat> parse_literal_float();
    std::optional<NodeLiteralBoolean> parse_literal_boolean();
    std::optional<NodeLiteralString> parse_literal_string();

    bool expect(token_type t_type);

    std::optional<token> peek(int offset = 0) const;
    std::optional<token> consume();

    std::vector<token> m_tokens;
    transaction_manager m_transaction_manager;

    error_handler m_error_handler;

};

}

#endif // __CPY_PARSER_HPP__
