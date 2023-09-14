#ifndef __CPY_TOKENS_HPP__
#define __CPY_TOKENS_HPP__

#include <string>
#include <optional>

namespace cpy
{

enum class token_type
{
    // file
    START_OF_FILE,
    END_OF_FILE,

    // literals
    STRING_LITERAL,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    BOOLEAN_LITERAL,

    // expressions
    IDENTIFIER,

    // other
    ASSIGN,
};

struct token {
    token_type type;

    size_t line_number;
    size_t line_offset;

    std::optional<std::string> value;
};

}

#endif // __CPY_TOKENS_HPP__
