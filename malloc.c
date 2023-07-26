#include "s_shell.h"
/**
*mem_aloc - fills memory with byte
*@p: pointer to memory
*@c: filled byte
*@n: number of bytes
*Return: pointer to memory
*/
char *mem_aloc(char *p, char c, unsigned int n)
{
unsigned int z;
for (z = 0; z < n; z++)
p[z] = c;
return (p);
}
/**
*str_free - frees a string from memory
*@ss: specified string
*Return: void
*/
void str_free(char **ss)
{
char **c = ss;
if (!ss)
return;
while (*ss)
free(*ss++);
free(c);
}
/**
*_realloc - reallocated a block of memory
*@ptr: pointer to the previous block
*@old_block: size of previous block
*@new_block: size of new block
*Return: void
*/
void *_realloc(void *ptr, unsigned int old_block, unsigned int new_block)
{
char *c;
if (!ptr)
return (malloc(new_block));
if (!new_block)
return (free(ptr), NULL);
if (new_block == old_block)
return (ptr);
c = malloc(new_block);
if (!c)
return (NULL);
old_block = old_block < new_block ? old_block : new_block;
while (old_block--)
c[old_block] = ((char *)ptr)[old_block];
free(ptr);
return (c);
}
