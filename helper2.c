#include "shell.h"

/**
 * get_args - gets the arguments from
 * and performs some operatim.
 * @line: the string buffer the command.
 * @exe_ret: the value of command.
 * Return: NULL if rror, or line.
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line != NULL)
		free(line);
		
	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1 || read == 0)
		return (NULL);

	if (read == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}
	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);
	return (line);
}

/**
 * call_args - partition oper and calls them.
 * @front: the beginni array.
 * @exe_ret: the value ed command.
 * @args: the argof array
 * Return: the rvalue.
*/
int call_args(char **args, char **front, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

