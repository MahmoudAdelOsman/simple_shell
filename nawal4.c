#include "s_shell.h"

/**
 * get_file_history - gets the history file
 * @func_data: structure containing a data model
 * Return: history file
 */

char *get_file_history(cmd_model *func_data)
{
	char *output, *a;

	a = get_value(func_data, "HOME=");
	if (!a)
		return (NULL);
	output = malloc(sizeof(char) * (str_length(a) +
				str_length(HISTORY_DOC) + 2));
	if (!output)
		return (NULL);
	output[0] = 0;
	string_copy(output, a);
	string_cat(output, "/");
	string_cat(output, HISTORY_DOC);
	return (output);
}

/**
 * new_history - creates a history file
 * @func_data: structure containing a data model
 * Return: 1 on Success
 */

int new_history(cmd_model *func_data)
{
	ssize_t write_flag;
	char *filename = get_file_history(func_data);
	l_list *x = NULL;

	if (!filename)
		return (-1);
	write_flag = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (write_flag == -1)
		return (-1);
	for (x = func_data->history; x; x = x->nxt)
	{
		print_string(x->str, write_flag);
		wr_char('\n', write_flag);
	}
	wr_char(BUFFER_FOR_CLEARING, write_flag);
	close(write_flag);
	return (1);
}

/**
 * read_history_row - reads history
 * @func_data: structure containing a data model
 * Return: log_counter_row on Success
 */

int read_history_row(cmd_model *func_data)
{
	int r;
	int y = 0, linecount = 0;
	ssize_t write_flag, read_length;
	ssize_t history_size = 0;
	struct stat st;
	char *ss = NULL, *filename = get_file_history(func_data);

	if (!filename)
		return (0);
	write_flag = open(filename, O_RDONLY);
	free(filename);
	if (write_flag == -1)
		return (0);
	if (!fstat(write_flag, &st))
		history_size = st.st_size;
	if (history_size < 2)
		return (0);
	ss = malloc(sizeof(char) * (history_size + 1));
	if (!ss)
		return (0);
	read_length = read(write_flag, ss, history_size);
	ss[history_size] = 0;
	if (read_length <= 0)
		return (free(ss), 0);
	close(write_flag);
	for (r = 0; r < history_size; r++)
		if (ss[r] == '\n')
		{
			ss[r] = 0;
			new_ll_history(func_data, ss + y, linecount++);
			y = r + 1;
		}
	if (y != r)
		new_ll_history(func_data, ss + y, linecount++);
	free(ss);
	func_data->log_counter_row = linecount;
	while (func_data->log_counter_row-- >= MAXIMUM_LENGTH_HIST)
		remove_node_from_index(&(func_data->history), 0);
	arrang_history(func_data);
	return (func_data->log_counter_row);
}

/**
 * new_ll_history - creates a history linked list
 * @func_data: structure containing a data model
 * @ss: string buffer
 * @linecount: history line counter
 * Return: 0 Always
 */

int new_ll_history(cmd_model *func_data, char *ss, int linecount)
{
	l_list *x = NULL;

	if (func_data->history)
		x = func_data->history;
	add_node_at_end(&x, ss, linecount);
	if (!func_data->history)
		func_data->history = x;
	return (0);
}

/**
 * arrang_history - rearranges the history linked list
 * @func_data: structure containing a data model
 * Return: log_counter_row
 */

int arrang_history(cmd_model *func_data)
{
	l_list *x = func_data->history;
	int z = 0;

	while (x)
	{
		x->number = z++;
		x = x->nxt;
	}
	return (func_data->log_counter_row = z);
}
