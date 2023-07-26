#include "s_shell.h"

/**
 * c_cd - changes the current directory
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int c_cd(cmd_model *func_data)
{
	char *m, *dir;
	char buf[1024];
	int chdir_return;

	m = getcwd(buf, 1024);
	if (!m)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!func_data->arg_v[1])
	{
		dir = get_value(func_data, "HOME=");
		if (!dir)
			chdir_return = chdir((dir = get_value(func_data, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (str_compare(func_data->arg_v[1], "-") == 0)
	{
		if (!get_value(func_data, "OLDPWD="))
		{
			_puts(m);
			_putchar('\n');
			return (1);
		}
		_puts(get_value(func_data, "OLDPWD=")), _putchar('\n');
		chdir_return = chdir((dir = get_value(func_data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(func_data->arg_v[1]);
	if (chdir_return == -1)
	{
		print_error(func_data, "can't cd to ");
		print_error_string(func_data->arg_v[1]);
		putchar_error('\n');
	}
	else
	{
		add_new_env(func_data, "OLDPWD", get_value(func_data, "PWD="));
		add_new_env(func_data, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * c_exit - exits simple shell
 * @func_data: structure containing a data model
 * Return: 0 on Success
 */

int c_exit(cmd_model *func_data)
{
	int checker;

	if (func_data->arg_v[1])
	{
		checker = error_conv(func_data->arg_v[1]);
		if (checker == -1)
		{
			func_data->fb = 2;
			print_error(func_data, "Illegal number: ");
			print_error_string(func_data->arg_v[1]);
			putchar_error('\n');
			return (1);
		}
		func_data->code_error = error_conv(func_data->arg_v[1]);
		return (-2);
	}
	func_data->code_error = -1;
	return (-2);
}

/**
 * c_help - executes a help command
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int c_help(cmd_model *func_data)
{
	char **rg;

	rg = func_data->arg_v;
	_puts("help call works. Function not yet implemented\n");
	if (0)
		_puts(*rg);
	return (0);
}
