#include "shell.h"

/**
 * get_builtin - will matche a command with corresponding
 * shell built-in function.
 * @command: command to match.
 *
 * Return: function pointer to corresponding built-in func.
 */

int (*get_builtin(char *command))(char **args, char **front)

{
	builtin_t funcs[] = {
		{ "exit", my_exit },
		{ "env", my_env },
		{ "setenv", my_setenv },
		{ "unsetenv", my_unsetenv },
		{ "cd", my_cd },
		{ "alias", my_alias },
		{ "help", my_help },
		{ NULL, NULL }
	};
	int a;

	for (a = 0; funcs[a].name; a++)
	{
		if (_strcmp(funcs[a].name, command) == 0)
			break;
	}
	return (funcs[a].f);
}
