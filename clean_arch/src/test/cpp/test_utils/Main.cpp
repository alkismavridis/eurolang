#include <iostream>
#include <vector>
#include <memory>

#include "UnitTest.h"
#include "ast/values/ValuesTest.h"
#include "analyser/scope/EulScopeTest.h"
#include "analyser/meta/AstMetadataTest.h"

using namespace std;

int main() {
	cout << endl << endl << "===== Initializing Eul test suite =====" << endl << endl;

	const vector<shared_ptr<UnitTest>> tests {
		make_shared<ValuesTest>(),
		make_shared<EulScopeTest>(),
		make_shared<AstMetadataTest>(),
	};

	for (shared_ptr<UnitTest> test : tests) {
		test->runAll();
	}

	cout << endl << endl << "===== All Tests succeeded =====" << endl << endl << endl;
}
