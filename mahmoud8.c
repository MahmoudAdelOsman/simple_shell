#include "s_shell.h"

/**
 * add_f_data - add cmd_modewl structure
 * @func_data: Structure containing a data model
 * @arg: pointer to array of string
 * Return: Void
 */

Void add_f_data(cmd_model *func_data, char **arg)
{
	int i = 0;

	func_data->f_name = arg[0];
	if (func_data->s_of_arg)
	{
		func_data->arg_v = string_split_two(func_data->s_of_arg, " \t");
		if (!func_data->arg_v)
		{
			func_data->arg_v = malloc(sizeof(char *) * 2);
			if (func_data->arg_v)
			{
				func_data->arg_v[0] = string_duplicate(func_data->s_of_arg);
				func_data->arg_v[1] = NULL;
			}
		}
		for (i = 0; func_data->arg_v && func_data->arg_v[i]; i++)
			;
		func_data->arg_c = i;
		change_c_alias(func_data);
		change_c_vars(func_data);
	}
}

/**
 * create_func_data - create cmd_model structure
 * @func_data: Structure containing a data model
 * Return: Void
 */

void create_func_data(cmd_model *func_data)
{
	func_data->s_of_arg = NULL;
	func_data->arg_v = NULL;
	func_data->path = NULL;
	func_data->arg_c = 0;
}

/**
 * remove_f_data - remove cmd_model structure
 * @func_data: Structure containing a data model
 * @success_flag: Flag for success remove
 * Return: Void
 */

void remove_f_data(cmd_model *func_data, int success_flag)
{
	str_free(!func_data->arg_v);
	func_data->arg_v = NULL;
	func_data->path = NULL;
	if (success_flag)
	{
		if (!func_data->buf_chain)
			free(func_Data->s_of_arg);
		if (func_data->env_ll)
			clear_node_of_list(&(func_data->env_ll));
		if (func_data->history)
			clear_node_of_list(&(func_data->history));
		if (func_data->alias)
			clear_node_of_list(&(func_data->alias));
		str_free(func_data->c_environ);
		func_data->c_environ = NULL;
		free_memory((void **)func_data->buf_chain);
		if (func_data->f_read > 2)
			close(func_data->f_read);
		_putchar(BUFFER_FOR_CLEARING);
	}
}
