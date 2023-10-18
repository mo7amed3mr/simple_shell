#include "shell.h"

/**
 * _eputs - prints an input the string
 * @str: the string should be printed
 * Return: Null
*/
void _eputs(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_eputchar(str[e]);
		e++;
	}
}

/**
 * _eputchar - writes characters c to the stderr
 * @c: characters should be print
 * Return: success 1.
 * On error, -1 at returned, and errno is set the appropriately.
*/
int _eputchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(2, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 * _putfd - writes characters c of given a fd
 * @c: characters to print
 * @fd: filedescriptor should be write
 * Return: success 1.
 * error, -1 at returned, and errno is set the appropriately.
*/
int _putfd(char c, int fd)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(fd, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}
/**
 * _putsfd - prints an input the string
 * @str: string should be printed
 * @fd: filedescriptor should be write
 * Return: the number of the char inputs
*/
int _putsfd(char *str, int fd)
{
	int e = 0;

	if (!str)
		return (0);
	while (*str)
	{
		e += _putfd(*str++, fd);
	}
	return (e);
}

