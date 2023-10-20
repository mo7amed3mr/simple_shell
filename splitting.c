#include "shell.h"

/**
 * token_len - ng and a delimiter character as arguments.
 * @str: the g.
 * @delim: thlimiter character.
 * Return: theh of the token.
*/
int token_len(char *str, char *delim)
{
	int index = 0;
	int len = 0;

	while (str[index] != '\0' && str[index] != *delim)
	{
		len++;
		index++;
	}
	return (len);
}

/**
 * count_tokens - Thion takes a string and
 * a delimiter cr as arguments.
 * @str: string.
 * @delim: delimiter character.
 * Return: number of tokens.
*/
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok -  This takes a string and a delimiter
 * character as and returns an array of tokens in the string.
 * @line: thbuffer to start the command.
 * @delim: the ter character.
 * Return: the a of tokens.
*/
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
