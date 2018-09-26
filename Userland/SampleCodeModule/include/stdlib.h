#ifndef STDLIB_H
#define STDLIB_H

#define RAND_MAX 32767

int rand();
void srand(unsigned int seed);
char toLower(char c);
char toUpper(char c);
int isLower(char c);
int isUpper(char c);
int isSpace(char c);
int isDigit(char c);
int isAlpha(char c);
int isAlphaNum(char c);
int stringIsAlpha(char *s);
int stringIsDigit(char *s);
void stringToUpper(char *s);
void stringToLower(char *s);
int stringIsNum(char *string);
void inToString(int num, char *ret);
int stringToInt(const char *string, int *num);
int pow(int num, int exp);

#endif