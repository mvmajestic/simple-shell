#include "shell.h"

/**
 * my_alias - the builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: array of arguments.
 * @front: double pointer to beginning of args.
 *
 * Return: If an error occurs - -1, otherwise - 0.
 */

int my_alias(char **args, char __attribute__((__unused__)) **front)

{
	alias_t *tmp = aliases;
	int a, ret = 0;
	char *value;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (ret);
	}
	for (a = 0; args[a]; a++)
	{
		tmp = aliases;
		value = _strchr(args[a], '=');
		if (!value)
		{
			while (tmp)
			{
				if (_strcmp(args[a], tmp->name) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				ret = create_error(args + a, 1);
		}
		else
			set_alias(args[a], value);
	}
	return (ret);
}

/**
 * set_alias - will either set existing alias 'name' with new value,
 * 'value' or creates new alias with 'name' and 'value'.
 * @var_name: name of alias.
 * @value: value of alias. First character is '='.
 */

void set_alias(char *var_name, char *value)

{
	alias_t *tmp = aliases;
	int len, a, b;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (a = 0, b = 0; value[a]; a++)
	{
		if (value[a] != '\'' && value[a] != '"')
			new_value[b++] = value[a];
	}
	new_value[b] = '\0';
	while (tmp)
	{
		if (_strcmp(var_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_value;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - will print alias in format name='value'.
 * @alias: pointer to alias.
 */

void print_alias(alias_t *alias)

{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * replace_aliases - will go through arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to arguments.
 *
 * Return: 2D pointer to arguments.
 */

char **replace_aliases(char **args)

{
	alias_t *tmp;
	int a;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (a = 0; args[a]; a++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(args[a], tmp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, tmp->value);
				free(args[a]);
				args[a] = new_value;
				a--;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (args);
}
