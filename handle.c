#include "shell.h"

/**
 * _strcat - Concate two strings.
 * @dest: Pointer to d string.
 * @src: pinter tstring.
 * Return: po destination string.
*/
char *_strcat(char *dest, char *src)
{
	char *p = dest;
	const char *source = src;

	while (*p != '\0')
		p++;

	while (*source != '\0')
		*p++ = *source++;

	*p = '\0';

	return (dest);
}

/**
 * _strncat - concatenatesing by copying n bytes from the source.
 * @dest: the destinastring.
 * @src: the source ing.
 * @n: the numer of bytes to from the source.
 * Return: a poinnation string.
*/
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = '\0';
	return (dest);
}

/**
 * _strcmp - compares ttrings.
 * @s1: the 1st strino be compared.
 * @s2: the secondtring.
 * Return: positineger if s1 > s2
 * 0 if s1 = s2
 * negative iger if s1 < s2
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strncmp - Compares two strings up t compared.
 * @s2: The second strompared.
 * @n: The number of charac
 * Negative inter if s1 < s2
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
