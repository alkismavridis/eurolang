#include "EulStatement.h"
#include "ExpressionStatement.h"
#include "ReturnStatement.h"
#include "VarDeclarationStatement.h"
#include "ConditionalBlock.h"
#include "TypeNode.h"
#include "StatementType.h"


using namespace std;

EulStatement::EulStatement(AstLocation location) : AstNode(location) {}

TypeNode::TypeNode(const string& name, AstLocation location) :
	AstNode(location),
	name(name) {}


ExpressionStatement::ExpressionStatement(unique_ptr<const EulValue> expression, AstLocation location) :
	EulStatement(location),
	expression(move(expression)) {}



ReturnStatement::ReturnStatement(unique_ptr<const EulValue> value, AstLocation location) :
	EulStatement(location),
	value(move(value)) {}


VarDeclarationStatement::VarDeclarationStatement(SymbolChangeType changeType, unique_ptr<const SymbolNameNode> name, AstLocation location) :
	EulStatement(location),
	changeType(changeType),
	name(move(name)),
	value(nullptr) {}

VarDeclarationStatement::VarDeclarationStatement(SymbolChangeType changeType, unique_ptr<const SymbolNameNode> name, unique_ptr<const EulValue> value, AstLocation location) :
	EulStatement(location),
	changeType(changeType),
	name(move(name)),
	value(move(value)) {}


ConditionalBlock::ConditionalBlock(unique_ptr<const EulValue> condition, list<unique_ptr<const EulStatement>> statements, AstLocation location) :
	AstNode(location),
	condition(move(condition)),
	statements(move(statements)) {}
