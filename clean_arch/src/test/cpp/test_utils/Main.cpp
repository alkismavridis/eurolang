#include <iostream>
#include <vector>
#include <memory>

#include "UnitTest.h"
#include "model/scope/EulScopeTest.h"
#include "model/ast_metadata/AstMetadataTest.h"
#include "usecases/compile/EulCompilerTest.h"

using namespace std;

int main() {
	cout << endl << endl << "===== Initializing Eul test suite =====" << endl << endl;

	const vector<shared_ptr<UnitTest>> tests {
		make_shared<EulScopeTest>(),
		make_shared<AstMetadataTest>(),
		make_shared<EulCompilerTest>(),
	};

	for (shared_ptr<UnitTest> test : tests) {
		test->runAll();
	}

	cout << endl << endl << "===== All Tests succeeded =====" << endl << endl << endl;
}
