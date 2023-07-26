#include "s_shell.h"
/*
*c_alias run alias command
*@func_data: structure containing a data model
*retun 0 always
*/

int c_alias(cmd_model *func_data)
{
int z = 0;
char *c = Null;
l_list *x = Null;
if (func_data->arg_c == 1)
{
x = func_data->alias;
while (x)
{
p_alias(x);
x= x->nxt;
}
return (0);
}
for (z = 1; func_data->arg_v[z]; z++)
c = c_strchr(func_data->arg_v[z],'=');
if (c)
add_alias(func_data, func_data->arg_v[z]);
else
p_alias(get_prefix(func_data->alias, func_data->arg_v[z]z, '='));
}
return (0);
}
/**
*p_alias - prints an alias string
*@x: alias node
*return 0 on success
*/
int p_alias(l_list *x)
{
char *ptr = Null, *c = Null;
if (x)
{
ptr = c_strchr(x->str, '=')
for (c = x->str; c<= ptr; c++)
_putchar(*c);
_putchar('/');
_puts(ptr + 1);
_puts("\n");
return (0);
}
return (1);
}
/**
*add_alias - adds alias string
*@func_data structure containing a data model
*@s_a: string alias
*return: 0 on success
*/
int add_alias(cmd_model *fun_data, char *s_a)
{
char *ptr;
ptr = c_strchr(s_a, '=');
if (!ptr)
rturn (1);
if (!*++ptr)
return (delete_alias(func_data, s_a));
delete_alias(func_data, s_a);
return (add_node_at_end(&(func_data->alias), s_a, 0) == Null);
}
/**
*delete_alias - removes alisa string
*@func_data: structure containing a data model
*@s_a: string alias
*return: 0 on success
*/
int delete_alias(cmd_model *func_data, char *s_a)
{
char *ptr, c;
int output;
ptr = c_strchr(s_a, '=');
if (!ptr)
returen (1);
c = *ptr;
*ptr = 0;
output = remove_node_from_index(&(func_data->alias),
index_node(func_data->alias, get_prefix(func_data->alias, s_a, -1)));
*ptr = c;
return (output);
}
/**
*c_history - run history linked list
*@func_data: structure contatining a data model
*return: 0 always
*/
int c_histroy(cmd_model *func_data)
{
print_list(func_data->history);
return (0);
}