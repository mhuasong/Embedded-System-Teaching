#ifndef _MYSTRING_H_ 
#define _MYSTRING_H_ 
#define NULL 0

int my_strcmp(char *string1, char *string2);
int my_strlen(char *string);
char *my_strcat(char *res, const char *string);
char *my_strcpy(const char *sou, char *dest);
const char *my_strchr(char const *str,int ch);
const char *my_strstr(char const *s1,char const *s2);

#endif
