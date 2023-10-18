#include "shell.h"

/**
 * fill_path_dir - will copy path and replace leading/sandwiched/trailing
 * colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 * with the current working directory.
 */

char *fill_path_dir(char *path)

{
	int a, len = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (a = 0; path[a]; a++)
	{
		if (path[a] == ':')
		{
			if (path[a + 1] == ':' || a == 0 || path[a + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (a = 0; path[a]; a++)
	{
		if (path[a] == ':')
		{
			if (a == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[a + 1] == ':' || path[a + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[a], 1);
		}
	}
	return (path_copy);
}


/**
 * get_location - will locate a command in PATH.
 * @command: command to locate.
 *
 * Return: If error occurs or command cannot be located - NULL.
 * Otherwise return full pathname of  command.
 */

char *get_location(char *command)

{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * get_path_dir - will tokenize colon-separated list of
 * directories into a list_s linked list.
 * @path: colon-separated list of directories.
 *
 * Return: pointer to initialized linked list.
 */

list_t *get_path_dir(char *path)

{
	int idx;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (idx = 0; dirs[idx]; idx++)
	{
		if (add_node_end(&head, dirs[idx]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
