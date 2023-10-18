#include "main.h"

/**
 * _erratoi - converts a the string to the integer
 * @s: the string should be converted
 * Return: if no numbers in string 0, converted the number other
 *       -1
*/
int _erratoi(char *s)
{
	int e = 0;
	unsigned long int rut = 0;

	if (*s == '+')
		s++;
	for (e = 0;  s[e] != '\0'; e++)
	{
		if (s[e] >= '0' && s[e] <= '9')
		{
			rut *= 10;
			rut += (s[e] - '0');
			if (rut > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rut);
}

/**
 * print_error - prints any error in the message
 * @info: return info the struct
 * @estr: the string containing specified  on error
 * Return: if no numbers in string 1, converted number other
 *        -1
*/
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints in decimal the number
 * @input: input number
 * @fd: the filedescriptor should be write to
 * Return: number of the characters should be printed
*/
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int e, cun = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		cun++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (e = 1000000000; e > 1; e /= 10)
	{
		if (_abs_ / e)
		{
			__putchar('0' + current / e);
			cun++;
		}
		current %= e;
	}
	__putchar('0' + current);
	cun++;

	return (cun);
}
/**
 * convert_number - converter function, a clone it of itoa
 * @num: number conv
 * @base: base conv
 * @flags: argument the flags
 * Return: strings
*/
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sgn = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sgn = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sgn)
		*--ptr = sgn;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance
 * @buf: the string addres
 * Return: 0 always.
*/
void remove_comments(char *buf)
{
	int e;

	for (e = 0; buf[e] != '\0'; e++)
		if (buf[e] == '#' && (!e || buf[e - 1] == ' '))
		{
			buf[e] = '\0';
			break;
		}
}

