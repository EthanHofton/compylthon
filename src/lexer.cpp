#include "cpy/lexer.hpp"

namespace cpy {

lexer::lexer(const std::string& src)
    : m_src(src)
    , m_pos(0)
{}

std::vector<token> lexer::tokenize() {
    std::vector<token> tokens;
    tokens.push_back({ token_type::START_OF_FILE, m_line_num, m_line_offset });

    std::string buf;
    while (peek().has_value()) {
        if (std::isalpha(peek().value()) || peek().value() == '_') {
            // keyword or identifier
            tokens.push_back(parse_keyword_or_identifer_literal(buf));
            continue;
        } else if (peek().value() == '"') {
            // string literal
            tokens.push_back(parse_string_literal(buf));
            continue;
        } else if (std::isdigit(peek().value())) {
            // number literal
            tokens.push_back(parse_number_literal(buf));
            continue;
        }  else if (peek().value() == '(') {
            // left bracket
            tokens.push_back({ token_type::LEFT_PARENTHASIS, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == ')') {
            // right bracket
            tokens.push_back({ token_type::RIGHT_PARENTHASIS, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == '}') {
            // right curly bracket
            tokens.push_back({ token_type::RIGHT_CURLY_PARENTHASIS, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == '{') {
            // left curly bracket
            tokens.push_back({ token_type::LEFT_CURLY_PARENTHASIS, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == ',') {
            // right comma
            tokens.push_back({ token_type::COMMA, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == ';') {
            // semi colon 
            tokens.push_back({ token_type::SEMI_COLON, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == '+') {
            tokens.push_back({ token_type::ADD, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == '-') {
            tokens.push_back({ token_type::SUBTRACT, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == '*') {
            // **, *
            tokens.push_back(parse_star(buf));
            continue;
        } else if (peek().value() == '/') {
            tokens.push_back({ token_type::DIVIDE, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == '=') {
            // =, ==
            tokens.push_back(parse_equal(buf));
            continue;
        } else if (peek().value() == '!') {
            // !, !=
            tokens.push_back(parse_explination_mark(buf));
            continue;
        } else if (peek().value() == '<') {
            // <, <=, <<
            tokens.push_back(parse_less_than(buf));
            continue;
        } else if (peek().value() == '>') {
            // >, >=, >>
            tokens.push_back(parse_grater_than(buf));
            continue;
        } else if (peek().value() == '&') {
            // &, &&
            tokens.push_back(parse_and(buf));
            continue;
        } else if (peek().value() == '|') {
            // |, ||
            tokens.push_back(parse_or(buf));
            continue;
        } else if (peek().value() == '^') {
            // ^
            tokens.push_back({ token_type::BITWISE_XOR, m_line_num, m_line_offset });
            consume();
            continue;
        } else if (peek().value() == '\n') {
            // newline
            consume();
            m_line_num++;
            m_line_offset = 0;
            continue;
        } else if (std::isspace(peek().value())) {
            // whitespace
            consume();
            continue;
        } else {
            // unknown
            m_error_handler.add_error(m_line_num, m_line_offset, error_code::E004);
            consume();
            continue;
        }
    }

    tokens.push_back({ token_type::END_OF_FILE, m_line_num, m_line_offset });

    // reset lexer
    m_line_num = 0;
    m_line_offset = 0;
    m_pos = 0;

    return tokens;
}

token lexer::parse_keyword_or_identifer_literal(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    std::optional<std::string> val;
    token_type type;

    // check for underscore aswell for identifier
    while (peek().has_value() && (std::isalnum(peek().value()) || peek().value() == '_')) {
        buf += consume().value();
    }

    // check for keywords
    if (buf == "if") {
        type = token_type::IF;
    } else if (buf == "else") {
        type = token_type::ELSE;
    } else if (buf == "while") {
        type = token_type::WHILE;
    } else if (buf == "for") {
        type = token_type::FOR;
    } else if (buf == "in") {
        type = token_type::IN;
    } else if (buf == "true" || buf == "false") {
        type = token_type::BOOLEAN_LITERAL;
        val = buf;
    } else {
        type = token_type::IDENTIFIER;
        val = buf;
    }

    token t = { type, m_token_start_line_num, m_token_start_line_offset, val };
    buf.clear();
    return t;
}

token lexer::parse_number_literal(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    // integer literal or float literal
    while (peek().has_value() && std::isdigit(peek().value())) {
        buf += consume().value();
    }

    // check for floating point
    if (peek().has_value() && peek().value() == '.') {
        // floating point
        buf += consume().value();
        // get fractional part
        std::string fract;
        while (peek().has_value() && std::isdigit(peek().value())) {
            fract += consume().value(); 
        }

        buf += fract;
        token t = { token_type::FLOAT_LITERAL, m_token_start_line_num, m_token_start_line_offset, buf };
        buf.clear();
        return t;
    }

    token t = { token_type::INTEGER_LITERAL, m_token_start_line_num, m_token_start_line_offset, buf };
    buf.clear();
    return t;
}

token lexer::parse_string_literal(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    consume();
    while (peek().has_value() && peek().value() != '"') {
        if (peek().value() == '\\') {
            // escape sequence
            consume();
            if (peek().has_value()) {
                switch (peek().value()) {
                    case 'n':
                        buf += '\n';
                        break;
                    case 't':
                        buf += '\t';
                        break;
                    case 'r':
                        buf += '\r';
                        break;
                    case '0':
                        buf += '\0';
                        break;
                    case '\\':
                        buf += '\\';
                        break;
                    case '"':
                        buf += '"';
                        break;
                    default:
                        break;
                }
                consume();
                continue;
            }
        }
        buf += consume().value();
    }

    if (!peek().has_value()) {
        // unterminated string literal
        m_error_handler.add_error(m_line_num, m_line_offset, error_code::E005);
    }

    // consume closing quote 
    consume();

    token t = { token_type::STRING_LITERAL, m_token_start_line_num, m_token_start_line_offset, buf };
    buf.clear();
    return t;
}


token lexer::parse_equal(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    token_type type = token_type::ASSIGN;

    // consume the first =
    consume();

    if (peek().has_value() && peek().value() == '=') {
        // ==
        type = token_type::EQUAL;
        consume();
    }

    token t = { type, m_token_start_line_num, m_token_start_line_offset };
    buf.clear();
    return t;
}

token lexer::parse_star(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    token_type type = token_type::MULTIPLY;

    // consume the first *
    consume();

    if (peek().has_value() && peek().value() == '*') {
        // **
        type = token_type::POWER;
        consume();
    }

    token t = { type, m_token_start_line_num, m_token_start_line_offset };
    buf.clear();
    return t;
}
token lexer::parse_explination_mark(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    token_type type = token_type::NOT;

    // consume the first !
    consume();

    if (peek().has_value() && peek().value() == '=') {
        // !=
        type = token_type::NOT_EQUAL;
        consume();
    }

    token t = { type, m_token_start_line_num, m_token_start_line_offset };
    buf.clear();
    return t;
}

token lexer::parse_less_than(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    token_type type = token_type::LESS_THAN;

    // consume the first < 
    consume();

    if (peek().has_value() && peek().value() == '<') {
        // <<
        type = token_type::LEFT_SHIFT;
        consume();
    } else if (peek().has_value() && peek().value() == '=') {
        // <=
        type = token_type::LESS_THAN_OR_EQUAL; 
        consume();
    }

    token t = { type, m_token_start_line_num, m_token_start_line_offset };
    buf.clear();
    return t;
}

token lexer::parse_grater_than(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    token_type type = token_type::GRATER_THAN;

    // consume the first >
    consume();

    if (peek().has_value() && peek().value() == '>') {
        // >>
        type = token_type::RIGHT_SHIFT;
        consume();
    } else if (peek().has_value() && peek().value() == '=') {
        // >= 
        type = token_type::GRATER_THAN_OR_EUQAL;
        consume();
    }

    token t = { type, m_token_start_line_num, m_token_start_line_offset };
    buf.clear();
    return t;
}

token lexer::parse_and(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    token_type type = token_type::BITWISE_AND;

    // consume the first &
    consume();

    if (peek().has_value() && peek().value() == '&') {
        // &&
        type = token_type::LOGICAL_AND;
        consume();
    }

    token t = { type, m_token_start_line_num, m_token_start_line_offset };
    buf.clear();
    return t;
}

token lexer::parse_or(std::string& buf) {
    m_token_start_line_num = m_line_num;
    m_token_start_line_offset = m_line_offset; 

    token_type type = token_type::BITWISE_OR;

    // consume the first |
    consume();

    if (peek().has_value() && peek().value() == '|') {
        // ||
        type = token_type::LOGICAL_OR;
        consume();
    }

    token t = { type, m_token_start_line_num, m_token_start_line_offset };
    buf.clear();
    return t;
}

std::optional<char> lexer::peek(int offset) {
    if (m_pos + offset >= m_src.size()) {
        return std::nullopt;
    }

    return m_src.at(m_pos + offset);
}

std::optional<char> lexer::consume() {
    if (m_pos >= m_src.size()) {
        return std::nullopt;
    }

    m_line_offset++;
    return m_src.at(m_pos++);
}

}
