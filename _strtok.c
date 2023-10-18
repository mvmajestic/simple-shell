#include "shell.h"

/**
 * _strtok - work like strtok
 * @str: double pointer of string we want to split
 * @seprator: str of seprator
 * Return: token of split string, NULL otherwise
 */

char *_strtok(char **str, char *seprator)

{
	char *buffer, *token;
	int lensep = strlen(seprator);
	char *cp = *str;

	if (*str == NULL || strcmp(*str, "\0") == 0)
		return (NULL);

	while (strncmp(*str, seprator, 1) == 0)
	{
		*str = strndup(&cp[1], (strlen(*str) - 1));
		cp = *str;
	}

	buffer = strstr(*str, seprator);
	if (buffer == NULL)
	{
		token = *str;
		*str = NULL;
		return (token);
	}
	token = strndup(*str, (strlen(*str) - strlen(buffer)));
	*str = strndup(&buffer[lensep], strlen(buffer) - lensep);
	if (strcmp(token, " ") == 0)
		return (NULL);
	return (token);
}
