#include <iostream>
#include <bitset> 
#include <iostream>
#include <stdio.h>

#include "mu_test.h"
#include "bitMap.h"

using namespace advcpp;

/*UNIT(DEF_CTOR_char)
	MyBitMap<sizeof(int) * CHAR_BIT + 3, int> bitMap;
	
	std::cout << "should be all 0" << std::endl;
	std::cout << bitMap.GetArray()[0] << " " << bitMap.GetArray()[1] << std::endl;

END_UNIT

UNIT(CTOR_from_bool_array)

	bool boolArr[sizeof(int) * CHAR_BIT + 3];
	std::fill_n(boolArr, sizeof(int) * CHAR_BIT + 3, 1);
	MyBitMap<sizeof(int) * CHAR_BIT + 3, int> bitMap(boolArr);
	
	std::cout << "should be -1 and 7" << std::endl;
	std::cout <<  bitMap.GetArray()[0] << " " << bitMap.GetArray()[1] << std::endl;

END_UNIT*/

UNIT(GetBit)
	std::size_t arrLength = sizeof(std::size_t) * CHAR_BIT + 3;

	bool boolArr[sizeof(std::size_t) * CHAR_BIT + 3] = {0};
	boolArr[1] = 1;

	MyBitMap<sizeof(std::size_t) * CHAR_BIT + 3, std::size_t> bitMap(boolArr);
	
	ASSERT_THAT(1 == bitMap.GetBit(1));
	ASSERT_THAT(0 == bitMap.GetBit(arrLength-1));
	
END_UNIT

UNIT(GetBit_outOfBounds)
	std::size_t arrLength = sizeof(std::size_t) * CHAR_BIT + 3;

	bool boolArr[sizeof(std::size_t) * CHAR_BIT + 3];
	boolArr[1] = 1;

	MyBitMap<sizeof(std::size_t) * CHAR_BIT + 3, std::size_t> bitMap(boolArr);
	
	try
	{
		bitMap.GetBit(arrLength);
		ASSERT_THAT(0);
	}
	catch(const std::overflow_error& _err){}
END_UNIT

UNIT(SetBit)

	MyBitMap<(sizeof(std::size_t) * CHAR_BIT), std::size_t> bitMap;
	
	bitMap.SetBit(0, 1);
	bitMap.SetBit(sizeof(std::size_t) * CHAR_BIT - 1, 1);
	
	ASSERT_THAT(1 == bitMap.GetBit(0));
	ASSERT_THAT(0 == bitMap.GetBit(1));
	ASSERT_THAT(1 == bitMap.GetBit(sizeof(std::size_t) * CHAR_BIT - 1));
END_UNIT

UNIT(SetBit_out_of_bounds)

	MyBitMap<sizeof(std::size_t), std::size_t> bitMap;
	
	try
	{
		bitMap.SetBit(sizeof(std::size_t), 1);
		ASSERT_THAT(0);
	}
	catch(const std::overflow_error& _err){}
END_UNIT

UNIT(copy_CTOR)

	MyBitMap<3> b;
	
	b.SetBit(0, 1);
	b.SetBit(2, 1);
	
	MyBitMap<3> a(b);
	
	ASSERT_THAT(1 == a.GetBit(0));
	ASSERT_THAT(0 == a.GetBit(1));
	ASSERT_THAT(1 == a.GetBit(2));
	
END_UNIT

UNIT(assignment_operator)

	MyBitMap<3> a;
	MyBitMap<3> b;
	
	b.SetBit(0, 1);
	b.SetBit(2, 1);
	
	a = b;
	
	ASSERT_THAT(1 == a.GetBit(0));
	ASSERT_THAT(0 == a.GetBit(1));
	ASSERT_THAT(1 == a.GetBit(2));
	
END_UNIT

UNIT(equal_operator)

	bool boolArr[3] = {1,0,1};
	MyBitMap<3> a(boolArr);
	
	MyBitMap<3> b(a);
	
	ASSERT_THAT(a == b);
	
	b[1] = 1;
	ASSERT_THAT(a != b);
END_UNIT

