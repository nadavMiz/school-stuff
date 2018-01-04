/*
 * mu_test.h
 * Mini Test Framework 
 *     a tiny unit test framework for simple tests. 
 * Version: 0.03
 *      Author: Muhammad Zahalqa   
 * 	    MuhammadZ@experis.co.il
 */

#ifndef MU_TEST_H_
#define MU_TEST_H_


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"



#define __MERGE_(a,b)  	a##b
#define __LABEL_(a) 		__MERGE_(x, a)
#define __UNIQUE_NAME_(x) 	__LABEL_(x, __LINE__)


typedef struct TEST_PAIR{
    int (*unitTest)(void);
    const char*unitName;
} TEST_PAIR;




#define FAIL                (1)
#define PASS                (0)

#define UNIT(name)          int name(void){

#define END_UNIT               return PASS; \
                            }

#define ASSERT_THAT(e)      do{ if(!(e)) return FAIL;} while(0)

#define TEST_SUITE(name)    int main(){\
                                const char *test_name = #name; \
                                TEST_PAIR tests[] = {

#define TEST(unit)		{unit, #unit},

#define IGNORE_TEST(unit)
#define END_SUITE                           {NULL, NULL} \
                                }; \
                                TEST_PAIR *pTest = tests; \
                                int fails = 0; \
                                fprintf(stderr, "%s\n", test_name); \
                                while(pTest->unitTest){ \
					int r = pTest->unitTest();  \
					fails += r == PASS ? 0 : 1; \
					fprintf(stderr, "%s - %s\n", r == PASS ? KGRN "PASS"  KWHT: KRED "FAIL" KWHT, pTest->unitName);\
					++pTest; \
                                }\
				fprintf(stderr, "%s done\n", test_name); \
                                return fails;\
                            }



#endif /* MU_TEST_H_ */


