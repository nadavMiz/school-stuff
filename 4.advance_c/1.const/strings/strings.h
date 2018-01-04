#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <stddef.h>

/*
get the length of a string
paramaters:
	_str: the string to get the length of
return:
	the length of the string.
	0: if _str is NULL
*/
size_t StrLen(const char* _str);

/*
recursive function that gets the length of a string
paramaters:
	_str: the string to get the length of
return:
	the length of the string.
	0: if _str is NULL
*/
size_t StrLenRec(const char* _str);

/*
compares two strings
paramaters:
	_s1: a string to be compared
	_s2: a string to be compared
return:
	0: strings are equal (including both are NULL).
	
	value < 0 : the first charecter from the beginning that
				does not mach is bigger in _s2 than in _s1 (also if only _s1 is NULL)
				
	value > 0 : the first charecter from the beginning that
				does not mach is bigger in _s1 than in _s2 (also if only _s2 is NULL)
*/
int StrCompare(const char* _s1, const char* _s2);

/*
compares two strings recursively
paramaters:
	_s1: a string to be compared
	_s2: a string to be compared
return:
	0: strings are equal (including both are NULL).
	
	value < 0 : the first charecter from the beginning that
				does not mach is bigger in _s2 than in _s1 (also if only _s1 is NULL)
				
	value > 0 : the first charecter from the beginning that
				does not mach is bigger in _s1 than in _s2 (also if only _s2 is NULL)
*/
int StrCompareRec(const char* _s1, const char* _s2);

/*
copy a string to a destination
paramaters:
	_destination: pointer to the destination array to copy to
	_source: the string to copy
returns:
	returns _destination
*/
char* StrCopy(char* _destination, const char* _source);

/*
copy a string to a destination recursively
paramaters:
	_destination: pointer to the destination array to copy to
	_source: the string to copy
returns:
	returns _destination
*/
char* StrCopyRec(char* _destination, const char* _source);

/*
copy the first n charecters of a string to the beginning of a destination string
does not add '\0' if one was not present at the end of the destination.
copy all of source if its end was less than n
paramaters:
	_destination: pointer to the destination array to copy to
	_source: the string to copy
	_num: number of charecters to copy
returns:
	returns _destination
*/
char* StrNCopy(char* _destination, const char* _source, size_t _num);

/*
copy the first n charecters of a string to the beginning of a destination string recursively
does not add '\0' if one was not present at the end of the destination.
copy all of source if its end was less than n
paramaters:
	_destination: pointer to the destination array to copy to
	_source: the string to copy
	_num: number of charecters to copy
returns:
	returns _destination
*/
char* StrNCopyRec(char* _destination, const char* _source, size_t num);

/*
copy one string to the end of another
paramaters:
	destination: pointer to the destination array to copy to the end of
	_source: the string to copy
returns:
	returns _destination
*/
char* StrConcat(char* _destination, const char* _source);

/*
searches for the first occurrence of a substring in a string
paramaters:
	_str: the string to search the substring in
	_search: the substring to search
returns:
	pointer to the beginning of the first occurrence _search in _str
*/
char* StrSubString(const char* _str, const char* _search);

#endif /* ifndef _STRINGS_H_ */
