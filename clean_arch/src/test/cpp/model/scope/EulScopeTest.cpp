#include <memory>

#include "model/ast/values/BooleanNode.h"
#include "model/ast/statements/SymbolChangeType.h"
#include "model/types/AnyType.h"

#include "model/scope/EulScope.h"
#include "model/scope/VariableAlreadyDeclaredException.h"

#include "test_utils/Assert.h"
#include "EulScopeTest.h"

using namespace std;


//SECTION TESTS

//tests for get()
void getShouldReturnExistingSymbol(UnitTest* t) {
	auto scope = make_unique<EulScope>(nullptr);
	AnyType type1;
	AnyType type2;
	BooleanNode value1(true, AstLocation(1, 1));
	BooleanNode value2(true, AstLocation(2, 1));

	scope->declareSymbol(SymbolChangeType::VAR, "first", &type1, &value1, AstLocation(1,2));
	scope->declareSymbol(SymbolChangeType::VAL, "second", &type2, &value2, AstLocation(20,30));

	Assert::equals((long)SymbolChangeType::VAR, (long)scope->getSymbol("first")->changeType, t, "changeType1");
	Assert::equals((long)SymbolChangeType::VAL, (long)scope->getSymbol("second")->changeType, t, "changeType2");

	Assert::same(&type1, scope->getSymbol("first")->varType, t, "varType1");
	Assert::same(&type2, scope->getSymbol("second")->varType, t, "varType2");

	Assert::same(&value1, scope->getSymbol("first")->value, t, "value1");
	Assert::same(&value2, scope->getSymbol("second")->value, t, "value2");

	Assert::same(&value1, scope->getSymbol("first")->value, t, "value1");
	Assert::same(&value2, scope->getSymbol("second")->value, t, "value2");

	Assert::equals(1, scope->getSymbol("first")->location.line, t, "line1");
	Assert::equals(20, scope->getSymbol("second")->location.line, t, "line2");

	Assert::equals(2, scope->getSymbol("first")->location.row, t, "row1");
	Assert::equals(30, scope->getSymbol("second")->location.row, t, "row2");
}

void getShouldReturnNullForNotExistingSymbol(UnitTest* t) {
	auto scope = make_unique<EulScope>(nullptr);
	AnyType type1;
	AnyType type2;
	BooleanNode value1(true, AstLocation(1, 1));
	BooleanNode value2(true, AstLocation(2, 1));

	scope->declareSymbol(SymbolChangeType::VAR, "first", &type1, &value1, AstLocation(1,2));
	scope->declareSymbol(SymbolChangeType::VAL, "second", &type2, &value2, AstLocation(20,30));

	Assert::null(scope->getSymbol("somthingElse"), t, "1");
}

void getShouldReturnSymbolFromParentScope(UnitTest* t) {
	EulScope parent(nullptr);
	EulScope scope(&parent);
	AnyType type1;
	AnyType type2;
	BooleanNode value1(true, AstLocation(1, 1));
	BooleanNode value2(true, AstLocation(2, 1));

	parent.declareSymbol(SymbolChangeType::VAR, "first", &type1, &value1, AstLocation(1,2));
	parent.declareSymbol(SymbolChangeType::VAL, "second", &type2, &value2, AstLocation(20,30));

	Assert::same(&value1, scope.getSymbol("first")->value, t, "1");
	Assert::same(&value2, scope.getSymbol("second")->value, t, "2");
}

void getShouldGivePriorityToSymbolFromChildScope(UnitTest* t) {
	EulScope parent(nullptr);
	EulScope scope(&parent);
	AnyType type1;
	AnyType type2;
	AnyType type3;
	BooleanNode parentValue1(true, AstLocation(1, 1));
	BooleanNode parentValue2(true, AstLocation(2, 1));
	BooleanNode childValue1(true, AstLocation(3, 1));

	parent.declareSymbol(SymbolChangeType::VAR, "first", &type1, &parentValue1, AstLocation(1,2));
	parent.declareSymbol(SymbolChangeType::VAR, "second", &type2, &parentValue2, AstLocation(1,2));
	scope.declareSymbol(SymbolChangeType::VAR, "first", &type3, &childValue1, AstLocation(4, 5));

	Assert::same(&childValue1, scope.getSymbol("first")->value, t, "1");
	Assert::same(&parentValue2, scope.getSymbol("second")->value, t, "2");
}


