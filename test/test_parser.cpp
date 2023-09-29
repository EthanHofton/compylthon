#include <gtest/gtest.h>
#include "cpy/parser.hpp"

using namespace cpy;

TEST(TestParser, TestExpressionIdentifier) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::IDENTIFIER, 0, 0, "var1" },
        token { token_type::SEMI_COLON, 0, 4 },
        token { token_type::END_OF_FILE, 0, 0 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeExpression>(statment.statment));

    NodeExpression expression = std::get<NodeExpression>(statment.statment);

    EXPECT_TRUE(std::holds_alternative<NodeIdentifier>(expression.expressions));

    NodeIdentifier identifier = std::get<NodeIdentifier>(expression.expressions);

    EXPECT_EQ(identifier.name, "var1");
}

TEST(TestParser, TestExpressionLiteralString) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::STRING_LITERAL, 0, 0, "literal 1" },
        token { token_type::SEMI_COLON, 0, 4 },
        token { token_type::END_OF_FILE, 0, 0 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeExpression>(statment.statment));

    NodeExpression expression = std::get<NodeExpression>(statment.statment);

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralString>(literal.literal));

    NodeLiteralString literal_string = std::get<NodeLiteralString>(literal.literal);

    EXPECT_EQ(literal_string.value, "literal 1");
}

TEST(TestParser, TestExpressionLiteralBooleanTrue) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::BOOLEAN_LITERAL, 0, 0, "true" },
        token { token_type::SEMI_COLON, 0, 4 },
        token { token_type::END_OF_FILE, 0, 0 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeExpression>(statment.statment));

    NodeExpression expression = std::get<NodeExpression>(statment.statment);

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralBoolean>(literal.literal));

    NodeLiteralBoolean literal_boolean = std::get<NodeLiteralBoolean>(literal.literal);

    EXPECT_TRUE(literal_boolean.value);
}

TEST(TestParser, TestExpressionLiteralBooleanFalse) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::BOOLEAN_LITERAL, 0, 0, "false" },
        token { token_type::SEMI_COLON, 0, 4 },
        token { token_type::END_OF_FILE, 0, 0 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeExpression>(statment.statment));

    NodeExpression expression = std::get<NodeExpression>(statment.statment);

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralBoolean>(literal.literal));

    NodeLiteralBoolean literal_boolean = std::get<NodeLiteralBoolean>(literal.literal);

    EXPECT_FALSE(literal_boolean.value);
}

TEST(TestParser, TestExpressionLiteralInteger) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::INTEGER_LITERAL, 0, 0, "5123" },
        token { token_type::SEMI_COLON, 0, 4 },
        token { token_type::END_OF_FILE, 0, 0 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeExpression>(statment.statment));

    NodeExpression expression = std::get<NodeExpression>(statment.statment);

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralInteger>(literal.literal));

    NodeLiteralInteger literal_integer = std::get<NodeLiteralInteger>(literal.literal);

    EXPECT_EQ(literal_integer.value, 5123);
}

TEST(TestParser, TestExpressionLiteralFloat) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::FLOAT_LITERAL, 0, 0, "5123.1234" },
        token { token_type::SEMI_COLON, 0, 4 },
        token { token_type::END_OF_FILE, 0, 0 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeExpression>(statment.statment));

    NodeExpression expression = std::get<NodeExpression>(statment.statment);

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralFloat>(literal.literal));

    NodeLiteralFloat literal_float = std::get<NodeLiteralFloat>(literal.literal);

    EXPECT_EQ(literal_float.value, 5123.1234f);
}

TEST(TestParser, TestExpressionAssigmentIdentEqExprLiteralInteger) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::IDENTIFIER, 0, 0, "var1" },
        token { token_type::ASSIGN, 0, 4 },
        token { token_type::INTEGER_LITERAL, 0, 5, "5123" },
        token { token_type::SEMI_COLON, 0, 9 },
        token { token_type::END_OF_FILE, 0, 9 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeAssigment>(statment.statment));

    NodeAssigment assigment = std::get<NodeAssigment>(statment.statment);

    NodeIdentifier identifier = assigment.identifier;

    EXPECT_EQ(identifier.name, "var1");

    NodeExpression expression = assigment.assigment;

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralInteger>(literal.literal));

    NodeLiteralInteger literal_integer = std::get<NodeLiteralInteger>(literal.literal);

    EXPECT_EQ(literal_integer.value, 5123);
}

