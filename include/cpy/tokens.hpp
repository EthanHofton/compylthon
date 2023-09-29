#ifndef __CPY_TOKENS_HPP__
#define __CPY_TOKENS_HPP__

#include <string>
#include <iostream>
#include <optional>

namespace cpy
{

enum class token_type
{
    // file
    START_OF_FILE, // done tested
    END_OF_FILE, // done tested

    // EXPRESSION
    IDENTIFIER, // done tested

    // LITERAL
    STRING_LITERAL, // done tested
    INTEGER_LITERAL, // done tested
    FLOAT_LITERAL, // done tested
    BOOLEAN_LITERAL, //done tested

    // BINARY_OPERATOR
    ADD, // + done tested
    SUBTRACT, // - done tested
    MULTIPLY, // * done tested
    DIVIDE, // / done tested
    POWER, // ** done tested
    EQUAL, // == done tested
    NOT_EQUAL, // != done tested
    LESS_THAN_OR_EQUAL, // <= done tested
    GRATER_THAN_OR_EUQAL, // >= done tested
    LESS_THAN, // < done tested
    GRATER_THAN, // > done tested
    LOGICAL_AND, // && done tested
    LOGICAL_OR, // || done tested
    LEFT_SHIFT, // << done tested
    RIGHT_SHIFT, // >> done tested
    BITWISE_XOR, // ^ done tested
    BITWISE_AND, // & done tested
    BITWISE_OR, // | done tested

    // UNARY_OPERATOR
    NOT, // ! done tested

    // MISC
    COMMA, // done tested
    LEFT_PARENTHASIS, // done tested
    RIGHT_PARENTHASIS, // done tested
    LEFT_CURLY_PARENTHASIS, // done tested
    RIGHT_CURLY_PARENTHASIS, // done tested
    ASSIGN, // done tested
    SEMI_COLON, // done tested

    // CONDITIONAL
    IF, // done tested
    ELSE, // done tested

    // LOOP
    WHILE, // done tested
    FOR, // done tested
    IN, // done tested
};

struct token {
    token_type type;

    size_t line_number;
    size_t line_offset;

    std::optional<std::string> value;
};

inline std::ostream& operator<<(std::ostream& os, token_type type) {
    switch (type) {
        case token_type::START_OF_FILE:
            os << "START_OF_FILE";
            break;
        case token_type::END_OF_FILE:
            os << "END_OF_FILE";
            break;
        case token_type::IDENTIFIER:
            os << "IDENTIFIER";
            break;
        case token_type::STRING_LITERAL:
            os << "STRING_LITERAL";
            break;
        case token_type::INTEGER_LITERAL:
            os << "INTEGER_LITERAL";
            break;
        case token_type::FLOAT_LITERAL:
            os << "FLOAT_LITERAL";
            break;
        case token_type::BOOLEAN_LITERAL:
            os << "BOOLEAN_LITERAL";
            break;
        case token_type::ADD:
            os << "+";
            break;
        case token_type::SUBTRACT:
            os << "-";
            break;
        case token_type::MULTIPLY:
            os << "*";
            break;
        case token_type::DIVIDE:
            os << "/";
            break;
        case token_type::POWER:
            os << "**";
            break;
        case token_type::EQUAL:
            os << "==";
            break;
        case token_type::NOT_EQUAL:
            os << "!=";
            break;
        case token_type::LESS_THAN_OR_EQUAL:
            os << "<=";
            break;
        case token_type::GRATER_THAN_OR_EUQAL:
            os << ">=";
            break;
        case token_type::LESS_THAN:
            os << "<";
            break;
        case token_type::GRATER_THAN:
            os << ">";
            break;
        case token_type::LOGICAL_AND:
            os << "&&";
            break;
        case token_type::LOGICAL_OR:
            os << "||";
            break;
        case token_type::LEFT_SHIFT:
            os << "<<";
            break;
        case token_type::RIGHT_SHIFT:
            os << ">>";
            break;
        case token_type::BITWISE_XOR:
            os << "~";
            break;
        case token_type::BITWISE_AND:
            os << "&";
            break;
        case token_type::BITWISE_OR:
            os << "|";
            break;
        case token_type::NOT:
            os << "!";
            break;
        case token_type::COMMA:
            os << ",";
            break;
        case token_type::LEFT_PARENTHASIS:
            os << "(";
            break;
        case token_type::RIGHT_PARENTHASIS:
            os << ")";
            break;
        case token_type::LEFT_CURLY_PARENTHASIS:
            os << "{";
            break;
        case token_type::RIGHT_CURLY_PARENTHASIS:
            os << "}";
            break;
        case token_type::ASSIGN:
            os << "=";
            break;
        case token_type::SEMI_COLON:
            os << ";";
            break;
        case token_type::IF:
            os << "IF";
            break;
        case token_type::ELSE:
            os << "ELSE";
            break;
        case token_type::WHILE:
            os << "WHILE";
            break;
        case token_type::FOR:
            os << "FOR";
            break;
        case token_type::IN:
            os << "IN";
            break;
        default:
            os << "Unknown token type";
            break;
    }

    return os;
}

}

#endif // __CPY_TOKENS_HPP__
