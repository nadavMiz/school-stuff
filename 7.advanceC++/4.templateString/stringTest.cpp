#include "mu_test.h"
#include "String_t.h"
#include "myStrBoost.h"

#include <string.h> // strcmp, strcpy
#include <wchar.h>
#include <cstdlib> // mbstowcs
#include <stdexcept>
#include <iostream>
#include <stdio.h>

using namespace advcpp;


/* ============================= 	*/
/*			char tests				*/
/* ============================= 	*/	
UNIT(DEF_CTOR_char)
	String_t<char> createdString_t;
	
	ASSERT_THAT(strcmp(createdString_t.c_str(), "") == 0);

END_UNIT
/* ============================= 	*/
UNIT(CTOR_from_char_ptr_char)
	char str[32];
	
	strcpy(str, "like dis");
	String_t<char> string(str);
	
	ASSERT_THAT(strcmp(string.c_str(), "like dis") == 0);
	
	String_t<char> anotherString_t("like dat");
	
	ASSERT_THAT(strcmp(anotherString_t.c_str(), "like dat") == 0);
	
END_UNIT
/* ================================= */
/*UNIT(CTOR_from_null_cp_char)
	
	bool caught = false;
	
	try
	{
		String_t<char> string(0);
	}	
	
	catch (std::invalid_argument)
	{
		caught = true; 
	}
	
	ASSERT_THAT(caught);
	
END_UNIT*/
/* ============================= 	*/
UNIT(copy_CTOR_char)
	String_t<char> first("dis is string");
	
	String_t<char> second(first);
	
	ASSERT_THAT(strcmp(second.c_str(), "dis is string") == 0);
END_UNIT
/* ============================= 	*/
UNIT(Assignment_char)
	String_t<char> first("dis is string");
	
	String_t<char> second;
	
	second = first;
	
	ASSERT_THAT(strcmp(second.c_str(), "dis is string") == 0);
	
	second = "and now?";
	
	ASSERT_THAT(strcmp(second.c_str(), "and now?") == 0);
END_UNIT
/* ============================= 	*/
UNIT(Length_char)
	String_t<char> str;
	
	ASSERT_THAT(str.Length() == 0);
	
	str = "STRING WITH 20 CHARS";
	
	ASSERT_THAT(str.Length() == 20);
END_UNIT

