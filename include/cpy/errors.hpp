#ifndef __CPY_ERRORS_HPP__
#define __CPY_ERRORS_HPP__

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

namespace cpy {

enum class error_code {
    E001, // Syntax Error - Unexpected token
    E002, // Undefined variable
    E003, // Invalid function call
    E004, // Unknown character
    E005, // Unterminated string literal
};

inline extern const std::unordered_map<error_code, std::string> error_messages = {
    {error_code::E001, "Syntax Error - Unexpected token"},
    {error_code::E002, "Undefined variable"},
    {error_code::E003, "Invalid function call"},
    {error_code::E004, "Unknown character"},
    {error_code::E005, "Unterminated string literal"},
};

inline std::ostream& operator<<(std::ostream& os, error_code code) {
    switch (code) {
        case error_code::E001:
            os << "E001";
            break;
        case error_code::E002:
            os << "E002";
            break;
        case error_code::E003:
            os << "E003";
            break;
        case error_code::E004:
            os << "E004";
            break;
        case error_code::E005:
            os << "E005";
            break;
        default:
            os << "Unknown error code";
            break;
    }
    return os;
}
    
struct error {
    size_t line_number;
    size_t line_offset;
    error_code code;
};

class error_handler {
public:

    /**
    * @brief add an error to the error handler
    *
    * @param error the error to add
    */
    void add_error(const error& err) {
        m_errors.push_back(err);
    }

    /**
    * @brief add an error to the error handler
    *
    * @param line_number the line number
    * @param line_offset the line offset
    * @param code the error code
    */
    void add_error(size_t line_number, size_t line_offset, error_code code) {
        m_errors.push_back({line_number, line_offset, code});
    }

    /**
    * @brief prints the errors to the specified output stream
    *
    * @param out the output stream
    */
    void print_errors(std::ostream& out = std::cerr) const {
        for (const auto& err : m_errors) {
            out << "Error " << err.code << ": " << error_messages.at(err.code) << " at line " << err.line_number << ":" << err.line_offset << std::endl;
        }
    }

    /**
    * @brief clears the errors
    */
    void clear_errors() {
        m_errors.clear();
    }

    /**
    * @brief returns whether or not the error handler has errors
    *
    * @return bool whether or not the error handler has errors
    */
    [[nodiscard]] bool has_errors() const {
        return !m_errors.empty();
    }

    /**
    * @brief returns the errors
    *
    * @return std::vector<error> the errors
    */
    [[nodiscard]] std::vector<error> get_errors() const {
        return m_errors;
    }

private:

    std::vector<error> m_errors;
};

}

#endif // __CPY_ERRORS_HPP__
