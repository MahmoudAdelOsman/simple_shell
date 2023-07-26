#include "s_shell.h"

/**
 * _conv - converts a string to an integer
 * @digit: The string to be converted
 * Return: 0 if there are no string numbers, converted number otherwise
 */

int _conv(char *digit)
{
	int x, y = 0, negative = 1, output;
	unsigned int out = 0;

	for (x = 0; digit[x] != '\0' && y != 2; x++)
	{
		if (digit[x] == '-')
			negative *= -1;
		if (digit[x] >= '0' && digit[x] <= '9')
		{
			y = 1;
			out *= 10;
			out += (digit[x] - '0');
		}
		else if (y == 1)
			y = 2;
	}
	if (negative == -1)
		output = -out;
	else
		output = out;
	return (output);
}

/**
 * _isalpha - checks for alphabetic characters
 * @c: the input character
 * Return: 1 if c is alphabetic, 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _specified - checks if character is a specified
 * @a: The char to check
 * @determined: The specified string
 * Return: 0 if false, 1 if true
 */

int _specified(char a, char *determined)
{
	while (*determined)
		if (*determined++ == a)
			return (1);
	return (0);
}

/**
 * onfire - returns true if shell is in on mode
 * @func_data: struct address
 * Return: 1 if shell is in on mode, 0 otherwise
 */

int onfire(cmd_model *func_data)
{
	return (isatty(STDIN_FILENO) && func_data->f_read <= 2);
}
