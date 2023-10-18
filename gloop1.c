#include "main.h"

/**
 * find_builtin - finds an builtin command
 * @info: parameter & return information the struct
 * Return: if builtin not found -1,
 *	if builtin executed successfully 0,
 *	if builtin found but not successful 1,
 *	if builtin signals exit 2
*/
int find_builtin(info_t *info)
{
	int e, buiilt_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (e = 0; builtintbl[e].type; e++)
		if (_strcmp(info->argv[0], builtintbl[e].type) == 0)
		{
			info->line_count++;
			buiilt_in_ret = builtintbl[e].func(info);
			break;
		}
	return (buiilt_in_ret);
}

/**
 * find_cmd - find a cmd in the current PATH
 * @info: parameter & return information the struct
 * Return: void
*/
void find_cmd(info_t *info)
{
	char *path = NULL;
	int e, z;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (e = 0, z = 0; info->arg[e]; e++)
		if (!is_delim(info->arg[e], " \t\n"))
			z++;
	if (!z)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
