#include "s_shell.h"
/**
*func_ctrl_c - blocks ctrl-c
*@n: first needed input
*Return: void
*/
void func_ctrl_c(__attribute__((unused))int n)
{
_puts("\n");
_puts("$ ");
_putchar(BUFFER_FOR_CLEARING);
}
/**
*buff_chained - buffers chained commands
*@func_data: structure containing a data model
*@input_buffer: buffer input needed
*@input_length: length of a buffer
*Return: reading bytes
*/
ssize_t buff_chained(cmd_model *func_data,
char **input_buffer, size_t *input_length)
{
ssize_t i = 0;
size_t len_p = 0;
if (!*input_length)
{
free(*input_buffer);
*input_buffer = NULL;
signal(SIGINT, func_ctrl_c);
#if GETLINE_USING
i = getline(input_buffer, &len_p, stdin);
#else
i = c_getline(func_data, input_buffer, &len_p);
#endif
if (i > 0)
{
if ((*input_buffer)[i - 1] == '\n')
{
(*input_buffer)[i - 1] = '\0';
i--;
}
func_data->line_count = 1;
change_first_char(*input_buffer);
new_ll_history(func_data, *input_buffer,
func_data->log_counter_row++);
if (c_strchr(*input_buffer, ';'))
{
*input_length = i;
func_data->buf_chain = input_buffer;
}
}
}
return (i);
}
/**
*read_buff_chained - reads a buffer
*@func_data: structure containing a data model
*@input_buffer: buffer input needed
*@input_length: length of buffer
*Return: i
*/
ssize_t read_buff_chained(cmd_model *func_data,
char *input_buffer, size_t *input_length)
{
ssize_t i = 0;
if (*input_length)
return (0);
i = read(func_data->f_read, input_buffer, BUFFER_READ_FUNCTION);
if (i >= 0)
*input_length = i;
return (i);
}
/**
*get_line - gets a line
*@func_data: structure containing a data model
*Return: reading bytes
*/
ssize_t get_line(cmd_model *func_data)
{
static char *c;
static size_t m, n, length;
ssize_t i = 0;
char **p = &(func_data->s_of_arg), *a;
_putchar(BUFFER_FOR_CLEARING);
i = buff_chained(func_data, &c, &length);
if (i == -1)
return (-1);
if (length)
{
n = m;
a = c + m;
chack_chaining_continue(func_data, c, &n, m, length);
while (n < length)
{
if (chack_chaining_delimeter(func_data, c, &n))
break;
n++;
}
m = n + 1;
if (m >= length)
{
m = length = 0;
func_data->c_mode = NORMAL_MODE_COM;
}
*p = a;
return (str_length(a));
}
*p = c;
return (i);
}
/**
*c_getline - gets the next line
*@func_data: structure containing a data model
*@ptr: pointer to character
*@length: length of buffer
*Return: output
*/
int c_getline(cmd_model *func_data, char **ptr, size_t *length)
{
static char read_buffer[BUFFER_READ_FUNCTION];
static size_t i, len;
size_t z;
ssize_t r = 0, output = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p && length)
output = *length;
if (i == len)
i = len = 0;
r = read_buff_chained(func_data, read_buffer, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = c_strchr(read_buffer + i, '\n');
z = c ? 1 + (unsigned int)(c - read_buffer) : len;
new_p = _realloc(p, output, output ? output + z : z + 1);
if (!new_p)
return (p ? free(p), -1 : -1);
if (output)
c_strncat(new_p, read_buffer + i, z - i);
else
c_strncpy(new_p, read_buffer + i, z - i + 1);
output += z - i;
i = z;
p = new_p;
if (length)
*length = output;
*ptr = p;
return (output);
}
