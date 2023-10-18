#include "shell.h"


/**
 * get_args - will get a command from standard input.
 * @line: buffer to store command.
 * @exe_ret: return value of last executed command.
 *
 * Return: if an error occurs - NULL.
 * Otherwise return a pointer to stored command.
 */

char *get_args(char *line, int *exe_ret)

{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - will partition operators from commands and calls them.
 * @args: array of arguments.
 * @front: double pointer to beginning of args.
 * @exe_ret: return value of parent process' last executed command.
 *
 * Return: return value of the last executed command.
 */

int call_args(char **args, char **front, int *exe_ret)

{
	int ret, idx;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], "||", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; index++)
					free(args[idx]);
				return (ret);
			}
		}
		else if (_strncmp(args[idx], "&&", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
 * run_args - will call execution of a command.
 * @args: array of arguments.
 * @front: double pointer to beginning of args.
 * @exe_ret: return value of parent process' last executed command.
 *
 * Return: return value of last executed command.
 */

int run_args(char **args, char **front, int *exe_ret)

{
	int ret, a;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (a = 0; args[a]; a++)
		free(args[a]);

	return (ret);
}

/**
 * handle_args - will get, calls, and runs execution of a command.
 * @exe_ret: return value of parent process' last executed command.
 *
 * Return: if an end-of-file is read - END_OF_FILE (-2).
 * if input cannot be tokenized - -1.
 * otherwise return exit value of last executed command.
 */

int handle_args(int *exe_ret)

{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - will check if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 * Otherwise - 0.
 */

int check_args(char **args)

{
	size_t j;
	char *curr, *nex;

	for (j = 0; args[j]; j++)
	{
		cur = args[j];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (j == 0 || curr[1] == ';')
				return (create_error(&args[j], 2));
			nex = args[j + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[j + 1], 2));
		}
	}
	return (0);
}
