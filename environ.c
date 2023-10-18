#include "shell.h"

/**
 * _getenv - will recieve an environmental variable from PATH.
 * @var: name of environmental variable to get.
 *
 * Return: if environmental variable does not exist - NULL,
 * otherwise - a pointer to environmental variable.
 */

char **_getenv(const char *var)

{
	int idx, len;

	len = _strlen(var);
	for (idx = 0; environ[idx]; idx++)
	{
		if (_strncmp(var, environ[idx], len) == 0)
			return (&environ[idx]);
	}

	return (NULL);
}

/**
 * _copyenv - will create copy of environment.
 *
 * Return: if error occurs - NULL.
 *         O - a double pointer to new copy.
 */

char **_copyenv(void)

{
	char **new_environ;
	size_t size;
	int idx;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (idx = 0; environ[idx]; idx++)
	{
		new_environ[idx] = malloc(_strlen(environ[idx]) + 1);

		if (!new_environ[idx])
		{
			for (idx--; idx >= 0; idx--)
				free(new_environ[idx]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[idx], environ[idx]);
	}
	new_environ[idx] = NULL;

	return (new_environ);
}

/**
 * free_env - will free environment copy.
 */

void free_env(void)

{
	int idx;

	for (idx = 0; environ[idx]; idx++)
		free(environ[idx]);
	free(environ);
}
