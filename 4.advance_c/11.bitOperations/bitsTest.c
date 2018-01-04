#include <stdio.h>
#include <time.h>

#include "bits.h"
#include "mu_test.h"

UNIT(test_abs)
	ASSERT_THAT( 5 == ABS(-5));
END_UNIT

TEST_SUITE(framework test)
	TEST(test_abs)
END_SUITE
