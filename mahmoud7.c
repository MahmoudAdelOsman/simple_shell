#include "s_shell.h"

/**
 * string_copy - copies a string
 * @dest: destination string
 * @src: source string
 * Return: pointer to destination string
 */

char *string_copy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * string_duplicate - duplicates a string
 * @ss: String input needed
 * Return: Pointer to string
 */

char *string_duplicate(const char *ss)
{
	int len = 0;
	char *result;

	if (ss == NULL)
		return (NULL);
	while (*ss++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--ss;
	return (result);
}

/**
 * _puts - print an input string
 * @ss: String input needed
 * Return: Void
 */

void _puts(char *ss)
{
	int x = 0;

	if (!ss)
		return;
	while (ss[x] != '\0')
	{
		_putchar(ss[x]);
		x++;
	}
}

/**
 * _putchar - print a character
 * @c: Character input needed
 * Return: 1 if Success
 */

int _putchar(char c)
{
	static int x;
	static char write_buffer[BUFFER_WRITE_FUNCTION];

	if (c == BUFFER_FOR_CLEARING || x >= BUFFER_WRITE_FUNCTION)
	{
		write(1, write_buffer, x);
		x = 0;
	}
	if (c != BUFFER_FOR_CLEARING)
		write_buffer[x++] = c;
	return (1);
}
