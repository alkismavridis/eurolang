#pragma once
#include <string>
#include <iostream>

class UnitTest {
	private: const std::string displayName;
	private: std::string currentCaseName;

	public: UnitTest(const std::string& tn);
	public: virtual ~UnitTest() {}

	//SECTION GETTERS
	public: const std::string getName() const;
	const std::string getCurrentTestName() const;
	const std::string getCurrentTestFullName() const;


	//SECTION CHAINING
	UnitTest* logStart();
	UnitTest* run(const std::string testName, void (testCallback)(UnitTest*));
	UnitTest* todo(const std::string& message);


	//SECTION RUNNING
	virtual void runAll() = 0;
};
