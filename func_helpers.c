#include "shell.h"

/**
 * free_args - will Free up memory taken by args.
 * @args: null-terminated double pointer containing commands/arguments.
 * @front: double pointer to beginning of args.
 */

void free_args(char **args, char **front)

{
	size_t a;

	for (a = 0; args[a] || args[a + 1]; a++)
		free(args[a]);

	free(front);
}

/**
 * get_pid - will get current process ID.
 * Description: View stat file, a space-delimited file containing
 * information about current process. The PID is
 * first word in file. The function reads the PID into
 * a buffer and replace space at end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */

char *get_pid(void)

{
	size_t b = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[b] != ' ')
		b++;
	buffer[b] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - will get value corresponding to environmental variable.
 * @beginning: environmental variable to search for.
 * @len: length of environmental variable to search for.
 *
 * Return: If variable is not found - an empty string,
 * otherwise return value of the environmental variable.
 *
 * Description: Variables are stored in format VARIABLE=VALUE.
 */

char *get_env_value(char *beginning, int len)

{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - will handle variable replacement.
 * @line: double pointer containing command and arguments.
 * @exe_ret: pointer to return value of last executed command.
 *
 * Description: Replaces $$ with current PID, $? with return value
 * of last executed program, and envrionmental variables
 * preceded by $ with their corresponding value.
 */

void variable_replacement(char **line, int *exe_ret)

{
	int a, b = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (a = 0; old_line[a]; a++)
	{
		if (old_line[a] == '$' && old_line[a + 1] &&
				old_line[a + 1] != ' ')
		{
			if (old_line[a + 1] == '$')
			{
				replacement = get_pid();
				b = a + 2;
			}
			else if (old_line[a + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				b = a + 2;
			}
			else if (old_line[a + 1])
			{
				for (b = a + 1; old_line[b] &&
						old_line[b] != '$' &&
						old_line[b] != ' '; b++)
					;
				len = b - (a + 1);
				replacement = get_env_value(&old_line[a + 1], len);
			}
			new_line = malloc(a + _strlen(replacement)
					  + _strlen(&old_line[b]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[b]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			a = -1;
		}
	}
}
