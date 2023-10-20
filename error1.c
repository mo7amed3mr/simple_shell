#include "shell.h"

/**
 * error_env - creates an error message
 * @args: array passed to comand.
 * Return: error.
*/
char *error_env(char **args)
{
	char *error_msg, *history_str;
	int error_len;

	history_str = _itoa(history);

	if (!history_str)
		return (NULL);

	args--;
	error_len = _strlen(program_name) + _strlen(history_str) +
		_strlen(args[0]) + 45;

	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}
	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, ": Unable to add/remove from enviroment\n");

	free(history_str);
	return (error_msg);
}

/**
 * error_1 - creates an error messsage
 * @args: array passed to the command.
 * Return: The error.
 */

char *error_1(char **args)
{
	char *error_msg;
	int error_len;

	error_len = _strlen(program_name) + _strlen(args[0]) + 13;
	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
		return (NULL);

	_strcpy(error_msg, "alias: ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, " not found\n");

	return (error_msg);
}

/**
 * error_126 - create an error.
 * @args: array passed to the command.
 * Return: the error.
 */

char *error_126(char **args)
{
	char *error_msg, *history_str;
	int error_len;

	history_str = _itoa(history);
	if (!history_str)
		return (NULL);

	error_len = _strlen(program_name) + _strlen(history_str) +
		_strlen(args[0]) + 24;

	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
		return (NULL);

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, ": Permission denied\n");

	free(history_str);
	return (error_msg);
}

/**
 * error_127 - creates an error message.
 * @args: array passsed to the command.
 * Return: the error.
*/
char *error_127(char **args)
{
	char *error_msg, *history_str;
	int error_len;

	history_str = _itoa(history);
	if (!history_str)
		return (NULL);

	error_len = _strlen(program_name) + _strlen(history_str) +
		_strlen(args[0]) + 16;

	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, ": not found\n");

	free(history_str);
	return (error_msg);
}
