#include "shell.h"

/**
 * add_node_end - adds a new the end of a linked list of directories
 * @head: the headlist
 * @dir: path for ode
 * Return: new node , null error
*/
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *last;
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);
	new_node->dir = dir;
	new_node->next = NULL;
	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * add_alias_end - adds a new alias at the end of a linked list of aliases
 * @head: pointer to the head of the list
 * @name: ame of the new alias to add
 * @value: value of the new alias
 * Return: the new node, NULL if fail
*/
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);
	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
 * free_list - frees a liectories
 * @head: the head
 */

void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}

/**
 * free_alias_list - free a alias lined.
 * @head: the head of.
*/
void free_alias_list(alias_t *head)
{
	alias_t *next;

	if (head == NULL)
		return;
	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}
