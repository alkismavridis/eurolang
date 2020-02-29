#include "ast/statements/StatementType.h"
#include "ast/statements/FunctionDeclarationStatement.h"
#include "analyser/model/types/FunctionType.h"

#include "BlockParser.h" //DEPRECATE IT!!!!!!!!
#include "AstAnalyser.h"

using namespace std;





unique_ptr<const AstMetadata> AstAnalyser::analyse(EulScope* const globalScope) {
	//TODO a lot todooooooooooo
	return nullptr;
}

void BlockParser::parseBlock(list<unique_ptr<const EulStatement>>& statements, AstMetadata* meta) {
	return;
}

void BlockParser::preDeclareTypes(list<unique_ptr<const EulStatement>>& statements, AstMetadata* meta) {
	for (auto& statement : statements) {
		const auto statementType = statement->getType();
		if (statementType == StatementType::FUNC_DECLARATION) {
			auto funcDeclaration = static_cast<const FunctionDeclarationStatement*>(statement.get());
			BlockParser::declareTypeFor(funcDeclaration, meta);
		}
	}
}

void BlockParser::declareTypeFor(const FunctionDeclarationStatement* stmt, AstMetadata* meta) {
	try {
		auto typeOfFunction = nullptr; //TODO
		meta->putAndOwnType(stmt->value.get(), move(typeOfFunction));
	}
	catch(EulException& ex) {
		meta->addError(ex);
	}
}


/*
 Responsibilities:
	- Create scopes where is needed
	- Declare symbols in scope (functions, variables, clases)
	- Assign types to every	value (including expressions, functions)


 Error detection:
	- Symbol not found
	- Duplicated symbol declaration
	- Use non-type as type
	- Invalid char size
	- Invalid expression combination.
	- Assignment statement to a const
	- Const definition without a value
*/
