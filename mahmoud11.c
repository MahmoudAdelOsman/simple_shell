#include "s_shell.h"

/**
 * free_memory - frees alocated memory
 * @p: Pointer to free
 * Return: 1 if success
 */

int free_memory(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
