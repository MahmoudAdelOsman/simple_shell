#include "s_shell.h"
/**
*ll_size - determines length of linked list
*@n: pointer to first node
*Return: length of linked list
*/
size_t ll_size(const l_list *n)
{
size_t z;
for (z = 0; n; z++)
n = n->nxt;
return (z);
}
/**
*ll_array - returns an array of strings of list->str
*@head: pointer to the first node
*Return: array of strings
*/
char **ll_array(l_list *head)
{
l_list *node = head;
size_t m = ll_size(head);
size_t n;
char **sss;
char *ss;
if (!head || !m)
return (NULL);
sss = malloc(sizeof(char *) * (m + 1));
if (!sss)
return (NULL);
for (m = 0; node; node = node->nxt, m++)
{
ss = malloc(str_length(node->str) + 1);
if (!ss)
{
for (n = 0; n < m; n++)
free(sss[n]);
free(sss);
return (NULL);
}
ss = string_copy(ss, node->str);
sss[m] = ss;
}
sss[m] = NULL;
return (sss);
}
/**
*print_list - prints all elements of a linked list
*@n: pointer to the first node
*Return: length of linked list
*/
size_t print_list(const l_list *n)
{
size_t r;
for (r = 0; n; r++)
{
_puts(num_to_str(n->number, 10, 0));
_putchar(':');
_putchar(' ');
_puts(n->str ? n->str : "(nil)");
_puts("\n");
n = n->nxt;
}
return (r);
}
/**
*get_prefix - returns node which has a specified prefix
*@node: pointer to first node
*@prefix: string input needed
*@c: character input
*Return: matched node
*/
l_list *get_prefix(l_list *node, char *prefix, char c)
{
char *s = NULL;
while (node)
{
s = haystack_check(node->str, prefix);
if (s && ((c == -1) || (*s == c)))
return (node);
node = node->nxt;
}
return (NULL);
}
/**
*index_node - gets index of a node
*@head: pointer to the first node
*@node: pointer to a node
*Return: index of a node
*/
ssize_t index_node(l_list *head, l_list *node)
{
size_t z;
for (z = 0; head; z++)
{
if (head == node)
return (z);
head = head->nxt;
}
return (-1);
}
