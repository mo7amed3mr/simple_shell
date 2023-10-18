#include "shell.h"

/**
 * **strtow - splits a the strings into the words. Repeat delimiter
 * @str: the input the string
 * @d: the delimeter the string
 * Return: a the pointers to array of the strings, or NULL
*/
char **strtow(char *str, char *d)
{
	int e, z, w, k, numberwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (e = 0; str[e] != '\0'; e++)
		if (!is_delim(str[e], d) && (is_delim(str[e + 1], d) || !str[e + 1]))
			numberwrds++;

	if (numberwrds == 0)
		return (NULL);
	s = malloc((1 + numberwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (e = 0, z = 0; z < numberwrds; z++)
	{
		while (is_delim(str[e], d))
			e++;
		k = 0;
		while (!is_delim(str[e + k], d) && str[e + k])
			k++;
		s[z] = malloc((k + 1) * sizeof(char));
		if (!s[z])
		{
			for (k = 0; k < z; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (w = 0; w < k; w++)
			s[z][w] = str[e++];
		s[z][w] = 0;
	}
	s[z] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int e, z, k, w, numberwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (e = 0; str[e] != '\0'; e++)
		if ((str[e] != d && str[e + 1] == d) ||
				    (str[e] != d && !str[e + 1]) || str[e + 1] == d)
			numberwrds++;
	if (numberwrds == 0)
		return (NULL);
	s = malloc((1 + numberwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (e = 0, z = 0; z < numberwrds; z++)
	{
		while (str[e] == d && str[e] != d)
			e++;
		k = 0;
		while (str[e + k] != d && str[e + k] && str[e + k] != d)
			k++;
		s[z] = malloc((k + 1) * sizeof(char));
		if (!s[z])
		{
			for (k = 0; k < z; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (w = 0; w < k; w++)
			s[z][w] = str[e++];
		s[z][w] = 0;
	}
	s[z] = NULL;
	return (s);
}
