#include "shell.h"

/**
 * my_exit - will exit shell.
 * @args: array of arguments containing exit value.
 * @front: double pointer to beginning of args.
 *
 * Return: there are no arguments - -4.
 * given exit value is invalid - 2.
 * O - exits with given status value.
 *
 * Description: after returning -4, the program exits back to main function.
 */

int my_exit(char **args, char **front)

{
	int a, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			a = 1;
			len_of_int++;
		}
		for (; args[0][a]; a++)
		{
			if (a <= len_of_int && args[0][a] >= '0' && args[0][a] <= '9')
				num = (num * 10) + (args[0][a] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-4);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * my_cd - will change current directory of the shell process.
 * @args: array of arguments.
 * @front: double pointer to beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 * If an error occurs - -5, otherwise - 0.
 */

int my_cd(char **args, char __attribute__((__unused__)) **front)

{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-5);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-5);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-5);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shellby_setenv(dir_info, dir_info) == -5)
		return (-5);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shellby_setenv(dir_info, dir_info) == -5)
		return (-5);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * my_help - will display information about shell built-in commands.
 * @args: array of arguments.
 * @front: pointer to beginning of args.
 *
 * Return: If an error occurs - -1, otherwise - 0.
 */

int my_help(char **args, char __attribute__((__unused__)) **front)

{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));
	return (0);
}
