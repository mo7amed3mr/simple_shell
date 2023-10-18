#include "shell.h"

/**
 * is_chain - Test if it's current chr in buffer is a chain the delimeter
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current in buf
 * Return: if chain delimeter 1, other 0
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t z = *p;

	if (buf[z] == '|' && buf[z + 1] == '|')
	{
		buf[z] = 0;
		z++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[z] == '&' && buf[z + 1] == '&')
	{
		buf[z] = 0;
		z++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[z] == ';')
	{
		buf[z] = 0; /* return the semi colon(;) with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = z;
	return (1);
}

/**
 * check_chain - checks when we should the chaining based on last status
 * @info: parameter the struct
 * @buf: char the buffer
 * @p: address in the current position in buffers
 * @i: starting position in bufffers
 * @len: the length of buffers
 * Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t z = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			z = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			z = len;
		}
	}

	*p = z;
}

/**
 * replace_alias - replaces any aliases in tokenized the string
 * @info: the parameter the struct
 * Return: if replaced 1, other 9
*/
int replace_alias(info_t *info)
{
	int e;
	list_t *node;
	char *p;

	for (e = 0; e < 10; e++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in tokenized the string
 * @info: the parameter the struct
 * Return: if replaced 1, other 0
*/
int replace_vars(info_t *info)
{
	int e = 0;
	list_t *node;

	for (e = 0; info->argv[e]; e++)
	{
		if (info->argv[e][0] != '$' || !info->argv[e][1])
			continue;

		if (!_strcmp(info->argv[e], "$?"))
		{
			replace_string(&(info->argv[e]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[e], "$$"))
		{
			replace_string(&(info->argv[e]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[e][1], '=');
		if (node)
		{
			replace_string(&(info->argv[e]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[e], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces the strings
 * @old: address in the old string
 * @new: the new string
 * Return: if replaced 1, other 0
*/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

