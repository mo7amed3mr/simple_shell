#include "shell.h"

char *program_name;
int history;
alias_t *aliases;

/**
 * signal_handler - handles the SIGINT signal by printing a new prompt
 * @sign: the signal number
 * Return: nothing
 */

void signal_handler(int sign)
{
	char *new_prompt = "\n$ ";

	(void)sign; /* to avoid unused variable warning */

	signal(SIGINT, signal_handler); /*This is to reset the signal handler */
	write(STDIN_FILENO, new_prompt, 3); /*this is to print a new prompt */
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @frnt: A double pointer to the beginning of args.
 * Return: If an error occurs - a corresponding error code.
 * O/w - The exit value of the last executed command.
 */

int execute(char **args, char **frnt)
{
	char *command = args[0];
	int flag = 0, ret = 0;

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_error(args, 126));
		else
			ret = (create_error(args, 127));
	}
	else
	{
		ret = execute_command(command, args, frnt);
	}

	if (flag)
		free(command);
	return (ret);
}

/**
 * execute_command - executes a given command with the
 * given arguments and environment variables
 * @command: the command to execute
 * @args: the array of arguments
 * @frnt: a pointer to the first element of args
 * Return: the exit status of the command
 */

int execute_command(char *command, char **args, char **frnt)
{
	pid_t child_pid;
	int status, ret = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error child:");
		return (1);
	}
	if (child_pid == 0)
	{
		execve(command, args, environ);
		if (errno == EACCES)
			ret = (create_error(args, 126));
		free_env();
		free_args(args, frnt);
		free_alias_list(aliases);
		_exit(ret);
	}
	else
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	return (ret);
}

/**
 * main - the main function of a shell program
 * @argc: the number of arguments
 * @argv: the array of arguments
 * Return: the execution return value
 *
 * Description: This function initializes some global variables,
 * registers a signal handler,
 * copies the environment variables,
 * and handles different modes of input.
 */

int main(int argc, char *argv[])
{
	int ret = 0;
	int retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	program_name = argv[0];
	history = 1;
	aliases = NULL;
	signal(SIGINT, signal_handler);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret);
}
