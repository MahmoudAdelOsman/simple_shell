#include "s_shell.h"

/**
 * c_main - main shell loop
 * @func_data: structure containing a data model
 * @arg: the arg_v vector
 * Return: 0 on Success
 */

int c_main(cmd_model *func_data, char **arg)
{
	ssize_t m = 0;
	int output_value = 0;

	while (m != -1 && output_value != -2)
	{
		create_func_data(func_data);
		if (onfire(func_data))
			_puts("$ ");
		putchar_error(BUFFER_FOR_CLEARING);
		m = get_line(func_data);
		if (m != -1)
		{
			add_f_data(func_data, arg);
			output_value = call_com(func_data);
			if (output_value == -1)
				find_com(func_data);
		}
		else if (onfire(func_data))
			_putchar('\n');
		remove_f_data(func_data, 0);
	}
	new_history(func_data);
	remove_f_data(func_data, 1);
	if (!onfire(func_data) && func_data->fb)
		exit(func_data->fb);
	if (output_value == -2)
	{
		if (func_data->code_error == -1)
			exit(func_data->fb);
		exit(func_data->code_error);
	}
	return (output_value);
}

/**
 * call_com - finds commands
 * @func_data: structure containing a data model
 * Return: 0 on Success
 */

int call_com(cmd_model *func_data)
{
	int x, output = -1;
	func_table com_table[] = {
		{"exit", c_exit},
		{"env_ll", c_env},
		{"help", c_help},
		{"history", c_history},
		{"setenv", c_add_env},
		{"unsetenv", c_remove_env},
		{"cd", c_cd},
		{"alias", c_alias},
		{NULL, NULL}
	};

	for (x = 0; com_table[x]. flag_name; x++)
		if (str_compare(func_data->arg_v[0], com_table[x].flag_name) == 0)
		{
			func_data->row_error_count++;
			output = com_table[x].func_name(func_data);
			break;
		}
	return (output);
}

/**
 * find_com - finds a command
 * @func_data: structure containing a data model
 * Return: void
 */

void find_com(cmd_model *func_data)
{
	char *dir = NULL;
	int m, n;

	func_data->path = func_data->arg_v[0];
	if (func_data->line_count == 1)
	{
		func_data->row_error_count++;
		func_data->line_count = 0;
	}
	for (m = 0, n = 0; func_data->s_of_arg[m]; m++)
		if (!_specified(func_data->s_of_arg[m], " \t\n"))
			n++;
	if (!n)
		return;
	dir = search_in_dir(func_data, get_value(func_data,
				"PATH="), func_data->arg_v[0]);
	if (dir)
	{
		func_data->path = dir;
		f_run_command(func_data);
	}
	else
	{
		if ((onfire(func_data) || get_value(func_data,
						"PATH=") || func_data->arg_v[0][0] == '/')
				&& exe_checker(func_data, func_data->arg_v[0]))
			f_run_command(func_data);
		else if (*(func_data->s_of_arg) != '\n')
		{
			func_data->fb = 127;
			print_error(func_data, "not found\n");
		}
	}
}

/**
 * f_run_command - forks to run command
 * @func_data: structure containing a data model
 * Return: void
 */

void f_run_command(cmd_model *func_data)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return;
	}
	if (child == 0)
	{
		if (execve(func_data->path, func_data->arg_v, get_str_environ(func_data)) == -1)
		{
			remove_f_data(func_data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(func_data->fb));
		if (WIFEXITED(func_data->fb))
		{
			func_data->fb = WEXITSTATUS(func_data->fb);
			if (func_data->fb == 126)
				print_error(func_data, "Permission denied\n");
		}
	}
}
