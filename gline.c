#include "shell.h"

/**
 * _realloc - Reallocates a memory ng malloc and free.
 * @ptr: A pointer to the memviously ayt for ptr.
 * @new_size: The size in bytes for the new memory block.
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 ahe realted memory block.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
 * _getline - reds input.
 * @lineptr: buffer to store the input.
 * @n: the ze.
 * @stream: the stram to read from.
 * Return: the number bytes.
*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer, *tmp;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 10);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		buffer[input] = c;
		input++;

		if (input % 10 == 0)
		{
			tmp = realloc(buffer, input + 10);
			if (!tmp)
			{
				free(buffer);
				return (-1);
			}
			buffer = tmp;
		}
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}

/**
 * assign_lineptr - reassign theiable.
 * @lineptr: buffer tonput.
 * @n: thesize.
 * @buffer: the stri be assigned.
 * @b: the size ffer.
*/
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		*n = (b > 120) ? b : 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		*n = (b > 120) ? b : 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		if (buffer != NULL)
			free(buffer);
	}
}
