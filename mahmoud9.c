#include "s_shell.h"

/**
 * get_str_environ - returns a string from an environment
 * @func_data: Structure containing a data model
 * Return: 0 Always
 */

char **get_str_environ(cmd_model *func_data)
{
	if (!func_data->c_environ || func_data->change_f)
	{
		func_data->c_environ = ll_array(func_data->env_ll);
		func_data->change_f = 0;
	}
	return (func_data->c_environ);
}

/**
 * remove_env - remove an environment
 * @func_data: structure containing a data model
 * @ss: string of environment property
 * Return: 1 if success
 */

int remove_env(cmd_model *func_data, char *ss)
{
	l_list *x = func_data->env_ll;
	size_t r = 0;
	char *c;

	if (!x || !ss)
		return (0);
	while (x)
	{
		c = haystack_check(x->str, ss);
		if (c && *c == '=')
		{
			func_data->change_f = remove_node_from_index(&(func_data->env_ll), r);
			r = 0;
			x = func_data->env_ll;
			continue;
		}
		x = x->nxt;
		r++;
	}
	return (func_data->change_f);
}

/**
 * add_new_env - create a new environment
 * @func_data: structure containing a data model
 * @ss: string of an environment property
 * @ss_value: string of environment variable value
 * Return: Always 0
 */

int add_new_env(cmd_model *func_data, char *ss, char *ss_value)
{
	char *x = NULL;
	l_list *y;
	char *z;

	if (!ss || !ss_value)
		return (0);
	x = malloc(str_length(ss) + str_length(ss_value) + 2);
	if (!x)
		return (1);
	string_copy(x, ss);
	string_cat(x, "=");
	string_cat(x, ss_value);
	x = func_data->env_ll;
	while (y)
	{
		z = haystack_check(y->str, ss);
		if (z && *z == "=")
		{
			free(y->str);
			y->str = x;
			func_data->change_f = 1;
			return (0);
		}
		y = y->nxt;
	}
	add_node_at_end(&(func_data->env_ll), x, 0);
	free(x);
	func_data->change_f = 1;
	return (0);
}
