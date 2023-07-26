#include "s_shell.h"

/**
 * clear_node_of_list - clears nodes of linked list
 * @head_p: Pointer to the first node
 * Return: Void
 */

void clear_node_of_list(l_list **head_p)
{
	l_list *node, *next_node, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		next_node = node->nxt;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_p = NULL;
}

/**
 * print_linked_list - prints a string of elements of linked list
 * @n: pointer to the first node
 * Return: length of linked list
 */

size_t print_linked_list(const l_list *n)
{
	size_t x = 0;

	while (n)
	{
		_puts(n->str ? n->str : "(nil)");
		_puts("\n");
		n = n->nxt;
		x++;
	}
	return (x);
}

/**
 * add_node_at_start - adds new node at the start of the ll
 * @head: Pointer to the first node
 * @str: String of node
 * @n: Node index
 * Return: Length of linked list
 */

l_list *add_node_at_start(l_list **head, const char *str, int n)
{
	l_list *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(l_list));
	if (!new_head)
		return (NULL);
	mem_aloc((void *)new_head, 0, sizeof(l_list));
	new_head->number = n;
	if (str)
	{
		new_head->str = string_duplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->nxt = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_at_end - adds new node at the end of ll
 * @head: pointer to the first node
 * @str: string of node
 * @n: Node index
 * Return: Length of linked list
 */

l_list *add_node_at_end(l_list **head, const char *str, int n)
{
	l_list *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(l_list));
	if (!new_node)
		return (NULL);
	mem_aloc((void *)new_node, 0, sizeof(l_list));
	new_node->number = n;
	if (str)
	{
		new_node->str = string_duplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nxt)
			node = node->nxt;
		node->nxt = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * remove_node_from_index - removes node at a specified index
 * @head: pointer to the first node
 * @index: node index to be removed
 * Return: 1 if success
 */

int remove_node_from_index(l_list **head, unsigned int index)
{
	l_list *node, *prev_node;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->nxt;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (x == index)
		{
			prev_node->nxt = node->nxt;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->nxt;
	}
	return (0);
}
