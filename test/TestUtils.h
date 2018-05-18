#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//region NUMERIC
void assertIntEquals(long int expected, long int actual, char* majorMessage, char* minorMessage) {
	if (expected==actual) return;
	printf("\n\n%s.%s\n\tExpected:%ld,\n\tFound: %ld.\n\n", majorMessage, minorMessage, expected, actual);
	exit(1);
}

void assertDoubleEquals(double expected, double actual, double tolerance, char* majorMessage, char* minorMessage) {
	const double diff = actual - expected;
	if (diff<tolerance && diff>-tolerance) return;
	printf("\n\n%s.%s\n\tExpected:%f,\n\tFound: %f.\n\tTolerance:%f\n\n", majorMessage, minorMessage, expected, actual, tolerance);
	exit(1);
}
//endregion




//region TEXT RELATED
void assertStringEquals(char* expected, char* actual, char* majorMessage, char* minorMessage) {
	if (strcmp(expected, actual)==0) return;
	printf("\n\n%s.%s\n\tExpected:%s,\n\tFound: %s.\n\n", majorMessage, minorMessage, expected, actual);
	exit(1);
}

void assertCharEquals(char expected, char actual, char* majorMessage, char* minorMessage) {
	if (expected==actual) return;
	printf("\n\n%s.%s\n\tExpected:%c,\n\tFound: %c.\n\n", majorMessage, minorMessage, expected, actual);
	exit(1);
}
//endregion




//region BOOLEANS
void assertTrue(char cond, char* majorMessage, char* minorMessage) {
	if (cond) return;
	printf("\n\n%s.%s\n\tAssert true failed.\n\n", majorMessage, minorMessage);
	exit(1);
}

void assertFalse(char cond, char* majorMessage, char* minorMessage) {
	if (!cond) return;
	printf("\n\n%s.%s\n\tAssert false failed.\n\n", majorMessage, minorMessage);
	exit(1);
}
//endregion




//region POINTERS
void assertPtrEquals(void* expected, void* actual, char* majorMessage, char* minorMessage) {
	if (expected==actual) return;
	printf("\n\n%s.%s\n\tExpected:%p,\n\tFound: %p	.\n\n", majorMessage, minorMessage, expected, actual);
	exit(1);
}

void assertNull(void* ptr, char* majorMessage, char* minorMessage) {
	if (ptr==0) return;
	printf("\n\n%s.%s\n\tExpected:NULL,\n\tFound: %p	.\n\n", majorMessage, minorMessage, ptr);
	exit(1);
}

void assertNotNull(void* ptr, char* majorMessage, char* minorMessage) {
	if (ptr!=0) return;
	printf("\n\n%s.%s\n\tExpected:no null pointer,\n\tFound: NULL	.\n\n", majorMessage, minorMessage);
	exit(1);
}
//endregion
