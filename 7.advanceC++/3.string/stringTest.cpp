#include "mu_test.h"
#include "String_t.h"
#include <string.h> // strcmp, strcpy
#include <stdio.h>

using namespace advcpp;

/* ============================= 	*/
/*				TESTS				*/
/* ============================= 	*/	
UNIT(DEF_CTOR)
	String_t createdString_t;
	
	ASSERT_THAT(strcmp(createdString_t.c_str(), "") == 0);

END_UNIT
/* ============================= 	*/
UNIT(CTOR_from_char_ptr)
	char str[32];
	
	strcpy(str, "like dis");
	String_t string(str);
	
	ASSERT_THAT(strcmp(string.c_str(), "like dis") == 0);
	
	String_t anotherString_t("like dat");
	
	ASSERT_THAT(strcmp(anotherString_t.c_str(), "like dat") == 0);
	
END_UNIT
/* ================================= */
/*UNIT(CTOR_from_null_cp)
	
	bool caught = false;
	
	try
	{
		String_t string(0);
	}	
	
	catch (std::invalid_argument)
	{
		caught = true; 
	}
	
	ASSERT_THAT(caught);
	
END_UNIT*/
/* ============================= 	*/
UNIT(copy_CTOR)
	String_t first("dis is string");
	
	String_t second(first);
	
	ASSERT_THAT(strcmp(second.c_str(), "dis is string") == 0);
END_UNIT
/* ============================= 	*/
UNIT(Assignment)
	String_t first("dis is string");
	
	String_t second;
	
	second = first;
	
	ASSERT_THAT(strcmp(second.c_str(), "dis is string") == 0);
	
	second = "and now?";
	
	ASSERT_THAT(strcmp(second.c_str(), "and now?") == 0);
END_UNIT
/* ============================= 	*/
UNIT(Length)
	String_t str;
	
	ASSERT_THAT(str.Length() == 0);
	
	str = "STRING WITH 20 CHARS";
	
	ASSERT_THAT(str.Length() == 20);
END_UNIT

/* ============================= 	*/	
UNIT(ToUpper)
	String_t str("I wan7t tO te~st s8Um StufF=");
	
	str.ToUpper();
	
	ASSERT_THAT(strcmp(str.c_str(), "I WAN7T TO TE~ST S8UM STUFF=") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(ToLower)
	String_t str("I wan7t tO te~st s8Um StufF=");
	
	str.ToLower();
	
	ASSERT_THAT(strcmp(str.c_str(), "i wan7t to te~st s8um stuff=") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(plus_char_ptr)
	String_t str("we comple");
	
	str = str + "te each other";
	
	ASSERT_THAT(strcmp(str.c_str(), "we complete each other") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(plus_String_t)
	String_t beg("we comple");
	String_t end("te each other");
	
	beg = beg + end;
	
	ASSERT_THAT(strcmp(beg.c_str(), "we complete each other") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(Comparators)
	String_t string("string");
	String_t Identical("string");
	String_t Different("different");
	
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
UNIT(GetIndexth)
	unsigned int i;
	String_t str("0123456789");
	
	for (i = 0; i < str.Length(); i += 1)
	{
		ASSERT_THAT(str[i] == (int)i + '0');
	}
	
END_UNIT
/* ================================= */
UNIT(GetIndexthOutOfBound)

	bool caught = false;
	
	String_t tenDigits("0123456789");
	
	try
	{
		tenDigits[10];
	}
	
	catch(std::out_of_range&)
	{
		caught = true;
	}
	
	ASSERT_THAT(caught);
	
END_UNIT
/* ============================= 	*/
/*			TEST SUIT				*/
/* ============================= 	*/	

TEST_SUITE(String_t)
	TEST(DEF_CTOR)
	TEST(CTOR_from_char_ptr)
	/*TEST(CTOR_from_null_cp)*/
	TEST(copy_CTOR)
	TEST(Assignment)
	TEST(Length)
	TEST(ToUpper)
	TEST(ToLower)
	TEST(plus_char_ptr)
	TEST(plus_String_t)
	TEST(Comparators)
	TEST(GetIndexth)
	TEST(GetIndexthOutOfBound)
END_SUITE
