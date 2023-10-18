#include "main.h"

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
