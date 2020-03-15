#pragma once

#include "../../test_utils/UnitTest.h"

struct EulCompilerTest : public UnitTest {
	EulCompilerTest() : UnitTest("EulCompilerTest") {}
	void runAll();
};
