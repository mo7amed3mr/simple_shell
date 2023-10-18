#include "shell.h"

/**
 * list_len - determines the length in the linked lists
 * @h: the ptr to the first node
 * Return: size of the list
*/
size_t list_len(const list_t *h)
{
	size_t e = 0;

	while (h)
	{
		h = h->next;
		e++;
	}
	return (e);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
*/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t e = list_len(head), z;
	char **strings;
	char *str;

	if (!head || !e)
		return (NULL);
	strings = malloc(sizeof(char *) * (e + 1));
	if (!strings)
		return (NULL);
	for (e = 0; node; node = node->next, e++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (z = 0; z < e; z++)
				free(strings[z]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[e] = str;
	}
	strings[e] = NULL;
	return (strings);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
*/
size_t print_list(const list_t *h)
{
	size_t e = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		e++;
	}
	return (e);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or nul
*/
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t e = 0;

	while (head)
	{
		if (head == node)
			return (e);
		head = head->next;
		e++;
	}
	return (-1);
}