UNIT(subscript_operator_const)
	bool boolArr[sizeof(std::size_t) * CHAR_BIT + 3] = {0};
	boolArr[0] = 1;

	const MyBitMap<sizeof(std::size_t), std::size_t>* bitMap = new MyBitMap<sizeof(std::size_t), std::size_t>(boolArr);
	
	ASSERT_THAT(1 == (*bitMap)[0]);
	ASSERT_THAT(0 == (*bitMap)[1]);
	
	//out of bounds
	try
	{
		(*bitMap)[sizeof(std::size_t) * CHAR_BIT + 3];
		ASSERT_THAT(0);
	}
	catch(const std::overflow_error& _err){}
	
	delete bitMap;
END_UNIT

UNIT(subscript_operator_non_const)
	MyBitMap<sizeof(std::size_t) * CHAR_BIT, std::size_t> bitMap;
	
	bitMap[1] = bitMap[2] = 1;
	
	ASSERT_THAT(0 == bitMap[0]);
	ASSERT_THAT(1 == bitMap[1]);
	ASSERT_THAT(1 == bitMap[2]);
	
	//out of bounds
	try
	{
		bitMap[sizeof(std::size_t) * CHAR_BIT];
		ASSERT_THAT(0);
	}
	catch(const std::overflow_error& _err){}
END_UNIT

UNIT(Flip)
	MyBitMap<sizeof(std::size_t) * CHAR_BIT + 3, std::size_t> bitMap;
	
	bitMap.Flip(0);
	ASSERT_THAT(1 == bitMap[0]);
	
	bitMap.Flip(0);
	ASSERT_THAT(0 == bitMap[0]);
	ASSERT_THAT(0 == bitMap[1]);
	
	bitMap.Flip(sizeof(std::size_t) * CHAR_BIT);
	ASSERT_THAT(1 == bitMap[sizeof(std::size_t) * CHAR_BIT]);
	
	
	//out of bounds
	try
	{
		bitMap.Flip(sizeof(std::size_t) * CHAR_BIT + 3);
		ASSERT_THAT(0);
	}
	catch(const std::overflow_error& _err){}
END_UNIT

UNIT(All)
	bool boolArr[sizeof(unsigned int) * CHAR_BIT + 3];
	std::fill_n(boolArr, sizeof(unsigned int) * CHAR_BIT + 3, 1);
	MyBitMap<sizeof(unsigned int) * CHAR_BIT + 3, unsigned int> bitMap(boolArr);
	
	ASSERT_THAT(bitMap.All());
	
	bitMap.Flip(0);
	ASSERT_THAT(!bitMap.All());
	
	bitMap.Flip(0);
	bitMap.Flip(sizeof(unsigned int) * CHAR_BIT);
	ASSERT_THAT(!bitMap.All());
	
	bitMap.Flip(sizeof(unsigned int) * CHAR_BIT);
	ASSERT_THAT(bitMap.All());
END_UNIT

UNIT(Any)
	MyBitMap<sizeof(unsigned int) * CHAR_BIT + 3, unsigned int> bitMap;
	
	ASSERT_THAT(!bitMap.Any());
	
	bitMap.Flip(0);
	ASSERT_THAT(bitMap.Any());
	
	bitMap.Flip(0);
	bitMap.Flip(sizeof(unsigned int) * CHAR_BIT);
	ASSERT_THAT(bitMap.Any());
	
	bitMap.Flip(sizeof(unsigned int) * CHAR_BIT);
	ASSERT_THAT(!bitMap.Any());
END_UNIT

UNIT(Empty)
	MyBitMap<sizeof(unsigned int) * CHAR_BIT + 3, unsigned int> bitMap;
	
	ASSERT_THAT(bitMap.Empty());
	
	bitMap.Flip(0);
	ASSERT_THAT(!bitMap.Empty());
	
	bitMap.Flip(0);
	bitMap.Flip(sizeof(unsigned int) * CHAR_BIT);
	ASSERT_THAT(!bitMap.Empty());
	
	bitMap.Flip(sizeof(unsigned int) * CHAR_BIT);
	ASSERT_THAT(bitMap.Empty());
END_UNIT

