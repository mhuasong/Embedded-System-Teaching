#include "mystring.h"
 
int my_strcmp(char *string1, char *string2)
{
	char *index1 = string1;
	char *index2 = string2;
	
	while (*index1 == *index2 && *index1 != '\0' && *index2 != '\0')
	{
		index1++;
		index2++;
	}
	if (*index1 - *index2 > 0)
	{
		return 1;
	}
	else if (*index1 - *index2 < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
 
int my_strlen(char *string)
{
	char *temp = string;
	int count = 0;
	if (string == NULL || *string == '\0')
	{
		return 0;
	}
	while (*temp != '\0')
	{
		temp++;
		count++;
	}
	return count;
}
 
char *my_strcat(char *res, const char *string)
{
	char *ret = res;
	if (string == NULL || *string == '\0')
	{
		return res;
	}
	while (*res != '\0')
	{
		res++;
	}
	while (*string != '\0')
	{
		*res++ = *string++;
	}
	*res = '\0';
	return ret;
}
 
char *my_strcpy(const char *sou, char *dest)
{
	char *addr = dest;
	if (dest == NULL || sou == NULL)
	{
		return NULL;
	}
	while (*sou != '\0')
	{
		*dest++ = *sou++;
	}
	*dest = '\0';
	return addr;
}
 
const char *my_strchr(char const *str,int ch)
{
	if (str == NULL || *str == '\0')
	{
		return NULL;
	}
	while (*str != ch && *str != '\0')
		str++;
	if (*str == ch)
		return str;
	else
		return NULL;
}
 
/*************************************************/
const char *my_strstr(char const *s1,char const *s2)
{
	int n;
	if (*s2 == '\0' || s2 == NULL)
	{
		return s1;
	}
	while (*s1 != '\0')
	{
		for (n = 0; *(s1 + n) == *(s2 + n); n++)
		{
			if (*(s2 + n + 1) == '\0')
				return s1;
		}
		s1++;
	}
	return NULL;
}

