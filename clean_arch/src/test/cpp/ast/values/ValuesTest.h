#pragma once

#include "test_utils/UnitTest.h"

struct ValuesTest : public UnitTest {
	ValuesTest() : UnitTest("ValuesTest") {}
	void runAll();
};
