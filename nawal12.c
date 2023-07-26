#include "simple_shell.h"

/**
 * print_decimal - prints a decimal number - base 10
 * @dec: first input needed
 * @write_flag: second input flag needed to write
 * Return: a printed decimal number
 */

int print_decimal(int dec, int write_flag)
{
	int (*print_char)(char) = _putchar;
	int b;
	int output = 0;
	unsigned int h, z;

	if (write_flag == STDERR_FILENO)
		print_char = putchar_error;
	if (dec < 0)
	{
		h = -dec;
		print_char ('-');
		output++;
	}
	else
		h = dec;
	z = h;
	for (b = 1000000000; b > 1; b /= 10)
	{
		if (h / b)
		{
			print_char ('0' + z / b);
			output++;
		}
		z %= b;
	}
	print_char ('0' + z);
	output++;
	return (output);
}

/**
 * num_to_str - converts number to string
 * @input: first input needed to convert
 * @base: number base
 * @flags: third flags input needed
 * Return: the converted string
 */

char *num_to_str(long int input, int base, int flags)
{
	static char *n;
	static char size_buffer[50];
	char *output;
	unsigned long number = input;
	char negative = 0;

	if (!(flags & TO_UNSIGNED) && input < 0)
	{
		number = -input;
		negative = '-';
	}
	n = flags & LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	output = &size_buffer[49];
	*output = '\0';
	do	{
		*--output = n[number % base];
		number /= base;
	} while (number != 0);
	if (negative)
		*--output = negative;
	return (output);
}

/**
 * change_first_char - changes first character '#' with '\0'
 * @ss: pointer to string to change
 * Return: void
 */

void change_first_char(char *ss)
{
	int t;

	for (t = 0; ss[t] != '\0'; t++)
		if (ss[t] == '#' && (!t || ss[t - 1] == ' '))
		{
			ss[t] = '\0';
			break;
		}
}

/**
 * error_conv - converts a string to integer
 * @input: first string input to be converted
 * Return: converted number or -1 on error
 */

int error_conv(char *input)
{
	int j = 0;
	unsigned long int output = 0;

	if (*input == '+')
		input++;
	for (j = 0; input[j] != '\0'; j++)
	{
		if (input[j] >= '0' && input[j] <= '9')
		{
			output *= 10;
			output += (input[j] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * print_error - prints an error messages
 * @func_data: structure containing data model
 * @c: input error type as a string
 * Return: void
 */

void print_error(cmd_model *func_data, char *c)
{
	print_error_string(func_data->f_name);
	print_error_string(": ");
	print_decimal(func_data->row_error_count, STDERR_FILENO);
	print_error_string(": ");
	print_error_string(func_data->arg_v[0]);
	print_error_string(": ");
	print_error_string(c);
}
