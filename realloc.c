#include "shell.h"

/**
 * _memset - fills the memory and constant byte
 * @s: the pointer in the memory area
 * @b: the byte in the fill *s
 * @n: the amount of bytes should be filled
 * Return: (s) this pointer to memory area s
*/
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int e;

	for (e = 0; e < n; e++)
		s[e] = b;
	return (s);
}

/**
 * ffree - frees the string of the strings
 * @pp: string of strings
*/
void ffree(char **pp)
{
	char **w = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(w);
}

/**
 * _realloc - realloc a block of the memory
 * @ptr: the pointer to previous malloc
 * @old_size: byte size of the previous
 * @new_size: byte size of new block
 * Return: pointer to block.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *z;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	z = malloc(new_size);
	if (!z)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		z[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (z);
}
