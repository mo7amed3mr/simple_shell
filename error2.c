#include "shell.h"

/**
 * error_syntax - error message.
 * @args: array comand.
 * Return: errors.
*/
char *error_syntax(char **args)
{
	char *error_msg, *history_str;
	int error_len;

	history_str = _itoa(history);
	if (!history_str)
		return (NULL);

	error_len = _strlen(program_name) + _strlen(history_str) +
		strlen(args[0]) + 33;
	error_msg = malloc(sizeof(char) * (error_len + 1));

	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": Syntax error: \"");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, "\" unexpected\n");

	free(history_str);
	return (error_msg);
}

/**
 * error_exit - ate an error message.
 * @args: arassed to command.
 * Return: thrror.
*/
char *error_exit(char **args)
{
	char *error_msg, *history_str;
	int error_len;

	history_str = _itoa(history);
	if (!history_str)
		return (NULL);

	error_len = _strlen(program_name) + _strlen(history_str) +
		_strlen(args[0]) + 27;

	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": exit: Illegal number: ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, "\n");

	free(history_str);
	return (error_msg);
}

/**
 * error_cd - cre an error message.
 * @args: arra to command.
 * Return: the eror.
 */

char *error_cd(char **args)
{
	char *error_msg, *history_str;
	int error_len;

	history_str = _itoa(history);
	if (!history_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';

	error_len = _strlen(program_name) + _strlen(history_str) +
		_strlen(args[0]) + 24;
	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	if (args[0][0] == '-')
		_strcat(error_msg, ": cd: Illegal option ");
	else
		_strcat(error_msg, ": cd: can't cd to ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, "\n");

	free(history_str);
	return (error_msg);
}
