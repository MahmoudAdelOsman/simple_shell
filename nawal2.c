#include "s_shell.h"

/**
 * wr_char - writes a character into a file
 * @a: printed character
 * @write_flag: a flag to write
 * Return: 1 on Success
 */

int wr_char(char a, int write_flag)
{
	static int q;
	static char write_size[BUFFER_WRITE_FUNCTION];

	if (a == BUFFER_FOR_CLEARING || q >= BUFFER_WRITE_FUNCTION)
	{
		write(write_flag, write_size, q);
		q = 0;
	}
	if (a != BUFFER_FOR_CLEARING)
		write_size[q++] = a;
	return (1);
}

/**
 * print_string - prints an input string
 * @ss: string to be printed
 * @write_flag: a flag to write
 * Return: the string to be printed
 */

int print_string(char *ss, int write_flag)
{
	int v = 0;

	if (!ss)
		return (0);
	while (*ss)
		v += wr_char(*ss++, write_flag);
	return (v);
}

/**
 * print_error_string - prints an input error string
 * @ss: string to be printed
 * Return: void
 */

void print_error_string(char *ss)
{
	int l;

	if (!ss)
		return;
	for (l = 0; ss[l] != '\0'; l++)
		putchar_error(ss[l]);
}

/**
 * putchar_error - writes a character to stderr
 * @a: character to be printed
 * Return: 1 on Success
 */

int putchar_error(char a)
{
	static int q;
	static char write_size[BUFFER_WRITE_FUNCTION];

	if (a == BUFFER_FOR_CLEARING || q >= BUFFER_WRITE_FUNCTION)
	{
		write(2, write_size, q);
		q = 0;
	}
	if (a != BUFFER_FOR_CLEARING)
		write_size[q++] = a;
	return (1);
}
