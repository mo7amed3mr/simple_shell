#include "main.h"

/**
 * _strcpy - copies the string
 * @dest: destination
 * @src: source
 * Return: the pointer to the destination
*/
char *_strcpy(char *dest, char *src)
{
	int e = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[e])
	{
		dest[e] = src[e];
		e++;
	}
	dest[e] = 0;
	return (dest);
}

/**
 * _strdup - duplicates the string
 * @str: string in the duplicate
 * Return: the pointer to the duplicated strings
*/
char *_strdup(const char *str)
{
	int le = 0;
	char *rret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		le++;
	rret = malloc(sizeof(char) * (le + 1));
	if (!rret)
		return (NULL);
	for (le++; le--;)
		rret[le] = *--str;
	return (rret);
}

/**
 * _puts - prints an input the strings
 * @str: the strings should be printed
 * Return: Nothing
*/
void _puts(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_putchar(str[e]);
		e++;
	}
}

/**
 * _putchar - type character c to the stdout
 * @c: character should be print
 * Return: if success 1.
 * On error, is returned -1, and errno is appropriately.
*/
int _putchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(1, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

