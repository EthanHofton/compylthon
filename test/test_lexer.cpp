#include <gtest/gtest.h>

#include "cpy/lexer.hpp"

using namespace cpy;

// test the tokenize function
TEST(TestLexer, TestTokenizeIdentAssignIntgerLiteral) {
    std::string prog = "varx = 1";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "varx");

    ASSERT_EQ(tokens[2].type, token_type::ASSIGN);
    ASSERT_FALSE(tokens[2].value.has_value());

    ASSERT_EQ(tokens[3].type, token_type::INTEGER_LITERAL);
    ASSERT_TRUE(tokens[3].value.has_value());
    ASSERT_EQ(tokens[3].value, "1");

    ASSERT_EQ(tokens[4].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[4].value.has_value());
}

TEST(TestLexer, TestTokenizeIdentAssignFloatLiteral) {
    std::string prog = "vary = 112.567";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "vary");

    ASSERT_EQ(tokens[2].type, token_type::ASSIGN);
    ASSERT_FALSE(tokens[2].value.has_value());

    ASSERT_EQ(tokens[3].type, token_type::FLOAT_LITERAL);
    ASSERT_TRUE(tokens[3].value.has_value());
    ASSERT_EQ(tokens[3].value, "112.567");

    ASSERT_EQ(tokens[4].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[4].value.has_value());
}

TEST(TestLexer, TestTokenizeIdentAssignBooleanLiteralTrue) {
    std::string prog = "a = true";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "a");

    ASSERT_EQ(tokens[2].type, token_type::ASSIGN);
    ASSERT_FALSE(tokens[2].value.has_value());

    ASSERT_EQ(tokens[3].type, token_type::BOOLEAN_LITERAL);
    ASSERT_TRUE(tokens[3].value.has_value());
    ASSERT_EQ(tokens[3].value, "true");

    ASSERT_EQ(tokens[4].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[4].value.has_value());
}

TEST(TestLexer, TestTokenizeIdentAssignBooleanLiteralFalse) {
    std::string prog = "a = false";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "a");

    ASSERT_EQ(tokens[2].type, token_type::ASSIGN);
    ASSERT_FALSE(tokens[2].value.has_value());

    ASSERT_EQ(tokens[3].type, token_type::BOOLEAN_LITERAL);
    ASSERT_TRUE(tokens[3].value.has_value());
    ASSERT_EQ(tokens[3].value, "false");

    ASSERT_EQ(tokens[4].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[4].value.has_value());
}

TEST(TestLexer, TestTokenizeIdentAssignStringLiteral) {
    std::string prog = R"(a = "hello world 12345!")";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "a");

    ASSERT_EQ(tokens[2].type, token_type::ASSIGN);
    ASSERT_FALSE(tokens[2].value.has_value());

    ASSERT_EQ(tokens[3].type, token_type::STRING_LITERAL);
    ASSERT_TRUE(tokens[3].value.has_value());
    ASSERT_EQ(tokens[3].value, "hello world 12345!");

    ASSERT_EQ(tokens[4].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[4].value.has_value());
}

TEST(TestLexer, TestTokenizeIdentAssignStringLiteralWithEscape) {
    std::string prog = R"(a = "hello world 12345!\n")";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "a");

    ASSERT_EQ(tokens[2].type, token_type::ASSIGN);
    ASSERT_FALSE(tokens[2].value.has_value());

    ASSERT_EQ(tokens[3].type, token_type::STRING_LITERAL);
    ASSERT_TRUE(tokens[3].value.has_value());
    ASSERT_EQ(tokens[3].value, "hello world 12345!\n");

    ASSERT_EQ(tokens[4].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[4].value.has_value());
}

TEST(TestLexer, TestTokenizeIdentifier) {
    std::string prog = "ident";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "ident");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 5);
}

TEST(TestLexer, TestTokenizeIdentifierWithNumbers) {
    std::string prog = "ident12345abc";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "ident12345abc");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 13);
}

