#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



class Assert {

    //region NUMERIC
    public: static void equals(long int expected, long int actual, const std::string& label) {
        if (expected==actual) return;
        std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << ".\n\n";
        exit(1);
    }

    public: static void equalsUnsigned(unsigned long int expected, unsigned long int actual, const std::string& label) {
            if (expected==actual) return;
            std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << ".\n\n";
            exit(1);
        }

    public: static void equals(double expected, double actual, double tolerance, const std::string& label) {
        if (abs(expected-actual)<tolerance) return;
        std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
        exit(1);
    }
    //endregion




    //region TEXT RELATED
    public: static void equals(const std::string& expected, const std::string& actual, const std::string& label) {
        if (expected==actual) return;
        std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
    	exit(1);
    }

    public: static void charEquals(char expected, char actual, const std::string& label) {
        if (expected==actual) return;
        std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
    	exit(1);
    }
    //endregion




    //region BOOLEANS
    public: static void that(char cond, const std::string& label) {
    	if (cond) return;
    	std::cout << "\n\n"<< label << "\n\tAssert true failed.\n\n";
    	exit(1);
    }

    public: static void thatNot(char cond, const std::string& label) {
    	if (!cond) return;
    	std::cout << "\n\n"<< label << "\n\tAssert false failed.\n\n";
    	exit(1);
    }
    //endregion




    //region POINTERS
    public: static void equals(void* expected, void* actual, const std::string& label) {
    	if (expected==actual) return;
    	std::cout << "\n\n"<< label << "\n\tAssert equals pointers failed.\n\n";
    	exit(1);
    }

    public: static void null(void* ptr, const std::string& label) {
    	if (ptr==0) return;
    	std::cout << "\n\n"<< label << "\n\tAssert null failed.\n\n";
    	exit(1);
    }

    public: static void notNull(void* ptr, const std::string& label) {
    	if (ptr!=0) return;
    	std::cout << "\n\n"<< label << "\n\tAssert not null failed.\n\n";
    	exit(1);
    }
    //endregion
};









