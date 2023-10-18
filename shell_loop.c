#include "shell.h"

/**
 * hsh - main the shell loop
 * @info: par & return info the struct
 * @av: the arg vec from main
 * Return: on success 0, on error 1, or error
*/
int hsh(info_t *info, char **av)
{
	ssize_t x = 0;
	int buiiltiin_ret = 0;

	while (x != -1 && buiiltiin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(info);
		if (x != -1)
		{
			set_info(info, av);
			buiiltiin_ret = find_builtin(info);
			if (buiiltiin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (buiiltiin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (buiiltiin_ret);
}

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

/**
 * fork_cmd - forks thread to run cmd
 * @info: a parameter & return information the struct
 * Return: void
*/
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT at ERROR FUNCTIONS */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT at ERROR FUNCTIONS */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

