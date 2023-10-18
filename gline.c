#include "main.h"

/**
 * input_buf - buffers chained
 * @info: parameter the struct
 * @buf: buffer addres
 * @len: len var addres
 * Return: bytes
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* fill it if nothing left buffer */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);/* if _strchr(*buf, ';') this a command chain? */
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line in this the newline
 * @info: parameter struct
 * Return: bytes read
*/
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t e, z, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		z = e; /* init new the iterator to the current buf */
		p = buf + e;

		check_chain(info, buf, &z, e, len);
		while (z < len)
		{
			if (is_chain(info, buf, &z))
				break;
			z++;
		}

		e = z + 1;
		if (e >= len)
		{
			e = len = 0; /* reset the length ,  the position */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* back pointer to current the position */
		return (_strlen(p)); /* return the length of current the command */
	}

	*buf_p = buf; /* back buffer from the _getline() */
	return (r); /* return the length of buffer from the _getline() */
}

/**
 * read_buf - reads this is buffer
 * @info: the parameter struct
 * @buf: this buffer
 * @i: this size
 * Return: r
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - give the next line from STDIN
 * @info: parameter this struct
 * @ptr: the address of pointer to buff or nul
 * @length: the size of preallocated pointer buff if not nul
 * Return: s
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t e, len;
	size_t w;
	ssize_t r = 0, s = 0;
	char *p = NULL, *Neww_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (e == len)
		e = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + e, '\n');
	w = c ? 1 + (unsigned int)(c - buf) : len;
	Neww_p = _realloc(p, s, s ? s + w : w + 1);
	if (!Neww_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(Neww_p, buf + e, w - e);
	else
		_strncpy(Neww_p, buf + e, w - e + 1);

	s += w - e;
	e = w;
	p = Neww_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks this ctrl-C
 * @sig_num: signal number
 * Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