UNIT(Reverse)
	MyBitMap<sizeof(unsigned int) * CHAR_BIT + 3, unsigned int> bitMap;
	
	bitMap.Reverse();
	ASSERT_THAT(bitMap.All());
	
	bitMap.Reverse();
	ASSERT_THAT(bitMap.Empty());
END_UNIT

UNIT(tilda_operator)
	MyBitMap<sizeof(unsigned int) * CHAR_BIT + 3, unsigned int> bitMap;
	
	MyBitMap<sizeof(unsigned int) * CHAR_BIT + 3, unsigned int> newBitMap = ~bitMap;
	ASSERT_THAT(newBitMap.All());
	
	bitMap = ~newBitMap;
	ASSERT_THAT(bitMap.Empty());
	
	bitMap = ~bitMap;
	ASSERT_THAT(bitMap.All());
END_UNIT

UNIT(and_operator)
	bool first[4] = {1,1,0,0};
	MyBitMap<4> a(first);
	
	bool second[4] = {1,0,1,0};
	MyBitMap<4> b(second);
	
	bool resaultArr[4] = {1,0,0,0};
	MyBitMap<4> resault(resaultArr);
	
	ASSERT_THAT(resault == (a & b));
	
	resault[0] = 0;
	ASSERT_THAT(resault.Empty());
	
END_UNIT

UNIT(or_operator)
	bool first[4] = {1,1,0,0};
	MyBitMap<4> a(first);
	
	bool second[4] = {1,0,1,0};
	MyBitMap<4> b(second);
	
	bool resaultArr[4] = {1,1,1,0};
	MyBitMap<4> resault(resaultArr);
	
	ASSERT_THAT(resault == (a | b));
	
END_UNIT

UNIT(leftShift_operator)
	bool begin[] = {0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1};
	bool end1[] = {1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0};
	bool end2[] = {1,1,1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0};
	MyBitMap<(sizeof(begin) / sizeof(bool)) > a(begin);
	MyBitMap<(sizeof(begin) / sizeof(bool)) > result1(end1);
	
	a <<= 10;
	ASSERT_THAT(a == result1);
	
	MyBitMap<(sizeof(begin) / sizeof(bool)) > b(begin);
	MyBitMap<(sizeof(begin) / sizeof(bool)) > result2(end2);
	
	b <<= 8;
	ASSERT_THAT(b == result2);
	
END_UNIT

UNIT(rightShift_operator)
	bool begin[] = {0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1};
	bool end1[] = {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1};
	bool end2[] = {0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,0,1};
	MyBitMap<(sizeof(begin) / sizeof(bool)) > a(begin);
	MyBitMap<(sizeof(begin) / sizeof(bool)) > result1(end1);
	
	a >>= 10;
	ASSERT_THAT(a == result1);
	
	MyBitMap<(sizeof(begin) / sizeof(bool)) > b(begin);
	MyBitMap<(sizeof(begin) / sizeof(bool)) > result2(end2);
	
	b >>= 8;
	ASSERT_THAT(b == result2);
	
END_UNIT

UNIT(Count)
	bool begin[] = {0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1};
	MyBitMap<(sizeof(begin) / sizeof(bool)), std::size_t > a(begin);
	
	ASSERT_THAT(a.Count() == 22);
	
END_UNIT

/* ============================= 	*/
/*			TEST SUIT				*/
/* ============================= 	*/	

TEST_SUITE(BitMap)
	//TEST(DEF_CTOR_char)
	//TEST(CTOR_from_bool_array)
	TEST(GetBit)
	TEST(GetBit_outOfBounds)
	TEST(SetBit)
	TEST(SetBit_out_of_bounds)
	TEST(copy_CTOR)
	TEST(assignment_operator)
	TEST(equal_operator)
	TEST(subscript_operator_const)
	TEST(subscript_operator_non_const)
	TEST(Flip)
	TEST(All)
	TEST(Any)
	TEST(Empty)
	TEST(Reverse)
	TEST(tilda_operator)
	TEST(and_operator)
	TEST(or_operator)
	TEST(leftShift_operator)
	TEST(rightShift_operator)
	TEST(Count)
END_SUITE
