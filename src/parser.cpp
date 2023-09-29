#include "cpy/parser.hpp"

namespace cpy {

parser::parser(const std::vector<token>& t_tokens)
    : m_tokens(t_tokens)
{}

std::optional<NodeProgram> parser::parse() {
    return parse_program();
}

std::optional<NodeProgram> parser::parse_program() {
    // Program Production:
    //  program -> scope
    // // program scope can be implicit

    expect(token_type::START_OF_FILE);

    auto scope = parse_scope(false);

    if (!scope.has_value()) {
        return std::nullopt;
    }

    expect(token_type::END_OF_FILE);

    return NodeProgram { scope.value() };
}
std::optional<NodeScope> parser::parse_scope(bool require_curlys) {
    // Scope Production:
    //  scope -> '{' { statment ';' } '}'
    // if require_curlys is false, then the scope can be implicit

    if (require_curlys && !expect(token_type::LEFT_CURLY_PARENTHASIS)) {
        return std::nullopt;
    } else {
        if (peek().has_value() && peek().value().type == token_type::LEFT_CURLY_PARENTHASIS) {
            consume();
        }
    }

    std::vector<NodeStatment> statments;

    while (peek().has_value() && peek().value().type != token_type::RIGHT_CURLY_PARENTHASIS && peek().value().type != token_type::END_OF_FILE) {
        auto statment = parse_statment();

        if (!statment.has_value()) {
            return std::nullopt;
        }

        if (!expect(token_type::SEMI_COLON)) {
            return std::nullopt;
        }

        statments.push_back(statment.value());
    }

    if (require_curlys && !expect(token_type::RIGHT_CURLY_PARENTHASIS)) {
        return std::nullopt;
    } else {
        if (peek().has_value() && peek().value().type == token_type::RIGHT_CURLY_PARENTHASIS) {
            consume();
        }
    }

    return NodeScope { statments };
}

std::optional<NodeStatment> parser::parse_statment() {
    // Statment Production:
    //  statment -> expression
    //  statment -> assigment

    // start a new transaction, so we can rollback if identifier of assigment gets consumed and fails

    m_transaction_manager.start();

    // important!! do assigment first, because it will consume the identifier
    auto assigment = parse_assigment();
    if (assigment.has_value()) {
        m_transaction_manager.commit();
        return NodeStatment { assigment.value() };
    }

    // rollback the transaction, so we can try the other production
    m_transaction_manager.rollback();

    // reset the transaction, so we can rollback if expression fails
    m_transaction_manager.start();

    auto expression = parse_expression();
    if (expression.has_value()) {
        m_transaction_manager.commit();
        return NodeStatment { expression.value() };
    }

    // rollback the transaction, so we can try the other production
    m_transaction_manager.rollback();


    m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Expected statment");
    return std::nullopt;
}

std::optional<NodeExpression> parser::parse_expression() {
    // Expression Production:
    //  expression -> identifier
    //  expression -> literal
    //  expression -> '(' expression ')'

    // since there are multiple productions, we need to try each one and rollback if it fails

    m_transaction_manager.start();

    auto identifier = parse_identifier();
    if (identifier.has_value()) {
        m_transaction_manager.commit();
        return NodeExpression { identifier.value() };
    }

    m_transaction_manager.rollback();

    m_transaction_manager.start();

    auto literal = parse_literal();
    if (literal.has_value()) {
        m_transaction_manager.commit();
        return NodeExpression { literal.value() };
    }

    m_transaction_manager.rollback();

    m_transaction_manager.start();

    if (expect(token_type::LEFT_PARENTHASIS)) {
        auto expression = parse_expression();
        if (!expression.has_value()) {
            m_transaction_manager.rollback();
            return std::nullopt;
        }

        if (!expect(token_type::RIGHT_PARENTHASIS)) {
            m_transaction_manager.rollback();
            return std::nullopt;
        }

        m_transaction_manager.commit();
        return NodeExpression { expression.value() };
    }

    m_transaction_manager.rollback();

    return std::nullopt;
}

std::optional<NodeAssigment> parser::parse_assigment() {
    // Assigment Production:
    //  assigment -> identifier '=' expression

    m_transaction_manager.start();

    auto identifier = parse_identifier();
    if (!identifier.has_value()) {
        m_transaction_manager.rollback();
        return std::nullopt;
    }

    if (!peek().has_value()) {
        m_transaction_manager.rollback();
        return std::nullopt;
    }
    
    if (peek().value().type != token_type::ASSIGN) {
        m_transaction_manager.rollback();
        return std::nullopt;
    }

    consume();

    auto expression = parse_expression();
    if (!expression.has_value()) {
        m_transaction_manager.rollback();
        return std::nullopt;
    }

    m_transaction_manager.commit();

    return NodeAssigment { identifier.value(), expression.value() };
}

std::optional<NodeIdentifier> parser::parse_identifier() {
    // Identifier Production (terminal):
    //  identifier -> IDENTIFIER

    if (!peek().has_value()) {
        return std::nullopt;
    }

    if (peek().value().type != token_type::IDENTIFIER) {
        return std::nullopt;
    }

    std::string identifier = peek().value().value.value();

    consume();

    return NodeIdentifier { identifier };
}

std::optional<NodeLiteral> parser::parse_literal() {
    // Literal Production:
    //  literal -> literal_integer
    //  literal -> literal_float
    //  literal -> literal_boolean
    //  literal -> literal_string

    // TODO:
    //  literal -> literal_array

    auto literal_integer = parse_literal_integer();
    if (literal_integer.has_value()) {
        return NodeLiteral { literal_integer.value() };
    }

    auto literal_float = parse_literal_float();
    if (literal_float.has_value()) {
        return NodeLiteral { literal_float.value() };
    }

    auto literal_boolean = parse_literal_boolean();
    if (literal_boolean.has_value()) {
        return NodeLiteral { literal_boolean.value() };
    }

    auto literal_string = parse_literal_string();
    if (literal_string.has_value()) {
        return NodeLiteral { literal_string.value() };
    }

    m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Expected literal");
    return std::nullopt;
}

std::optional<NodeLiteralInteger> parser::parse_literal_integer() {
    // Literal Integer Production (terminal):
    //  literal_integer -> INTEGER

    if (!peek().has_value()) {
        return std::nullopt;
    }

    if (peek().value().type != token_type::INTEGER_LITERAL) {
        return std::nullopt;
    }

    if (!peek().value().value.has_value()) {
        m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Expected integer literal");
    }

    std::string string_value = peek().value().value.value(); 
    int value;

    try {
        value = std::stoi(string_value);
    } catch (std::out_of_range) {
        m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Integer literal out of range");
        return std::nullopt;
    }

    consume();

    return NodeLiteralInteger { value };
}

std::optional<NodeLiteralFloat> parser::parse_literal_float() {
    // Literal float Production (terminal):
    //  literal_float -> FLOAT

    if (!peek().has_value()) {
        return std::nullopt;
    }

    if (peek().value().type != token_type::FLOAT_LITERAL) {
        return std::nullopt;
    }

    if (!peek().value().value.has_value()) {
        m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Expected float literal");
    }

    std::string string_value = peek().value().value.value(); 
    float value;

    try {
        value = std::stof(string_value);
    } catch (std::out_of_range) {
        m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Float literal out of range");
        return std::nullopt;
    }

    consume();

    return NodeLiteralFloat { value };
}

std::optional<NodeLiteralBoolean> parser::parse_literal_boolean() {
    // Literal boolean Production (terminal):
    //  literal_boolean -> true 
    //  literal_boolean -> false 

    if (!peek().has_value()) {
        return std::nullopt;
    }

    if (peek().value().type != token_type::BOOLEAN_LITERAL) {
        return std::nullopt;
    }

    if (!peek().value().value.has_value()) {
        m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Expected boolean literal");
    }

    std::string string_value = peek().value().value.value(); 

    if (string_value != "true" && string_value != "false") {
        m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Expected boolean literal");
    }

    bool value = string_value == "true";

    consume();

    return NodeLiteralBoolean { value };
}

std::optional<NodeLiteralString> parser::parse_literal_string() {
    // Literal String Production (terminal):
    //  literal_string -> "STRING"

    if (!peek().has_value()) {
        return std::nullopt;
    }

    if (peek().value().type != token_type::STRING_LITERAL) {
        return std::nullopt;
    }

    if (!peek().value().value.has_value()) {
        m_error_handler.add_error(peek().value().line_number, peek().value().line_offset, error_code::E006, "Expected string literal");
    }

    std::string string_value = peek().value().value.value(); 

    consume();

    return NodeLiteralString { string_value };
}

bool parser::expect(token_type t_type) {
    if (!peek().has_value()) {
        std::stringstream error_ss;
        error_ss << "Expected token type " << t_type << ", got end of file";
        m_error_handler.add_error(peek(-1).value().line_number, peek(-1).value().line_offset, error_code::E006, error_ss.str());
        return false;
    }

    if (peek().value().type != t_type) {
        std::stringstream error_ss;
        error_ss << "Expected token type " << t_type << ", got " << peek().value().type;
        m_error_handler.add_error(peek(-1).value().line_number, peek(-1).value().line_offset, error_code::E006, error_ss.str());
        return false;
    }

    consume();

    return true;
}

std::optional<token> parser::peek(int offset) const {
    size_t pos = m_transaction_manager.pos();

    if (pos + offset >= m_tokens.size()) {
        return std::nullopt;
    }

    return m_tokens.at(pos + offset);
}

std::optional<token> parser::consume() {
    size_t& pos = m_transaction_manager.pos();

    if (pos >= m_tokens.size()) {
        return std::nullopt;
    }

    return m_tokens.at(pos++);
}

}
