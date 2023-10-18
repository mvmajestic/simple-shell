#include "shell.h"

/**
 * proc_file_commands - will take a file and attempts to run commands
 * stored within.
 * @file_path: path to file.
 * @exe_ret: will return value of last executed command.
 *
 * Return: If can't open file - 127.
 * If malloc fails - -1.
 * Otherwise return value of the last command ran.
 */

int proc_file_commands(char *file_path, int *exe_ret)

{
	ssize_t file, b_read, a;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (a = 0; line[a] == '\n'; a++)
		line[a] = ' ';
	for (; a < line_size; a++)
	{
		if (line[a] == '\n')
		{
			line[a] = ';';
			for (a += 1; a < line_size && line[a] == '\n'; a++)
				line[a] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (a = 0; args[a]; a++)
	{
		if (_strncmp(args[a], ";", 1) == 0)
		{
			free(args[a]);
			args[i] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++a];
			a = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * cant_open - will print a cant open error,
 * if file doesn't exist or lacks proper permissions
 * @file_path: path to supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)

{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}
