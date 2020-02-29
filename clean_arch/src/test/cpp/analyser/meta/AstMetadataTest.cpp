#include "ast/values/BooleanNode.h"

#include "analyser/model/meta/AstMetadata.h"
#include "analyser/model/meta/ValueTypeAlreadySetException.h"
#include "analyser/model/meta/ValueTypeNotSetException.h"
#include "analyser/model/types/AnyType.h"

#include "test_utils/Assert.h"

#include "AstMetadataTest.h"



using namespace std;



//SECTION UTILS
struct TypeThatCountsDestructors : public EulType {
	int* const counter;

	 TypeThatCountsDestructors(int* counter) : counter(counter) {}
	 ~TypeThatCountsDestructors() {
		 (*counter)++;
	 }
};


//SECTION TESTS
void hasErrorsShouldReturnFalseIfNoErrorsExist(UnitTest* t) {
	AstMetadata meta(nullptr);
	Assert::thatNot(meta.hasErrors(), t, "1");
}

void hasErrorsShouldReturnTrueIfErrorsExist(UnitTest* t) {
	AstMetadata meta(nullptr);
	meta.addError(EulException("foo", "bar", AstLocation(2, 3)));
	Assert::that(meta.hasErrors(), t, "1");
}

void getTypeFor_shouldReturnExistingType(UnitTest* t) {
	AstMetadata meta(nullptr);
	BooleanNode node(true, AstLocation(5,5));
	AnyType anyType;
	meta.putType(&node, &anyType);

	const EulType* result = meta.getTypeFor(&node);
	Assert::same(result, &anyType, t, "1");
}

void getTypeFor_shouldReturnNullForNonExistingType(UnitTest* t) {
	AstMetadata meta(nullptr);
	BooleanNode node(true, AstLocation(5,5));
	const EulType* type = meta.getTypeFor(&node);
	Assert::null(type, t, "1");
}

void getTypeFor_shouldThrowExceptionOnDuplicatePut(UnitTest* t) {
	AstMetadata meta(nullptr);
	BooleanNode node(true, AstLocation(5,6));
	AnyType anyType;
	meta.putType(&node, &anyType);

	auto result = Assert::throws<ValueTypeAlreadySetException>(
		[&]()-> void { meta.putType(&node, &anyType); },
		t,
		"1"
	);
	Assert::equals(result.message, "PutType failed. Type already set.", t, "2");
	Assert::equals(result.location.line, 5, t, "3");
	Assert::equals(result.location.row, 6, t, "4");
}

void requireTypeFor_shouldThrowExceptionIfTypeDoesNotExists(UnitTest* t) {
	AstMetadata meta(nullptr);
	BooleanNode node(true, AstLocation(5,6));

	auto result = Assert::throws<ValueTypeNotSetException>(
		[&]()-> void { meta.requireTypeFor(&node); },
		t,
		"1"
	);
	Assert::equals(result.message, "RequiredType not present.", t, "2");
	Assert::equals(result.location.line, 5, t, "3");
	Assert::equals(result.location.row, 6, t, "4");
}

void requireTypeFor_shouldReturnExistingType(UnitTest* t) {
	AstMetadata meta(nullptr);
	BooleanNode node(true, AstLocation(5,5));
	AnyType anyType;
	meta.putType(&node, &anyType);

	const EulType* result = meta.requireTypeFor(&node);
	Assert::same(result, &anyType, t, "1");
}

void putAndOwnType_shouldPutTypeInMap(UnitTest* t) {
	AstMetadata meta(nullptr);
	BooleanNode node(true, AstLocation(5,5));
	auto anyType = make_unique<AnyType>();
	auto anyTypePtr = anyType.get();
	meta.putAndOwnType(&node, move(anyType));

	const EulType* result = meta.requireTypeFor(&node);
	Assert::same(result, anyTypePtr, t, "1");
}

void putAndOwnType_shouldDeallocateMemory(UnitTest* t) {
	unique_ptr<AstMetadata> meta = make_unique<AstMetadata>(nullptr);
	BooleanNode node(true, AstLocation(5,5));
	int counter = 0;
	auto destructorCountingType = make_unique<TypeThatCountsDestructors>(&counter);
	meta->putAndOwnType(&node, move(destructorCountingType));

	//delete the metadata. destructorCountingType should also be deleted
	meta = nullptr;
	Assert::equals(counter, 1, t, "1");
}


void AstMetadataTest::runAll() {
	this
		->logStart()
		->run("hasErrorsShouldReturnFalseIfNoErrorsExist", hasErrorsShouldReturnFalseIfNoErrorsExist)
		->run("hasErrorsShouldReturnTrueIfErrorsExist", hasErrorsShouldReturnTrueIfErrorsExist)

		->run("getTypeFor_shouldReturnExistingType", getTypeFor_shouldReturnExistingType)
		->run("getTypeFor_shouldReturnNullForNonExistingType", getTypeFor_shouldReturnNullForNonExistingType)
		->run("getTypeFor_shouldThrowExceptionOnDuplicatePut", getTypeFor_shouldThrowExceptionOnDuplicatePut)

		->run("requireTypeFor_shouldThrowExceptionIfTypeDoesNotExists", requireTypeFor_shouldThrowExceptionIfTypeDoesNotExists)
		->run("requireTypeFor_shouldReturnExistingType", requireTypeFor_shouldReturnExistingType)
		->run("putAndOwnType_shouldPutTypeInMap", putAndOwnType_shouldPutTypeInMap)
		->run("putAndOwnType_shouldDeallocateMemory", putAndOwnType_shouldDeallocateMemory)
		;
}
