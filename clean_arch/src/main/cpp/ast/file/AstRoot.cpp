#include "AstRoot.h"

using namespace std;

AstRoot::AstRoot(string& name, list<unique_ptr<const EulStatement>> statements) :
	name(name),
	statements(move(statements)) {}
