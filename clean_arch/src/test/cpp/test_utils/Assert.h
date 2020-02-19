#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <functional>


#include "UnitTest.h"


struct Assert {
  static void fail(const UnitTest* t, const std::string& message);
  static void equals(long int expected, long int actual, const UnitTest* t, const std::string& label);
  static void equalsUnsigned(unsigned long int expected, unsigned long int actual, const UnitTest* t, const std::string& label);
  static void equals(double expected, double actual, double tolerance, const UnitTest* t, const std::string& label);
  static void equals(const std::string& expected, const std::string& actual, const UnitTest* t, const std::string& label) ;
  static void charEquals(char expected, char actual, const UnitTest* t, const std::string& label);
  static void that(char cond, const UnitTest* t, const std::string& label);
  static void thatNot(char cond, const UnitTest* t, const std::string& label);
  static void same(void* expected, void* actual, const UnitTest* t, const std::string& label);
  static void null(void* ptr, const UnitTest* t, const std::string& label);
  static void notNull(void* ptr, const UnitTest* t, const std::string& label);

  template <typename T>
  static T throws(std::function<void()> callback, UnitTest* t, const std::string& message) {
    try {
      callback();
      Assert::fail(t, message);
      throw ""; //just to keep compiler calm
    }
    catch(T ex) {
      Assert::equals("Variable someSymbol is already defined.", ex.message, t, "2");
      return ex;
    }
  }
};