//tests for declareSymbol()
void declareShouldCreateEntry(UnitTest* t) {
	EulScope scope(nullptr);
	AnyType type;
	BooleanNode value(true, AstLocation(3, 1));

	scope.declareSymbol(SymbolChangeType::VAL, "someSymbol", &type, &value, AstLocation(10,20));

	Assert::equals((long)SymbolChangeType::VAL, (long)scope.getSymbol("someSymbol")->changeType, t, "1");
	Assert::same(&type, scope.getSymbol("someSymbol")->varType, t, "2");
	Assert::same(&value, scope.getSymbol("someSymbol")->value, t, "3");
	Assert::equals(10, scope.getSymbol("someSymbol")->location.line, t, "4");
	Assert::equals(20, scope.getSymbol("someSymbol")->location.row, t, "5");
}

void declareShouldCreateEntryEvenIfItExistsInParentScope(UnitTest* t) {
	auto parent = make_unique<EulScope>(nullptr);
	auto scope = make_unique<EulScope>(parent.get());
	AnyType type1;
	AnyType type2;
	BooleanNode value1(true, AstLocation(1, 1));
	BooleanNode value2(true, AstLocation(2, 1));

	parent->declareSymbol(SymbolChangeType::VAR, "someSymbol", &type1, &value1, AstLocation(1,2));
	scope->declareSymbol(SymbolChangeType::VAL, "someSymbol", &type2, &value2, AstLocation(20,30));

	Assert::same(&value1, parent->getSymbol("someSymbol")->value, t, "1");
	Assert::same(&value2, scope->getSymbol("someSymbol")->value, t, "2");
}

void declareShouldFailIfSymbolExistsInSameScope(UnitTest* t) {
	auto scope = make_unique<EulScope>(nullptr);
	AnyType type1;
	AnyType type2;
	BooleanNode value1(true, AstLocation(1, 1));
	BooleanNode value2(true, AstLocation(2, 1));

	scope->declareSymbol(SymbolChangeType::VAR, "someSymbol", &type1, &value1, AstLocation(11,21));

	auto ex = Assert::throws<VariableAlreadyDeclaredException>(
		[&]()-> void { scope->declareSymbol(SymbolChangeType::VAR, "someSymbol", &type2, &value2, AstLocation(1,2)); },
		t,
		"1"
	);
	Assert::equals("Variable someSymbol is already defined.", ex.message, t, "2");
	Assert::equals(1, ex.location.line, t, "3");
	Assert::equals(2, ex.location.row, t, "4");
	Assert::equals(11, ex.prevDeclarationLoacation.line, t, "5");
	Assert::equals(21, ex.prevDeclarationLoacation.row, t, "6");
}



// glue code
void EulScopeTest::runAll() {
	this
		->logStart()
		->run("getShouldReturnExistingSymbol", getShouldReturnExistingSymbol)
		->run("getShouldReturnNullForNotExistingSymbol", getShouldReturnNullForNotExistingSymbol)
		->run("getShouldReturnSymbolFromParentScope", getShouldReturnSymbolFromParentScope)
		->run("getShouldGivePriorityToSymbolFromChildScope", getShouldGivePriorityToSymbolFromChildScope)

		->run("declareShouldCreateEntry", declareShouldCreateEntry)
		->run("declareShouldCreateEntryEvenIfItExistsInParentScope", declareShouldCreateEntryEvenIfItExistsInParentScope)
		->run("declareShouldFailIfSymbolExistsInSameScope", declareShouldFailIfSymbolExistsInSameScope)
		->todo("test type declaration / getters. Decide if type/value declaration with same keys can coexist.")
		;
}
