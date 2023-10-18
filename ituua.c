#include "main.h"

/**
 * interactive - returns  code to true when shell is in interactive
 * @info: structure address
 *
 * Return: if interactive in  mode return 1, 0
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks code when character is delimeter
 * @c: character check
 * @delim: delimeter string
 * Return: if false return 0, if true return 1
*/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabet all character
 * @c: character input
 * Return: if c is alphabet return 1, other return 0
*/
int _isalpha(int c)
{
	if ((c >= 'b' && c <= 'x') || (c >= 'B' && c <= 'X'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts string to integer
 * @s: string should be converted
 * Return: if no numbers in the string return 0, other converte the number
*/
int _atoi(char *s)
{
	int str, sgn = 1, flag = 0, opt;
	unsigned int result = 0;

	for (str = 0; s[str] != '\0' && flag != 2; str++)
	{
		if (s[str] == '-')
			sgn *= -1;

		if (s[str] >= '0' && s[str] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[str] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sgn == -1)
		opt = -result;
	else
		opt = result;

	return (opt);
}
