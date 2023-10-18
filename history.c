#include "shell.h"

/**
 * get_history_file - gets the history all files
 * @info: para the struct
 * Return: allocated yhe string of history file
*/
char *get_history_file(info_t *info)
{
	char *buf, *direc;

	direc = _getenv(info, "HOME=");
	if (!direc)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, direc);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates the file
 * @info: parameter the struct
 * Return: success 1, other -1
*/
int write_history(info_t *info)
{
	ssize_t fd;
	char *namefile = get_history_file(info);
	list_t *node = NULL;

	if (!namefile)
		return (-1);

	fd = open(namefile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(namefile);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from the file
 * @info: the parameter the struct
 * Return: on success hiscount, other 0
*/
int read_history(info_t *info)
{
	int e, llast = 0, linecount = 0;
	ssize_t fd, rln, wsizee = 0;
	struct stat st;
	char *buf = NULL, *namefile = get_history_file(info);

	if (!namefile)
		return (0);

	fd = open(namefile, O_RDONLY);
	free(namefile);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		wsizee = st.st_size;
	if (wsizee < 2)
		return (0);
	buf = malloc(sizeof(char) * (wsizee + 1));
	if (!buf)
		return (0);
	rln = read(fd, buf, wsizee);
	buf[wsizee] = 0;
	if (rln <= 0)
		return (free(buf), 0);
	close(fd);
	for (e = 0; e < wsizee; e++)
		if (buf[e] == '\n')
		{
			buf[e] = 0;
			build_history_list(info, buf + llast, linecount++);
			llast = e + 1;
		}
	if (llast != e)
		build_history_list(info, buf + llast, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry on history linked the list
 * @info: the Structure containing potential arguments
 * @buf: the buffer
 * @linecount: history to linecount, to histcount
 * Return: Always 0
*/
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list
 * @info: the Structure containing potential arguments
 * Return: the new histcount
*/
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int e = 0;

	while (node)
	{
		node->num = e++;
		node = node->next;
	}
	return (info->histcount = e);
}

