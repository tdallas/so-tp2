#include <stdlib.h>

unsigned long int rand_next = 1;

int rand()
{
	rand_next = rand_next * 1103515245 + 12345;
	return ((unsigned int)(rand_next / 65536) % 32768);
}

void srand(unsigned int seed)
{
	rand_next = seed;
}

char toLower(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return 'a' + c - 'A';
	}
	return c;
}
char toUpper(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return 'A' + c - 'a';
	}
	return c;
}

int isUpper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

int isLower(char c)
{
	return (c >= 'a' && c <= 'z');
}

int isSpace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v');
}

int isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

int isAlpha(char c)
{
	return (isLower(c) || isUpper(c));
}

int isAlphaNum(char c)
{
	return (isAlpha(c) || isDigit(c));
}

int stringIsAlpha(char *s)
{
	while (*s != '\0')
	{
		if (!isAlpha(*s))
		{
			return 0;
		}
		s++;
	}
	return 1;
}

void stringToLower(char *s)
{
	while (*s != '\0')
	{
		if (isUpper(*s))
		{
			*s = toLower(*s);
		}
		s++;
	}
}

void stringToUpper(char *s)
{
	while (*s != '\0')
	{
		if (isLower(*s))
		{
			*s = toUpper(*s);
		}
		s++;
	}
}

int stringIsDigit(char *s)
{
	while (*s != '\0')
	{
		if (!isDigit(*s))
		{
			return 0;
		}
		s++;
	}
	return 1;
}

int stringIsAlphaNum(char *s)
{
	while (*s != '\0')
	{
		if (!isAlphaNum(*s))
		{
			return 0;
		}
		s++;
	}
	return 1;
}

int countDigits(int num)
{
	int count = 0;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return count;
}

// Return values: 2 if float, 1 if int, 0 if not num
int stringIsNum(char *string)
{

	int isFloat = 0;

	if (*string == '-')
	{
		string++;
	}

	if (!isDigit(*string))
	{
		return 0;
	}
	string++;

	while (!isSpace(*string) && *string != '\0')
	{
		int dotRead = 0;
		if (!isDigit(*string))
		{
			if (*string == '.')
			{
				if (dotRead > 0)
					return 0;
				isFloat++;
				dotRead++;
				string++;
			}
			else
			{
				return 0;
			}
		}
		string++;
	}

	return 1 + isFloat;
}

void inToString(int num, char *ret)
{
	int dig = 0;
	int flagNegative = 0;
	char aux;
	if (num != 0)
	{
		if (num < 0)
		{
			num = -num;
			ret[0] = '-';
			dig++;
			flagNegative = 1;
		}
		while (num != 0)
		{
			ret[dig] = (num % 10) + '0';
			num = num / 10;
			dig++;
		}
		if (flagNegative)
		{
			char *auxRet = ret + 1;
			dig--;
			for (int x = 0; x < dig / 2; x++)
			{
				aux = auxRet[x];
				auxRet[x] = auxRet[dig - x - 1];
				auxRet[dig - x - 1] = aux;
			}
			dig++;
			ret = auxRet;
			ret[dig] = 0;
		}
		else
		{
			for (int x = 0; x < dig / 2; x++)
			{
				aux = ret[x];
				ret[x] = ret[dig - x - 1];
				ret[dig - x - 1] = aux;
			}
			ret[dig] = 0;
		}
	}
	else
	{
		ret[0] = '0';
	}
}

int stringToInt(const char *string, int *num)
{
	int i = 0;
	*num = 0;
	int sign = 1;
	if (string[i] == '+' || string[i] == '-')
	{
		if (string[i] == '-')
			sign = -1;
		i++;
	}
	while (isDigit(string[i]))
	{
		(*num) *= 10;
		(*num) += (int)(string[i] - '0');
		i++;
	}
	(*num) *= sign;
	return i;
}

int pow(int num, int exp)
{
	int result = 1;
	while (exp != 0)
	{
		result *= num;
		exp--;
	}
	return result;
}