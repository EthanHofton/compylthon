#ifndef __CPY_LEXER_HPP__
#define __CPY_LEXER_HPP__

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "tokens.hpp"
#include "errors.hpp"

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

    /**
    * @brief prints the errors from the error handler
    *
    * @param t_out the output stream to print to
    */
    inline void print_errors(std::ostream& t_out = std::cerr) { m_error_handler.print_errors(t_out); }

    /**
    * @brief clears the errors from the error handler
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

    std::optional<char> peek(int offset = 0);
    std::optional<char> consume();

    token parse_number_literal(std::string& buf);
    token parse_string_literal(std::string& buf);
    token parse_keyword_or_identifer_literal(std::string& buf);

    std::string m_src;
    size_t m_pos = 0;

    size_t m_line_num = 0;
    size_t m_line_offset = 0;

    size_t m_token_start_line_num = 0;
    size_t m_token_start_line_offset = 0;

    error_handler m_error_handler;
};

} // namespace cpy

#endif // __CPY_LEXER_HPP__
