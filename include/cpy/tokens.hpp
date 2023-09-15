#ifndef __CPY_TOKENS_HPP__
#define __CPY_TOKENS_HPP__

#include <string>
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

}

#endif // __CPY_TOKENS_HPP__
