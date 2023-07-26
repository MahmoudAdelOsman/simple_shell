#include "s_shell.h"
/**
*get_file_history - gets the history file
*@func_data: structure containing a data model
*return: history file
*/
char *get_file_history(cmd_model *func_data)
{
char *output, *a;
a = get_value(fun_data, "HOME=");
if (!a)
return (NULL);
output = malloc(sizeof(char) * (str_length(a) +
str_length(HISTORY_DO)
if (!a)
return (NULL);
output = malloc(sizeof(char) * (str_length(a) +  
str_length(HISTORY_DOC)
if (!output)
return (NULL)
output[0] = 0;
string_copy(output, a);
string_cat(output, "/");
string_cat(output, HISTORY_DOC);
return (output);
}
/**
*new_history - creates a histroy file
*@func_data: structure containing a data model
*Return: 1 on success
*/
int new_history(cmd_model *func_data)
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
*new_ll_history - creates a history linked list
*@func_data: structure containing a data model
*@ss: string buffer
*@linecount: history line counter
*Return: 0 Always
*/
int new_ll_history(cmd_modle *func_data, char *ss, int linecount)
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
*arrang_history - rearranges the history linked list
*@func_data: structure containing a data model
*Return: log_counter_row
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
