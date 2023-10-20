#include "shell.h"

/**
 * check_args - checks the arguments passed to a shell command.
 * @args: the argument of.
 * Return: zero if no errors found.
*/
int check_args(char **args)
{
	size_t i;
	char *current, *next;

	for (i = 0; args[i]; i++)
	{
		current = args[i];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (i == 0 || current[1] == ';')
			{
				return (create_error(&args[i], 2));
			}
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}

	}
	return (0);
}

/**
 * handle_args - handles the command and executes.
 * @exe_ret: the value oed command.
 * Return: in the off file, it cannot be tokenized -1
 * exit value.
*/
int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * run_args - runs the ard to a shell
 * command and retesult.
 * @args: the argume array.
 * @front: the beginnthe array.
 * @exe_ret: the of executed command.
 * Return: the fiurn value.
*/
int run_args(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	history++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}
