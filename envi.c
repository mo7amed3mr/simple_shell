#include "shell.h"

/**
 * _getenv - takes a string as an argument and return a pointer
 * @var: the name.
 * Return: NULL if no match is found
 * pointer to the environment variable that matches the string
*/
char **_getenv(const char *var)
{
	int index, length;

	length = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], length) == 0)
			return (&environ[index]);
	}
	return (NULL);
}

/**
 * free_env - free the memory allocated
*/
void free_env(void)
{
	int index;

	if (environ == NULL)
		return;
	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _copyenv - copy the environment variable from the global variable
 * Return: new array of strings with the same values
 * NULL if memory allocation fails
*/
char **_copyenv(void)
{
	char **new_env;
	size_t env_size;
	int i;

	for (env_size = 0; environ[env_size]; env_size++)
		;

/**
 * Allocate memory for the new array with enough space for
 * the strings and a NULL pointer
 */
	new_env = malloc(sizeof(char *) * (env_size + 1));
	if (!new_env)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_env[i] = malloc(_strlen(environ[i]) + 1);
		if (!new_env[i])
		{
			for (i--; i >= 0; i--)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[i], environ[i]);
	}
	new_env[i] = NULL;
	return (new_env);
}
