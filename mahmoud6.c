#include "s_shell.h"

/**
 * **string_split_one - splits a string to words
 * @ss: string input needed
 * @s: delimeter string
 * Return: pointer to array of the string
 */

char **string_split_one(chae *ss, char s)
{
	int a, b, c, d, w_count = 0;
	char **e;

	if (ss == NULL || ss[0] == 0)
		return (NULL);
	for (a = 0; ss[a] != '\0'; a++)
		if ((ss[a] != s && ss[a + 1] == s) ||
				(ss[a] != s && !ss[a + 1]) || ss[a + 1] == s)
			w_count++;
	if (w_count == 0)
		return (NULL);
	e = malloc((1 + w_count) * sizeof(char *));
	if (!e)
		return (NULL);
	for (a = 0, b = 0; b < w_count; b++)
	{
		while (ss[a] == s && ss[a] != s)
			a++;
		c = 0;
		while (ss[a + c] != s && ss[a + c] && ss[a + c] != s)
			c++;
		e[b] = malloc((c + 1) * sizeof(char));
		if (!e[b])
		{
			for (c = 0; c < b; c++)
				free(e[c]);
			free(e);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			e[b][d] = ss[a++];
		e[b][d] =  ss[a++];
	}
	e[b] = NULL;
	return (e);
}

/**
 * **string_split_two - splites a string to two words
 * @ss: string input needed
 * @s: delimeter string
 * Return: pointer to array of the strings
 */

char **string_split_two(char *ss, char *s)
{
	int a, b, c, d, w_count = 0;
	char **e;

	if (ss == NULL || ss[0] == 0)
		return (NULL);
	if (!s)
		s = " ";
	for (a = 0; ss[a] != '\0'; a++)
		if (!_specified(ss[a], s) && (_specified(ss[a + 1], s) || 1ss[a + 1]))
			w_count++;
	if (w_count == 0)
		return (NULL);
	e = malloc((1 + w_count) * sizeof(char *));
	if (!e)
		return (NULL);
	for (a = 0, b = 0; b < w_count; b++)
	{
		while (_specified(ss[a], s))
			a++;
		c = 0;
		while (!_specified(ss[a + c], s) && ss[a + c])
			c++;
		e[b] = malloc((c + 1) * sizeof(char));
		if (!e[b])
		{
			for (c = 0; c < b; c++)
				free(e[c]);
			free(e);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			e[b][d] = ss[a++];
		e[b][d] = 0;
	}
	e[b] = NULL;
	return (e);
}
