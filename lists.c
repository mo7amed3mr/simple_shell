#include "shell.h"

/**
 * add_node - adds a node to the start
 * @head: address of pointer
 * @str: str of node
 * @num: node index by history
 * Return: size in the list
*/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *head_new;

	if (!head)
		return (NULL);
	head_new = malloc(sizeof(list_t));
	if (!head_new)
		return (NULL);
	_memset((void *)head_new, 0, sizeof(list_t));
	head_new->num = num;
	if (str)
	{
		head_new->str = _strdup(str);
		if (!head_new->str)
		{
			free(head_new);
			return (NULL);
		}
	}
	head_new->next = *head;
	*head = head_new;
	return (head_new);
}

/**
 * add_node_end - add  node in the end at list
 * @head: address of the pointer
 * @str: the str field at node
 * @num: node index by history
 * Return: size at the list
*/
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *node_new, *node;

	if (!head)
		return (NULL);

	node = *head;
	node_new = malloc(sizeof(list_t));
	if (!node_new)
		return (NULL);
	_memset((void *)node_new, 0, sizeof(list_t));
	node_new->num = num;
	if (str)
	{
		node_new->str = _strdup(str);
		if (!node_new->str)
		{
			free(node_new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = node_new;
	}
	else
		*head = node_new;
	return (node_new);
}

/**
 * print_list_str - prints the str elements of the list_t
 * @h: the pointer to first node
 * Return: size of list
*/
size_t print_list_str(const list_t *h)
{
	size_t e = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		e++;
	}
	return (e);
}

/**
 * delete_node_at_index - deletes node of index
 * @head: address of the pointer
 * @index: index of node should be delete
 * Return: success 1, other 0
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int e = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (e == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		e++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of the lists
 * @head_ptr: address of the pointer head
 * Return: void
*/
void free_list(list_t **head_ptr)
{
	list_t *node, *node_next, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		node_next = node->next;
		free(node->str);
		free(node);
		node = node_next;
	}
	*head_ptr = NULL;
}

