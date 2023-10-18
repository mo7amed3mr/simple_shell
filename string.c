#include "shell.h"

/**
 * _strlen - returns the length of the strings
 * @s: the string checks
 * Return: integer the length of the string
*/
int _strlen(char *s)
{
	int e = 0;

	if (!s)
		return (0);

	while (*s++)
		e++;
	return (e);
}

/**
 * _strcmp - performs lexicogarphic  of two strangs.
 * @s1: first the string
 * @s2: second the string
 * Return: if s1 < s2 negetive, if s1 > s2 positive, if s1 == s2 zero
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - check if the needle starts
 * @haystack: the strings should be search
 * @needle: substring should be find
 * Return: the address of haystack or No
*/
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates the two strings
 * @dest: destination buff
 * @src: source buff
 * Return: the pointer to destination buff
*/
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

