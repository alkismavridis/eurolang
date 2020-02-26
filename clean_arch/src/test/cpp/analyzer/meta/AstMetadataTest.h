#pragma once

#include "../../test_utils/UnitTest.h"

struct AstMetadataTest : public UnitTest {
  AstMetadataTest() : UnitTest("AstMetadataTest") {}
  void runAll();
};
