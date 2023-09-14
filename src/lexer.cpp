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
        if (std::isalpha(peek().value())) {
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
        } else if (peek().value() == '=') {
            // assignment
            consume();
            tokens.push_back({ token_type::ASSIGN, m_line_num, m_line_offset });
            continue;
        } else if (peek().value() == '\n') {
            // newline
            m_line_num++;
            m_line_offset = 0;
            consume();
            continue;
        } else if (std::isspace(peek().value())) {
            // whitespace
            consume();
            continue;
        } else {
            // unknown
            // TODO: add to list of errors, for now just print to cerr and cosume
            std::cerr << "Unknown token: " << peek().value() << " at line " << m_line_num << ":"<< m_line_offset << std::endl;
            consume();
            continue;
        }
    }

    tokens.push_back({ token_type::END_OF_FILE, m_line_num, m_line_offset });

    m_line_num = 0;
    m_line_offset = 0;
    m_pos = 0;

    return tokens;
}

token lexer::parse_keyword_or_identifer_literal(std::string& buf) {
    std::optional<std::string> val;
    token_type type;

    while (peek().has_value() && std::isalnum(peek().value())) {
        buf += consume().value();
    }

    // check for keywords
    if (buf == "true" || buf == "false") {
        type = token_type::BOOLEAN_LITERAL;
        val = buf;
    } else {
        type = token_type::IDENTIFIER;
        val = buf;
    }

    token t = { type, m_line_num, m_line_offset, val };
    buf.clear();
    return t;
}

token lexer::parse_number_literal(std::string& buf) {
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
        token t = { token_type::FLOAT_LITERAL, m_line_num, m_line_offset, buf };
        buf.clear();
        return t;
    }

    token t = { token_type::INTEGER_LITERAL, m_line_num, m_line_offset, buf };
    buf.clear();
    return t;
}

token lexer::parse_string_literal(std::string& buf) {
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
        // TODO: add to list of errors, for now just print to cerr and cosume
        // unterminated string literal
        std::cerr << "Unterminated string literal at line " << m_line_num << ":"<< m_line_offset << std::endl;
    }

    // consume closing quote 
    consume();

    token t = { token_type::STRING_LITERAL, m_line_num, m_line_offset, buf };
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
