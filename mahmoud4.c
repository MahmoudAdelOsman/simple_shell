#include "s_shell.h"

/**
 * str_length - returns length of string
 * @c: String input needed
 * Return: length of string
 */

int str_length(char *c)
{
	int x = 0;

	if (!c)
		return (0);
	while (*c++)
		x++;
	return (x);
}

/**
 * str_compare - compares between two strings.
 * @str1: first string.
 * @str2: second string.
 * Return: positive if str1 > str2, negative if
 * str1 < str2, zero if str1 == str2.
 */

int str_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * haystack_check - check if needle starts with haystack
 * @ss: string to search
 * @s: second string
 * Return: pointer to next of haystack
 */

char *haystack_check(const char *ss, const char *s)
{
	while (*s)
		if (*s++ != *ss++)
			return (NULL);
	return ((char *)ss);
}

/**
 * string_cat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: Pointer to destination string
 */

char *string_cat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