TEST(TextLexer, TestTokenizeIdentifierWithUnderscore) {
    std::string prog = "ident_12345";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "ident_12345");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 11);
}

TEST(TextLexer, TestTokenizeIdentifierStartingUnderscore) {
    std::string prog = "_ident_12345";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "_ident_12345");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 12);
}

TEST(TestLexer, TestTokenizeAssign) {
    std::string prog = "=";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::ASSIGN);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 1);
}

TEST(TestLexer, TestTokenizeIntegerLiteral) {
    std::string prog = "1234567";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::INTEGER_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "1234567");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 7);
}

TEST(TestLexer, TestTokenizeFloatLiteral) {
    std::string prog = "123.456";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::FLOAT_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "123.456");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 7);
}

TEST(TestLexer, TestTokenizeFloatLiteralNoFract) {
    std::string prog = "123.";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::FLOAT_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "123.");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 4);
}

TEST(TestLexer, TestTokenizeFloatLiteralNoFractIdent) {
    std::string prog = "123.abc";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 4);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::FLOAT_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "123.");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::IDENTIFIER);
    ASSERT_TRUE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].value, "abc");
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 4);

    ASSERT_EQ(tokens[3].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[3].value.has_value());
    ASSERT_EQ(tokens[3].line_number, 0);
    ASSERT_EQ(tokens[3].line_offset, 7);
}

TEST(TestLexer, TestTokenizeNewLine) {
    std::string prog = R"(
1234

5678 9
"Hello, World\n\n"
123.456
true
)";

    
    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 8);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::INTEGER_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "1234");
    ASSERT_EQ(tokens[1].line_number, 1);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::INTEGER_LITERAL);
    ASSERT_TRUE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].value, "5678");
    ASSERT_EQ(tokens[2].line_number, 3);
    ASSERT_EQ(tokens[2].line_offset, 0);

    ASSERT_EQ(tokens[3].type, token_type::INTEGER_LITERAL);
    ASSERT_TRUE(tokens[3].value.has_value());
    ASSERT_EQ(tokens[3].value, "9");
    ASSERT_EQ(tokens[3].line_number, 3);
    ASSERT_EQ(tokens[3].line_offset, 5);

    ASSERT_EQ(tokens[4].type, token_type::STRING_LITERAL);
    ASSERT_TRUE(tokens[4].value.has_value());
    ASSERT_EQ(tokens[4].value, "Hello, World\n\n");
    ASSERT_EQ(tokens[4].line_number, 4);
    ASSERT_EQ(tokens[4].line_offset, 0);

    ASSERT_EQ(tokens[5].type, token_type::FLOAT_LITERAL);
    ASSERT_TRUE(tokens[5].value.has_value());
    ASSERT_EQ(tokens[5].value, "123.456");
    ASSERT_EQ(tokens[5].line_number, 5);
    ASSERT_EQ(tokens[5].line_offset, 0);

    ASSERT_EQ(tokens[6].type, token_type::BOOLEAN_LITERAL);
    ASSERT_TRUE(tokens[6].value.has_value());
    ASSERT_EQ(tokens[6].value, "true");
    ASSERT_EQ(tokens[6].line_number, 6);
    ASSERT_EQ(tokens[6].line_offset, 0);

    ASSERT_EQ(tokens[7].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[7].value.has_value());
    ASSERT_EQ(tokens[7].line_number, 7);
    ASSERT_EQ(tokens[7].line_offset, 0);
}

TEST(TestLexer, TestTokenizeStringLiteral) {
    std::string prog = R"("Hello, World!!!?")";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::STRING_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "Hello, World!!!?");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 18);
}

TEST(TestLexer, TestTokenizeStringLiteralNoTerminiator) {
    std::string prog = R"("Hello, World!!!?)";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_TRUE(l.has_errors());
    ASSERT_EQ(l.get_errors().size(), 1);
    ASSERT_EQ(l.get_errors()[0].line_number, 0);
    ASSERT_EQ(l.get_errors()[0].line_offset, 17);
    ASSERT_EQ(l.get_errors()[0].code, error_code::E005);
        
    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::STRING_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "Hello, World!!!?");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 17);
}

