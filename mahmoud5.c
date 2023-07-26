#include "s_shell.h"

/**
 * c_env - prints the current environment
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int c_env(cmd_model *func_data)
{
	print_linked_list(func_data->env_ll);
	return (0);
}

/**
 * c_add_env - creates a new environment
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int c_add_env(cmd_model *func_data)
{
	if (func_data->arg_c != 3)
	{
		print_error_string("incorrect number of arguments\n");
		return (1);
	}
	if (add_new_env(func_data, func_data->arg_v[1], func_data->arg_v[2]))
		return (0);
	return (1);
}

/**
 * c_remove_env - remove an existing environment
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int c_remove_env(cmd_model *func_data)
{
	int n;

	if (func_data->arg_c == 1)
	{
		print_error_string("too few arguments.\n");
		return (1);
	}
	for (n = 1; n <= func_data->arg_c; n++)
		remove_env(func_data, func_data->arg_v[n]);
	return (0);
}

/**
 * ll_env - creates environment linked list
 * @func_data: structure containing a data model
 * Return: 0 Always
 */
int ll_env(cmd_model *func_data)
{
	l_list *x = NULL;
	size_t v;

	for (v = 0; c_environ[v]; v++)
		add_node_at_end(&x, c_environ[v], 0);
	func_data->env_ll = x;
	return (0);
}

/**
 * get_value - gets a value of an enviroment
 * @func_data: structure containing a data model
 * @env_name: environment name
 * Return: value of an environment
 */

char *get_value(cmd_model *func_data, const char *env_name)
{
	l_list *x = func_data->env_ll;
	char *w;

	while (x)
	{
		w = haystack_check(x->str, env_name);
		if (w && *w)
			return (w);
		x = x->nxt;
	}
	return (NULL);
}
