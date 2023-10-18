#include "shell.h"

/**
 * get_environ - returns the string array
 * @info: Structure containing arguments. Used to
 *          constant prototype.
 * Return: Always 0
*/
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove any environment var
 * @info: the Structure containing arguments. Used to
 *        constant prototype.
 *  Return: if delete 1, other 0
 * @var: string env var
*/
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t e = 0;
	char *w;

	if (!node || !var)
		return (0);

	while (node)
	{
		w = starts_with(node->str, var);
		if (w && *w == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), e);
			e = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		e++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment var
 * @info: Structure containing potential arguments. Used to
 *        constant prototype.
 * @var: string env var property
 * @value: string env var value
 * Return: Always 0
*/
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *w;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		w = starts_with(node->str, var);
		if (w && *w == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}