TEST(TestLexer, TestTokenizeBooleanTrue) {
    std::string prog = "true";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::BOOLEAN_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "true");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 4);
}

TEST(TestLexer, TestTokenizeBooleanFalse) {
    std::string prog = "false";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::BOOLEAN_LITERAL);
    ASSERT_TRUE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].value, "false");
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 5);
}

TEST(TestLexer, TestTokenizeUnknownCharicter) {
    std::string prog = "$#~";

    lexer l(prog);
    auto tokens = l.tokenize();

    ASSERT_TRUE(l.has_errors());
    ASSERT_EQ(l.get_errors().size(), 3);

    ASSERT_EQ(l.get_errors()[0].code, error_code::E004);
    ASSERT_EQ(l.get_errors()[0].line_number, 0);
    ASSERT_EQ(l.get_errors()[0].line_offset, 0);

    ASSERT_EQ(l.get_errors()[1].code, error_code::E004);
    ASSERT_EQ(l.get_errors()[1].line_number, 0);
    ASSERT_EQ(l.get_errors()[1].line_offset, 1);

    ASSERT_EQ(l.get_errors()[2].code, error_code::E004);
    ASSERT_EQ(l.get_errors()[2].line_number, 0);
    ASSERT_EQ(l.get_errors()[2].line_offset, 2);

    ASSERT_EQ(tokens.size(), 2);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 3);
}

TEST(TestLexer, TestTokenizeIf) {
    std::string prog = "if";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::IF);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 2);
}

TEST(TestLexer, TestTokenizeElse) {
    std::string prog = "else";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::ELSE);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 4);
}

TEST(TestLexer, TestTokenizeWhile) {
    std::string prog = "while";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::WHILE);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 5);
}

TEST(TestLexer, TestTokenizeFor) {
    std::string prog = "for";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::FOR);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 3);
}

TEST(TestLexer, TestTokenizeIn) {
    std::string prog = "in";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::IN);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 2);
}

TEST(TestLexer, TestTokenizeLeftParenthasis) {
    std::string prog = "(";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::LEFT_PARENTHASIS);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 1);
}

TEST(TestLexer, TestTokenizeRightParenthasis) {
    std::string prog = ")";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::RIGHT_PARENTHASIS);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 1);
}

TEST(TestLexer, TestTokenizeRightCurlyParenthasis) {
    std::string prog = "}";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::RIGHT_CURLY_PARENTHASIS);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 1);
}

TEST(TestLexer, TestTokenizeLeftCurlyParenthasis) {
    std::string prog = "{";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::LEFT_CURLY_PARENTHASIS);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 1);
}

TEST(TestLexer, TestTokenizeComma) {
    std::string prog = ",";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::COMMA);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 1);
}

TEST(TestLexer, TestTokenizeSemiColon) {
    std::string prog = ";";

    lexer l(prog);
    auto tokens = l.tokenize();

    l.print_errors(std::cerr);

    ASSERT_FALSE(l.has_errors());

    ASSERT_EQ(tokens.size(), 3);

    ASSERT_EQ(tokens[0].type, token_type::START_OF_FILE);
    ASSERT_FALSE(tokens[0].value.has_value());
    ASSERT_EQ(tokens[0].line_number, 0);
    ASSERT_EQ(tokens[0].line_offset, 0);

    ASSERT_EQ(tokens[1].type, token_type::SEMI_COLON);
    ASSERT_FALSE(tokens[1].value.has_value());
    ASSERT_EQ(tokens[1].line_number, 0);
    ASSERT_EQ(tokens[1].line_offset, 0);

    ASSERT_EQ(tokens[2].type, token_type::END_OF_FILE);
    ASSERT_FALSE(tokens[2].value.has_value());
    ASSERT_EQ(tokens[2].line_number, 0);
    ASSERT_EQ(tokens[2].line_offset, 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
