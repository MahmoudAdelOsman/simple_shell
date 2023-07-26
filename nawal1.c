#include "s_shell.h"

/**
 * c_alias - runs alias command
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int c_alias(cmd_model *func_data)
{
	int z = 0;
	char *c = NULL;
	l_list *x = NULL;

	if (func_data->arg_c == 1)
	{
		x = func_data->alias;
		while (x)
		{
			p_alias(x);
			x = x->nxt;
		}
		return (0);
	}
	for (z = 1; func_data->arg_v[z]; z++)
	{
		c = c_strchr(func_data->arg_v[z], '=');
		if (c)
			add_alias(func_data, func_data->arg_v[z]);
		else
			p_alias(get_prefix(func_data->alias, func_data->arg_v[z], '='));
	}
	return (0);
}

/**
 * p_alias - prints an alias string
 * @x: alias node
 * Return: 0 on Success
 */

int p_alias(l_list *x)
{
	char *ptr = NULL, *c = NULL;

	if (x)
	{
		ptr = c_strchr(x->str, '=');
		for (c = x->str; c <= ptr; c++)
		_putchar(*c);
		_putchar('/');
		_puts(ptr + 1);
		_puts("\n");
		return (0);
	}
	return (1);
}

/**
 * add_alias - adds alias string
 * @func_data: structure containing a data model
 * @s_a: string alias
 * Return: 0 on Success
 */

int add_alias(cmd_model *func_data, char *s_a)
{
	char *ptr;

	ptr = c_strchr(s_a, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (delete_alias(func_data, s_a));
	delete_alias(func_data, s_a);
	return (add_node_at_end(&(func_data->alias), s_a, 0) == NULL);
}

/**
 * delete_alias - removes alias string
 * @func_data: structure containing a data model
 * @s_a: string alias
 * Return: 0 on Success
 */

int delete_alias(cmd_model *func_data, char *s_a)
{
	char *ptr, c;
	int output;

	ptr = c_strchr(s_a, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	output = remove_node_from_index(&(func_data->alias),
			index_node(func_data->alias, get_prefix(func_data->alias, s_a, -1)));
	*ptr = c;
	return (output);
}

/**
 * c_history - runs history linked list
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int c_history(cmd_model *func_data)
{
	print_list(func_data->history);
	return (0);
}
