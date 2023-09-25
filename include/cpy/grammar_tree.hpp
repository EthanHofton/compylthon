#ifndef __CPY_GRAMMAR_TREE_HPP__
#define __CPY_GRAMMAR_TREE_HPP__

#include <vector>
#include <optional>
#include <string>
#include <variant>
#include <sstream>

namespace cpy {

// program
struct NodeProgram;

// scope
struct NodeScope;

// statment
struct NodeStatment;

// expression
struct NodeExpression;
struct NodeAssigment;

// literals
struct NodeLiteral;
struct NodeLiteralString;
struct NodeLiteralInteger;
struct NodeLiteralFloat;
struct NodeLiteralBoolean;

// identifier
struct NodeIdentifier;

struct NodeLiteralString { std::string value; };
struct NodeLiteralInteger { int value; };
struct NodeLiteralFloat { float value; };
struct NodeLiteralBoolean { bool value; };

struct NodeLiteral { std::variant<NodeLiteralString, NodeLiteralBoolean, NodeLiteralInteger, NodeLiteralFloat> literal; };
struct NodeIdentifier { std::string name; };

struct NodeExpression { std::variant<NodeLiteral, NodeIdentifier> expressions; };
struct NodeAssigment { NodeIdentifier identifier; NodeExpression assigment; };
struct NodeScope { std::vector<NodeStatment> statments; };

struct NodeStatment { std::variant<NodeScope, NodeExpression, NodeAssigment> statment; };
struct NodeProgram { NodeScope scope; };

}

#endif // __CPY_GRAMMAR_TREE_HPP__
