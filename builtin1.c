#include "shell.h"

/**
 * _myhistory - displays history the list, one of command by line, preceded
 *              with the line numbers, starting from 0.
 * @info: the struct containing potential arguments.
 *		for constant function prototype.
 * Return: 0 always
*/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to the strings
 * @info: parameter the structure
 * @str: string
 * Return: success 0,  error 1.
*/
int unset_alias(info_t *info, char *str)
{
	char *q, w;
	int rett;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	w = *q;
	*q = 0;
	rett = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = w;
	return (rett);
}

/**
 * set_alias - this code sets alias to the all string
 * @info: this is the parameter the structure
 * @str: string
 * Return: if success return 0, if error return 1
*/
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - this prints an alias the string in code
 * @node: aliass node
 * Return: if success 0, if error 1
*/
int print_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias the builtin
 * @info: the structure containing arguments. to main prototype.
 * Return: 0 always.
*/
int _myalias(info_t *info)
{
	int e = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (e = 1; info->argv[e]; e++)
	{
		q = _strchr(info->argv[e], '=');
		if (q)
			set_alias(info, info->argv[e]);
		else
			print_alias(node_starts_with(info->alias, info->argv[e], '='));
	}

	return (0);
}
