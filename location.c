#include "main.h"

/**
 * bfree - frees a the pointer and the NULLs
 * @ptr: the pointer addres
 * Return: if freed 1, other 0.
*/
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
