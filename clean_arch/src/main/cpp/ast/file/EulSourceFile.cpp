#include "EulSourceFile.h"

using namespace std;

EulSourceFile::EulSourceFile(string& name, list<unique_ptr<const EulStatement>> statements) :
  name(name),
  statements(move(statements)) {}
