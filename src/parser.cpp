#include "cpy/parser.hpp"

namespace cpy {

parser::parser(const std::vector<token>& t_tokens)
    : m_tokens(t_tokens)
{}

std::optional<NodeProgram> parser::parse() {
    std::optional<NodeProgram> root;

    return root;
}

std::optional<NodeScope> parser::parse_scope(bool require_curlys) {
    std::optional<NodeScope> scope = NodeScope();

    if (require_curlys) {
        if (!peek().has_value()) {
            return std::nullopt;
        }

        if (peek().value().type != token_type::LEFT_CURLY_PARENTHASIS) {
            return std::nullopt;
        }

        consume();
    }

    std::optional<NodeStatment> statment;
    while ((statment = parse_statment()).has_value()) {
        scope.value().statments.push_back(statment.value());
    }

    if (require_curlys) {
        expect(token_type::RIGHT_CURLY_PARENTHASIS);
        return std::nullopt;
    }

    return scope;
}

std::optional<NodeStatment> parser::parse_statment() {
    NodeStatment statment;

    // first check for scope
    std::optional<NodeScope> scope;
    if ((scope = parse_scope()).has_value()) {
        statment.statment = scope.value();
        return statment;
    }

    // next check for assigment
    std::optional<NodeAssigment> assigment;
    if ((assigment = parse_assigment()).has_value()) {
        statment.statment = assigment.value();
        return statment;
    }

    // next check for expression
    std::optional<NodeExpression()> expression;
    if ((expression = parse_expression()).has_value()) {
        statment.statment = expression.value();
        return statment;
    }

    return std::nullopt;
}

std::optional<NodeExpression> parser::parse_expression() {
    NodeExpression expression;

    // check for literal
    std::optional<NodeLiteral> literal;
    if ((literal = parse_literal()).has_value()) {
        expression.expressions = literal.value();
        return expression;
    }
    
    // check for identifier
    std::optional<NodeIdentifier> identifier;
    if ((identifier = parse_identifier()).has_value()) {
        expression.expressions = identifier.value();
        return expression;
    }

    return std::nullopt;
}

std::optional<NodeAssigment> parser::parse_assigment() {}
std::optional<NodeIdentifier> parser::parse_identifier() {}
std::optional<NodeLiteral> parser::parse_literal() {}
std::optional<NodeLiteralInteger> parser::parse_literal_integer() {}
std::optional<NodeLiteralFloat> parser::parse_literal_float() {}
std::optional<NodeLiteralBoolean> parser::parse_literal_boolean() {}
std::optional<NodeLiteralString> parser::parse_literal_string() {}

bool parser::expect(token_type t_type) {
    if (peek().has_value()) {
        // expected t_token
        return false;
    }

    if (peek().value().type != t_type) {
        // expected type type, got peek().value().type
        return false;
    }

    consume();

    return true;
}

std::optional<token> parser::peek(int offset) const {
    if (m_pos + offset >= m_tokens.size()) {
        return std::nullopt;
    }

    return m_tokens.at(m_pos + offset);
}
std::optional<token> parser::consume() {
    if (m_pos >= m_tokens.size()) {
        return std::nullopt;
    }

    return m_tokens.at(m_pos++);
}

}
