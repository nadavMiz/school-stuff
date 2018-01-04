#ifndef STRINGS_H
#define STRINGS_H

/*
convert string to int.
param str: the string to convert
return: the converted string. if the string wasn't valid return 0;
*/
int myAtoi(char *str);
/*
convert int to string.
param fromIntiger: the int to convert
param toString: pointer to store the converted int
return 0: failed, 1:succeeded
*/
int myItoa(int value, char *toString);
/*
reverse the inputed string
param toReverse: the string to reverse
return: 0: failed 1:succeeded
*/
int reverseString(char *toReverse);

/*
return: 
  1: if the string is a palindrom
  0: if the string isnt palindrom
*/
int isPalindrom(char *string);

/*
append src to the end of dest
return pointer to dest
*/
char *myStrcat(char *dest, const char *src);

/*
compare 2 strings
return 0: strings are equal. return negative string 2 is larger.
return positive: string 1 is larger.  
*/
int myStrcmp(char* str1, char* str2);

#endif