TEST(TestParser, TestExpressionAssigmentIdentEqExprLiteralFloat) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::IDENTIFIER, 0, 0, "var1" },
        token { token_type::ASSIGN, 0, 4 },
        token { token_type::FLOAT_LITERAL, 0, 5, "5123.1234" },
        token { token_type::SEMI_COLON, 0, 14 },
        token { token_type::END_OF_FILE, 0, 14 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeAssigment>(statment.statment));

    NodeAssigment assigment = std::get<NodeAssigment>(statment.statment);

    NodeIdentifier identifier = assigment.identifier;

    EXPECT_EQ(identifier.name, "var1");

    NodeExpression expression = assigment.assigment;

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralFloat>(literal.literal));

    NodeLiteralFloat literal_float = std::get<NodeLiteralFloat>(literal.literal);

    EXPECT_EQ(literal_float.value, 5123.1234f);
}

TEST(TestParser, TestExpressionAssigmentIdentEqExprLiteralString) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::IDENTIFIER, 0, 0, "var1" },
        token { token_type::ASSIGN, 0, 4 },
        token { token_type::STRING_LITERAL, 0, 5, "hello world" },
        token { token_type::SEMI_COLON, 0, 17 },
        token { token_type::END_OF_FILE, 0, 17 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeAssigment>(statment.statment));

    NodeAssigment assigment = std::get<NodeAssigment>(statment.statment);

    NodeIdentifier identifier = assigment.identifier;

    EXPECT_EQ(identifier.name, "var1");

    NodeExpression expression = assigment.assigment;

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralString>(literal.literal));

    NodeLiteralString literal_string = std::get<NodeLiteralString>(literal.literal);

    EXPECT_EQ(literal_string.value, "hello world");
}

TEST(TestParser, TestExpressionAssigmentIdentEqExprLiteralBooleanTrue) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::IDENTIFIER, 0, 0, "var1" },
        token { token_type::ASSIGN, 0, 4 },
        token { token_type::BOOLEAN_LITERAL, 0, 5, "true"},
        token { token_type::SEMI_COLON, 0, 9 },
        token { token_type::END_OF_FILE, 0, 9 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeAssigment>(statment.statment));

    NodeAssigment assigment = std::get<NodeAssigment>(statment.statment);

    NodeIdentifier identifier = assigment.identifier;

    EXPECT_EQ(identifier.name, "var1");

    NodeExpression expression = assigment.assigment;

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralBoolean>(literal.literal));

    NodeLiteralBoolean literal_boolean = std::get<NodeLiteralBoolean>(literal.literal);

    EXPECT_EQ(literal_boolean.value, true);
}

TEST(TestParser, TestExpressionAssigmentIdentEqExprLiteralBooleanFalse) {
    std::vector<token> tokens = {
        token { token_type::START_OF_FILE, 0, 0 },
        token { token_type::IDENTIFIER, 0, 0, "var1" },
        token { token_type::ASSIGN, 0, 4 },
        token { token_type::BOOLEAN_LITERAL, 0, 5, "false"},
        token { token_type::SEMI_COLON, 0, 10 },
        token { token_type::END_OF_FILE, 0, 10 },
    };

    parser p(tokens);

    auto ast = p.parse();

    p.print_errors();

    EXPECT_FALSE(p.has_errors());

    EXPECT_TRUE(ast.has_value());

    NodeProgram program = ast.value();

    EXPECT_EQ(program.scope.statments.size(), 1);

    NodeStatment statment = program.scope.statments[0];

    EXPECT_TRUE(std::holds_alternative<NodeAssigment>(statment.statment));

    NodeAssigment assigment = std::get<NodeAssigment>(statment.statment);

    NodeIdentifier identifier = assigment.identifier;

    EXPECT_EQ(identifier.name, "var1");

    NodeExpression expression = assigment.assigment;

    EXPECT_TRUE(std::holds_alternative<NodeLiteral>(expression.expressions));

    NodeLiteral literal = std::get<NodeLiteral>(expression.expressions);

    EXPECT_TRUE(std::holds_alternative<NodeLiteralBoolean>(literal.literal));

    NodeLiteralBoolean literal_boolean = std::get<NodeLiteralBoolean>(literal.literal);

    EXPECT_EQ(literal_boolean.value, false);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
