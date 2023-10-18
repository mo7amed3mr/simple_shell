#include "shell.h"

/**
 * _strncpy - copies the string
 * @dest: the destination string will be copied
 * @src: sourse string
 * @n: amount of characters will be copied
 * Return: concatenated string
*/
char *_strncpy(char *dest, char *src, int n)
{
	int e, z;
	char *s = dest;

	e = 0;
	while (src[e] != '\0' && e < n - 1)
	{
		dest[e] = src[e];
		e++;
	}
	if (e < n)
	{
		z = e;
		while (z < n)
		{
			dest[z] = '\0';
			z++;
		}
	}
	return (s);
}
/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
*/
char *_strncat(char *dest, char *src, int n)
{
	int e, z;
	char *s = dest;

	e = 0;
	z = 0;
	while (dest[e] != '\0')
		e++;
	while (src[z] != '\0' && z < n)
	{
		dest[e] = src[z];
		e++;
		z++;
	}
	if (z < n)
		dest[e] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
*/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
