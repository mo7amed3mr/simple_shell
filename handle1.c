#include "shell.h"

/**
 * _strchr - locatacter in a string.
 * @str: the str check.
 * @ch: the er to be located.
 * Return: NUsn’t found.
*/
char *_strchr(char *str, char ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
			return (str);
	}
	str++;
	return (NULL);
}

/**
 * _strlen - retura string.
 * @s: the poine string.
 * Return: thength.
*/
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * _is_included - helper ecks
 * if a charac string.
 * @letter: the cha be check.
 * @prefix: thecheck.
 * Return: 0.
*/
int _is_included(char letter, char *prefix)
{
	while (*prefix != '\0')
	{
		if (*prefix == letter)
		{
			return (1);
		}
		prefix++;
	}
	return (0);
}

/**
 * _strspn - get the length of a prefix substring.
 * @str: the pointer to be string.
 * @prefix: the string to be check.
 * Return: the length.
*/
unsigned int _strspn(char *str, char *prefix)
{
	unsigned int length = 0;

	while (*str != '\0')
	{
		if (_is_included(*str, prefix))
		{
			length++;
		}
		else
		{
			break;
		}
		str++;
	}
	return (length);
}

/**
 * _strcpy - copy a string.
 * @dest: the destination.
 * @src: The source of the string.
 * Return: p.
*/
char *_strcpy(char *dest, char *src)
{
	char *p = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return (p);
}
