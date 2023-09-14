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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
