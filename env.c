#include "main.h"

/**
 * _myenv - this prints should print the current environ
 * @info: the struct containing arguments.
 *          to constant function the prototype.
 * Return: Always 0
*/
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - give the value of an environ
 * @info: the struct containing arguments.
 * @name: env name
 *
 * Return: the value
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *lump = info->env;
	char *e;

	while (lump)
	{
		e = starts_with(lump->str, name);
		if (e && *e)
			return (e);
		lump = lump->next;
	}
	return (NULL);
}

/**
 * _mysetenv - the Initialize a new environment var.
 * @info: the struct containing potential arguments.
 *  Return: Always 0
*/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - it is remove an environment var.
 * @info: the struct containing potential arguments.
 *		Used to maintain function prototype.
 * Return: Always 0
*/
int _myunsetenv(info_t *info)
{
	int z;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (z = 1; z <= info->argc; z++)
		_unsetenv(info, info->argv[z]);

	return (0);
}
/**
 * populate_env_list - populates env linked list
 * @info: this structure containing potential arguments
 * Return: Always 0
*/
int populate_env_list(info_t *info)
{
	list_t *lump = NULL;
	size_t z;

	for (z = 0; environ[z]; z++)
		add_node_end(&lump, environ[z], 0);
	info->env = lump;
	return (0);
}
