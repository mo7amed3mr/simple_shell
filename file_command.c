#include "shell.h"

/**
 * cant_open - if t doesnt exist print error
 * @file_path: pa the file
 * Return: er 127.
*/
int cant_open(char *file_path)
{
	char *error, *history_str;
	int length;

	history_str = _itoa(history);
	if (!history_str)
		return (127);
	length = _strlen(program_name) + _strlen(history_str) +
		_strlen(file_path) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (127);
	}

	_strcpy(error, program_name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");
	free(history_str);
	write(STDERR_FILENO, error, length);
	free(error);
	return (127);
}

/**
 * read_file - reads it in a buffer
 * @file_path: the path of read
 * @line: a pointer to the bcontent will be stored
 * @exe_ret: pointt stores the return value of the function
 * Return: the size  in bytes, or -1 on failure.
*/
int read_file(char *file_path, char **line, int *exe_ret)
{
	ssize_t file, b_read;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char buffer[120];

	file = open(file_path, O_RDONLY);
	if (file == -1)
		return (*exe_ret = cant_open(file_path));
	*line = malloc(sizeof(char) * old_size);
	if (!*line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		*line = _realloc(*line, old_size, line_size);
		_strcat(*line, buffer);
		old_size = line_size;
		} while (b_read);
	return (line_size);
}

/**
 * proc_file_commands - Takes an the commands stored.
 * @file_path: Path to the fturnue of the last executed command.
 * Return: value
*/
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	history = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}
