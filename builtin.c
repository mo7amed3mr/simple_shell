#include "shell.h"

/**
 * get_builtin - returns a pointer to a builtin
 * function that matches the given command.
 * @command: The command to match.
 * Return: A function pointer to the corresponding builtin.
*/
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shellby_exit - exits the shell program.
 * @args: array of arguments containing the exit value.
 * @front: pointer to the beginning of args.
 * Return: if there are no arguments - -3.
 * if the given exit value is invalid - 2.
 * otherwise  exits with the given status value.
*/
int shellby_exit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args == NULL || args[0] == NULL)
		return (-3);

	if (args[0][0] == '+')
	{
		i = 1;
		len_of_int++;
	}
	for (; args[0][i]; i++)
	{
		if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
			num = (num * 10) + (args[0][i] - '0');
		else
			return (create_error(--args, 2));
	}
	if (args[1] != NULL)
		return (create_error(--args, 2));

	if (num > max - 1)
		return (create_error(--args, 2));

	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * shellby_help - Displays information about shellby builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 * Return: If an error occurs - -1.otherwise - 0.
*/
int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, program_name, _strlen(program_name));

	return (0);
}
