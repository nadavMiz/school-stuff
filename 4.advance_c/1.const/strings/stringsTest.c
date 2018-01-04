#include <stdio.h>
#include <string.h>
#include "strings.h"

#define TEST_STRING "blipBloopTest"
#define TEST_STRING_LEN 13

typedef enum 
{
	PASSED,
	FAILED
} Result;

/*******************helper functions******************/

void PrintTest(Result _result, char* _testName)
{
	if(PASSED == _result)
	{
		printf("PASSED %s\n", _testName);
	}
	else if(FAILED == _result)
	{
		printf("FAILED %s\n", _testName);
	}
}

/*-----------main test functions-------------*/


void TestStrLenNormal()
{
	char testName[30] = "strlen normal";
	if(StrLen(TEST_STRING) == TEST_STRING_LEN)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrLenRecNormal()
{
	char testName[30] = "strlen recursive normal";
	if(StrLenRec(TEST_STRING) == TEST_STRING_LEN)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}
void TestStrCompareNormal()
{
	char testName[30] = "strcmp normal";
	char str1[30] = "blipBloop";
	char str2[30] = "blipBlooabg";
	if(0 != StrCompare(str1, TEST_STRING) && 0 == StrCompare(TEST_STRING, TEST_STRING) && 0 > StrCompare(str2, TEST_STRING))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrCompareRecNormal()
{
	char testName[30] = "strcmp recursive normal";
	char str1[30] = "blipBloop";
	char str2[30] = "blipBlooabg";
	if(0 != StrCompareRec(str1, TEST_STRING) && 0 == StrCompareRec(TEST_STRING, TEST_STRING) && 0 > StrCompareRec(str2, TEST_STRING))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrCopyNormal()
{
	char testName[30] = "strcpy normal";
	char str1[30] = "BlipBloop";
	StrCopy(str1, TEST_STRING);
	if(0 == StrCompare(str1, TEST_STRING))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrCopyRecNormal()
{
	char testName[30] = "strcpy recursive normal";
	char str1[30] = "BlipBloop";
	StrCopyRec(str1, TEST_STRING);
	if(0 == StrCompare(str1, TEST_STRING))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrNCopyNormal()
{
	char testName[30] = "strncpy normal";
	char str2[30] = "BlipBloopTest";
	char str1[30] = "BloopBlip";
	char str3[30];
	StrNCopy(str2, str1, 5);
	StrNCopy(str3, str1, 15);
	if(0 == StrCompare(str2, "BlooploopTest") && 0 == StrCompare(str3, str1))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrNCopyRecNormal()
{
	char testName[30] = "strncpy recursive normal";
	char str2[30] = "BlipBloopTest";
	char str1[30] = "BloopBlip";
	char str3[30];
	StrNCopyRec(str2, str1, 5);
	StrNCopyRec(str3, str1, 15);
	if(0 == StrCompare(str2, "BlooploopTest") && 0 == StrCompare(str3, str1))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}
void TestStrConcatNormal()
{
	char testName[30] = "strConcat normal";
	char str2[30] = "BlipBloop";
	char str1[30] = "Test";
	StrConcat(str2, str1);
	if(0 == StrCompare(str2, "BlipBloopTest"))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrSubStringNormal()
{
	char testName[30] = "strtr normal";
	char *result1, *result2, *result3;
	result1 = StrSubString(TEST_STRING, "blip");
	result2 = StrSubString(TEST_STRING, "Bloop");
	result3 = StrSubString(TEST_STRING, "Blip");
	if(0 == strncmp(result1, "blip", 4) && 0 == strncmp(result2, "Bloop", 5) && NULL == result3)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrLenEmpty()
{
	char testName[30] = "strlen empty";
	char empty = '\0';
	if(StrLen(&empty) == 0)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrLenRecEmpty()
{
	char testName[30] = "strlen recursive empty";
	char empty = '\0';
	if(StrLenRec(&empty) == 0)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrLenNull()
{
	char testName[30] = "strlen NULL";
	if(StrLen(NULL) == 0)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrLenRecNull()
{
	char testName[30] = "strlen recursive NULL";
	if(StrLenRec(NULL) == 0)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrCopyNull()
{
	char testName[30] = "strcpy NULL";
	char str1[30] = "BlipBloop";
	char str2[30] = "fdg";
	StrCopy(str1, NULL);
	StrCopy(NULL, str2);
	if(NULL == str1)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrCopyRecNull()
{
	char testName[30] = "strcpy recursive NULL";
	char str1[30] = "BlipBloop";
	char str2[30] = "fdg";
	StrCopyRec(str1, NULL);
	StrCopyRec(NULL, str2);
	if(NULL == str1)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrNCopyNull()
{
	char testName[30] = "strncpy NULL";
	char str1[30] = "BlipBloop";
	char str2[30] = "fdg";
	StrNCopy(str1, NULL, 15);
	StrNCopy(NULL, str2, 15);
	if(0 == StrCompare(str1, "BlipBloop"))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrNCopyRecNull()
{
	char testName[30] = "strncpy recursive NULL";
	char str1[30] = "BlipBloop";
	char str2[30] = "fdg";
	StrNCopyRec(str1, NULL, 15);
	StrNCopyRec(NULL, str2, 15);
	if(0 == StrCompare(str1, "BlipBloop"))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrConcatNull()
{
	char testName[30] = "strConcat NULL";
	char str1[30] = "BlipBloop";
	char str2[30] = "fdg";
	StrConcat(str1, NULL);
	StrConcat(NULL, str2);
	if(0 == StrCompare(str1, "BlipBloop"))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestStrSubStringNull()
{
	char testName[30] = "strstr NULL";
	char str1[30] = "BlipBloop";
	char* result1;
	char* result2;
	result1 = StrSubString(str1, NULL);
	result2 = StrSubString(NULL, str1);
	if(NULL == result1 && NULL == result2)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

int main()
{
	/* normal tests :) */
	TestStrLenNormal();
	TestStrLenRecNormal();
	TestStrCompareNormal();
	TestStrCompareRecNormal();
	TestStrCopyNormal();
	TestStrCopyRecNormal();
	TestStrNCopyNormal();
	TestStrNCopyRecNormal();
	TestStrConcatNormal();
	TestStrSubStringNormal();
	
	/* extreme tests ;> */
	TestStrLenEmpty();
	TestStrLenNull();
	TestStrLenRecEmpty();
	TestStrLenRecNull();
	TestStrNCopyNull();
	TestStrNCopyRecNull();
	TestStrConcatNull();
	TestStrSubStringNull();
	
	
	return 1;
}
