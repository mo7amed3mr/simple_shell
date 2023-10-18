#include "shell.h"

/**
 * is_cmd - determines cmd
 * @info: info the struct
 * @path: the path to the file
 * Return: if true 1, other 0
*/
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates the character
 * @pathstr: the PATH pf the string
 * @stop: stop index
 * @start: start index
 * Return: the pointer to new buff
*/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int e = 0, z = 0;

	for (z = 0, e = start; e < stop; e++)
		if (pathstr[e] != ':')
			buf[z++] = pathstr[e];
	buf[z] = 0;
	return (buf);
}

/**
 * find_path - find the cmd in the PATH str
 * @info: info of the struct
 * @pathstr: the PATH str
 * @cmd: the cmd findded
 * Return: full path of cmd foundd or no
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int e = 0, ccur_ps = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[e] || pathstr[e] == ':')
		{
			path = dup_chars(pathstr, ccur_ps, e);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[e])
				break;
			ccur_ps = e;
		}
		e++;
	}
	return (NULL);
}

