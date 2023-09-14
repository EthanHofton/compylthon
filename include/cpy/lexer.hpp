#ifndef __CPY_LEXER_HPP__
#define __CPY_LEXER_HPP__

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "tokens.hpp"

namespace cpy {

class lexer {
public:

    /**
    * @brief Construct a new lexer object
    *
    * @param std::string the source code to lex
    */
    explicit lexer(const std::string&);

    /**
    * @brief tokenizes the source code
    *
    * @return std::vector<tokens> the tokens
    */
    [[nodiscard]] std::vector<token> tokenize();

private:

    std::optional<char> peek(int offset = 0);
    std::optional<char> consume();

    token parse_number_literal(std::string& buf);
    token parse_string_literal(std::string& buf);
    token parse_keyword_or_identifer_literal(std::string& buf);

    std::string m_src;
    size_t m_pos = 0;
    size_t m_line_num = 0;
    size_t m_line_offset = 0;
};

} // namespace cpy

#endif // __CPY_LEXER_HPP__
