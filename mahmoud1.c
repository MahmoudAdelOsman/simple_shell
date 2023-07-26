#include "s_shell.h"

/**
 * main - main program
 * @margc: arg_c counter
 * @margv: arg_v vector
 * Return: 0 if seccess
 */

int main(int margc, char **margv)
{
	cmd_model func_data[] = {{NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
		{0}, {0}, {0}, {0}, {0}, {0}, {NULL}, {NULL}, {NULL}, {0}, {0}, {0}};
	int a = 2;

	asm ("mov %1, %0\n\tadd $3, %0" : "=r" (a) : "r" (a));

	if (margc == 2)
	{
		a = open(margv[1], O_RDONLY);
		if (a == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_error_string(margv[0]);
				print_error_string(": 0: cant open");
				print_error_string(margv[1]);
				putchar_error('\n');
				putchar_error(BUFFER_FOR_CLEARING);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		func_data->f_read = a;
	}
	ll_env(func_data);
	read_history_row(func_data);
	c_main(func_data, margv);
	return (EXIT_SUCCESS);
}
