#include "shell.h"

/**
 * my_env - will print current environment.
 * @args: array of arguments passed to shell.
 * @front: double pointer to beginning of args.
 *
 * Return: if an error occurs - -1, otherwise - 0.
 *
 * Description: will print one variable per line in
 * format 'variable'='value'.
 */
int my_env(char **args, char __attribute__((__unused__)) **front)
{
	int idx;
	char cr = '\n';

	if (!environ)
		return (-1);

	for (idx = 0; environ[idx]; idx++)
	{
		write(STDOUT_FILENO, environ[idx], _strlen(environ[idx]));
		write(STDOUT_FILENO, &cr, 1);
	}

	(void)args;
	return (0);
}

/**
 * my_setenv - will change or adds an environmental variable to PATH.
 * @args: array of arguments passed to shell.
 * @front: double pointer to beginning of args.
 * Description: args[1] is name of new or existing PATH variable.
 *              args[2] is value to set new or changed variable to.
 *
 * Return: If an error occurs - -1, otherwise - 0.
 */

int my_setenv(char **args, char __attribute__((__unused__)) **front)

{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int idx;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (idx = 0; environ[idx]; idx++)
		new_environ[idx] = environ[idx];

	free(environ);
	environ = new_environ;
	environ[idx] = new_value;
	environ[idx + 1] = NULL;

	return (0);
}

/**
 * my_unsetenv - will remove an environmental variable from PATH.
 * @args: array of arguments passed to shell.
 * @front: double pointer to beginning of args.
 * Description: args[1] is PATH variable to remove.
 *
 * Return: If an error occurs - -1, otherwise - 0.
 */

int my_unsetenv(char **args, char __attribute__((__unused__)) **front)

{
	char **env_var, **new_environ;
	size_t size;
	int idx, idx2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (idx = 0, idx2 = 0; environ[idx]; idx++)
	{
		if (*env_var == environ[idx])
		{
			free(*env_var);
			continue;
		}
		new_environ[idx2] = environ[idx];
		idx2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
