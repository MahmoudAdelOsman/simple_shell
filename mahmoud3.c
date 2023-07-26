#include "s_shell.h"

/**
 * check_chaining_delimeter - check current character a chain delimeter
 * @func_data: Structure containing a data model
 * @c: Character buffer
 * @p: Pointer to current character
 * Return: 1 if Success
 */

int check_chaining_delimeter(cmd_model *func_data, char *c, size_t *p)
{
	size_t a = *p;

	if (c[x] == '|' && c[x + 1] == '|')
	{
		c[x] = 0;
		x++;
		func_data->c_mode = OR_MODE_COM;
	}
	else if (c[x] == '&' && c[x + 1] == '&')
	{
		c[x] = 0;
		x++;
		func_data->c_mode = AND_MODE_COM;
	}
	else if (c[x] == ';')
	{
		c[x] = 0;
		func_data->c_mode = END_MODE_COM;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * check_chaining_continue - check chaining continuaty
 * @func_data: Structure containing a data model
 * @c: Character buffer
 * @p: Pointer to character
 * @length: length of character buffer
 * @n: starting position
 * Return: Void
 */

void check_chaining_continue(cmd_model *func_data, char *c, size_t n,
		size_t *p, size_t length)
{
	size_t y = *p;

	if (func_data->c_mode == AND_MODE_COM)
	{
		if (func_data->fb)
		{
			c[n] = 0;
			y = length;
		}
	}
	if (func_data->c_mode == OR_MODE_COM)
	{
		if (!func_data->fb)
		{
			c[n] = 0;
			y = length;
		}
	}
	*p = y;
}

/**
 * change_c_alias - changes alias string
 * @func_data: Structure containing adata model
 * Return: 1 if Success
 */

int change_c_alias(cmd_model *func_data)
{
	l_list *x;
	char *a;
	int m;

	for (m = 0; m < 10; m++)
	{
		x = get_prefix(func_data->alias, func_data->arg_v[0], '=');
		if (!x)
			return (0);
		free(func_data->arg_v[0]);
		a = c_strche(x->str, '=');
		if (!a)
			return (0);
		a = string_duplicate(a + 1);
		if (!a)
			return (0);
		func_data->arg_v[0] = a;
	}
	return (1);
}

/**
 * change_str - changes string
 * @ss1: Pointer to Pointer to first string
 * @ss2: Pointer to second string
 * Return: 1 if Success
 */

int change_str(char **ss1, char *ss2)
{
	free(*ss1);
	*ss1 = ss2;
	return (1);
}

/**
 * change_c_vars - changes vars string
 * @func_data: Structure conteaining a data model
 * Return: 1 if Success
 */

int change_c_vars(cmd_model *func_data)
{
	int v;
	l_list *x;

	for (v = 0; func_data->arg_v[v]; v++)
	{
		if (func_data->arg_v[v][0] != '$' || !func_data->arg_v[v][1])
			continue;
		if (!str_compare(func_data->arg_v[v], "$?"))
		{
			change_str(&(func_data->arg_v[v]),
					string_duplicate(num_to_str(func_data->fb, 10, 0)));
			continue;
		}
		if (!str_compare(func_data->arg_v[v], "$$"))
		{
			change_str(&(func_data->arg_v[v]),
					string_duplicate(num_to_str(getpid(), 10, 0)));
			continue;
		}
		x = get_prefix(func_Data->env_ll, &func_data->arg_v[v][1], '=');
		if (x)
		{
			change_str(&(func_data->arg_v[v]),
					string_duplicate(c_strchr(s->str, '=') + 1));
			continue;
		}
		change_str(&(func_data->arg_v[v]), string_duplicate(""));
	}
	return (0);
}