/* ============================= 	*/	
UNIT(ToUpper_char)
	String_t<char> str("I wan7t tO te~st s8Um StufF=");
	
	ToUpper(str);
	
	ASSERT_THAT(strcmp(str.c_str(), "I WAN7T TO TE~ST S8UM STUFF=") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(ToLower_char)
	String_t<char> str("I wan7t tO te~st s8Um StufF=");
	
	ToLower(str);
	
	std::cout << str << std::endl;
	ASSERT_THAT(strcmp(str.c_str(), "i wan7t to te~st s8um stuff=") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(plus_char_ptr_char)
	String_t<char> str("we comple");
	
	str = str + "te each other";
	
	ASSERT_THAT(strcmp(str.c_str(), "we complete each other") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(plus_String_t_char)
	String_t<char> beg("we comple");
	String_t<char> end("te each other");
	
	beg = beg + end;
	
	ASSERT_THAT(strcmp(beg.c_str(), "we complete each other") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(Comparators_char)
	String_t<char> string("string");
	String_t<char> Identical("string");
	String_t<char> Different("different");
	
	ASSERT_THAT(string == Identical);
	ASSERT_THAT(string != Different);
	ASSERT_THAT(!(string != Identical));
	ASSERT_THAT(!(string == Different));
	ASSERT_THAT(string == "string");
	ASSERT_THAT(string != "not");
	ASSERT_THAT(!(string == "not"));
	ASSERT_THAT(!(string != "string"));	
	
END_UNIT

/* ============================= 	*/	
UNIT(GetIndexth_char)
	unsigned int i;
	String_t<char> str("0123456789");
	
	for (i = 0; i < str.Length(); i += 1)
	{
		ASSERT_THAT(str[i] == (int)i + '0');
	}
	
END_UNIT
/* ================================= */
UNIT(GetIndexthOutOfBound_char)

	bool caught = false;
	
	String_t<char> tenDigits("0123456789");
	
	try
	{
		tenDigits[10];
	}
	
	catch(std::out_of_range)
	{
		caught = true;
	}
	
	ASSERT_THAT(caught);
	
END_UNIT

/* ================================= */
/*			wchar_t TESTS			 */
/* ================================= */

// auxilliary function
wchar_t* CreateWString(const char* cp)
{
	unsigned int length = strlen(cp) + 1;
	wchar_t* wString = new wchar_t[length];
	mbstowcs(wString, cp, length);
	
	return wString;
}

UNIT(DEF_CTOR_wchar_t)
	String_t<wchar_t> createdString_t;
	
	wchar_t* empty = CreateWString("");
	
	ASSERT_THAT(wcscmp(createdString_t.c_str(), empty) == 0);
	
	delete [] empty;

END_UNIT
/* ============================= 	*/
UNIT(CTOR_from_char_ptr_wchar_t)
	wchar_t* wString =  CreateWString("like dis");
	
	String_t<wchar_t> string(wString);
	
	ASSERT_THAT(wcscmp(string.c_str(), wString) == 0);
		
	delete [] wString;
	
END_UNIT
/* ================================= */
/*UNIT(CTOR_from_null_cp_wchar_t)
	
	bool caught = false;
	
	try
	{
		String_t<wchar_t> string(0);
	}	
	
	catch (std::invalid_argument)
	{
		caught = true; 
	}
	
	ASSERT_THAT(caught);
	
END_UNIT*/
/* ============================= 	*/
UNIT(copy_CTOR_wchar_t)

	wchar_t* wString =  CreateWString("dis is string");
	
	String_t<wchar_t> first(wString);
	
	String_t<wchar_t> second(first);
	
	ASSERT_THAT(wcscmp(second.c_str(), wString) == 0);
	
	delete [] wString;
	
END_UNIT
/* ============================= 	*/
UNIT(Assignment_wchar_t)

	wchar_t* wString =  CreateWString("dis is string");
	
	String_t<wchar_t> first(wString);
	
	String_t<wchar_t> second;
	
	second = first;
	
	ASSERT_THAT(wcscmp(second.c_str(), wString) == 0);
	
	delete [] wString;
	
END_UNIT
/* ============================= 	*/
UNIT(Length_wchar_t)
	
	wchar_t* wString =  CreateWString("STRING WITH 20 CHARS");
	
	String_t<wchar_t> str;
	
	ASSERT_THAT(str.Length() == 0);
	
	str = wString;
	
	ASSERT_THAT(str.Length() == 20);
	
	delete[] wString;
	
END_UNIT

/* ============================= 	*/	
UNIT(ToUpper_wchar_t)
	
	wchar_t* wString =  CreateWString("I wan7t tO te~st s8Um StufF=");
	wchar_t* wUpper = CreateWString("I WAN7T TO TE~ST S8UM STUFF=");
	
	String_t<wchar_t> str(wString);
	
	ToUpper(str);
	
	ASSERT_THAT(wcscmp(str.c_str(), wUpper) == 0);
	
	delete[] wString;
	delete[] wUpper;
	
END_UNIT
/* ============================= 	*/	
UNIT(ToLower_wchar_t)

	wchar_t* wString =  CreateWString("I wan7t tO te~st s8Um StufF=");
	wchar_t* wUpper = CreateWString("i wan7t to te~st s8um stuff=");
	
	String_t<wchar_t> str(wString);
	
	ToLower(str);
	
	ASSERT_THAT(wcscmp(str.c_str(), wUpper) == 0);
	
	delete[] wString;
	delete[] wUpper;
	
END_UNIT
/* ============================= 	*/	
UNIT(plus_char_ptr_wchar_t)

	wchar_t* one =  CreateWString("we comple");
	wchar_t* two =  CreateWString("te each other");
	wchar_t* res = CreateWString("we complete each other");
	
	String_t<wchar_t> str(one);
	
	str = str + two;
	
	ASSERT_THAT(wcscmp(str.c_str(), res) == 0);
	
	delete[] one;
	delete[] two;
	delete[] res;
	
END_UNIT
/* ============================= 	*/	
UNIT(plus_String_t_wchar_t)

	wchar_t* one =  CreateWString("we comple");
	wchar_t* two =  CreateWString("te each other");
	wchar_t* res = CreateWString("we complete each other");
	
	String_t<wchar_t> beg(one);
	String_t<wchar_t> end(two);
	
	beg = beg + end;
	
	ASSERT_THAT(wcscmp(beg.c_str(), res) == 0);
	
	delete[] one;
	delete[] two;
	delete[] res;
	
END_UNIT
/* ============================= 	*/	
UNIT(Comparators_wchar_t)
	
	wchar_t* Wstring =  CreateWString("string");
	wchar_t* WIdentical =  CreateWString("string");
	wchar_t* WDifferent = CreateWString("different");
	
	String_t<wchar_t> string(Wstring);
	String_t<wchar_t> Identical(WIdentical);
	String_t<wchar_t> Different(WDifferent);
	
	ASSERT_THAT(string == Identical);
	ASSERT_THAT(string != Different);
	ASSERT_THAT(!(string != Identical));
	ASSERT_THAT(!(string == Different));
	
	delete[] Wstring;
	delete[] WIdentical;
	delete[] WDifferent;
	
END_UNIT


/* ================================= */
UNIT(GetIndexthOutOfBound_wchar_t)

	bool caught = false;
	wchar_t* digits = CreateWString("0123456789");
	
	String_t<wchar_t> tenDigits(digits);
	
	try
	{
		tenDigits[10];
	}
	
	catch(std::out_of_range)
	{
		caught = true;
	}
	
	ASSERT_THAT(caught);
	
	delete[] digits;
	
END_UNIT

/* =================================*/
/*			print tests				*/
/* ================================= */
UNIT(print_char)
	String_t<char> str("(char) IS DIS PRINTING??");
	
	std::cout << str << std::endl;
	
END_UNIT

UNIT(print_wchar_t)
	
	wchar_t* wStr =  CreateWString("(wchar_t) IS DIS PRINTING??");
	
	String_t<wchar_t> str(wStr);
	
	std::wcout << str << std::endl;
END_UNIT


/* ============================= 	*/
/*			TEST SUIT				*/
/* ============================= 	*/	

TEST_SUITE(String_t)
	TEST(DEF_CTOR_char)
	TEST(CTOR_from_char_ptr_char)
	/*TEST(CTOR_from_null_cp_char)*/
	TEST(copy_CTOR_char)
	TEST(Assignment_char)
	TEST(Length_char)
	TEST(ToUpper_char)
	TEST(ToLower_char)
	TEST(plus_char_ptr_char)
	TEST(plus_String_t_char)
	TEST(Comparators_char)
	TEST(GetIndexth_char)
	TEST(GetIndexthOutOfBound_char)
	
	TEST(DEF_CTOR_wchar_t)
	TEST(CTOR_from_char_ptr_wchar_t)
	//TEST(CTOR_from_null_cp_wchar_t)
	TEST(copy_CTOR_wchar_t)
	TEST(Assignment_wchar_t)
	TEST(Length_wchar_t)
	TEST(ToUpper_wchar_t)
	TEST(ToLower_wchar_t)
	TEST(plus_char_ptr_wchar_t)
	TEST(plus_String_t_wchar_t)
	TEST(Comparators_wchar_t)
	TEST(GetIndexthOutOfBound_wchar_t)
	
	TEST(print_char)
	TEST(print_wchar_t)
END_SUITE
