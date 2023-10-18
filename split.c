#include "shell.h"

/**
 * token_len - will find the delimiter index marking end
 * of the first token contained within a string.
 * @str: string to be searched.
 * @delim: delimiter character.
 *
 * Return: delimiter index marking end of
 * the intitial token pointed to be str.
 */

int token_len(char *str, char *delim)

{
	int idx = 0, len = 0;

	while (*(str + idx) && *(str + idx) != *delim)
	{
		len++;
		idx++;
	}

	return (len);
}

/**
 * count_tokens - will count number of delimited words
 * contained within a string.
 * @str: string to be searched.
 * @delim: delimiter character.
 *
 * Return: number of words contained within str.
 */

int count_tokens(char *str, char *delim)

{
	int idx, tokens = 0, len = 0;

	for (idx = 0; *(str + idx); idx++)
		len++;

	for (idx = 0; idx < len; idx++)
	{
		if (*(str + idx) != *delim)
		{
			tokens++;
			idx += token_len(str + idx, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - will tokenize a string.
 * @line: string.
 * @delim: delimiter character to tokenize string by.
 *
 * Return: pointer to an array containing tokenized words.
 */

char **_strtok(char *line, char *delim)

{
	char **ptr;
	int idx = 0, tokens, i, letters, j;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (i = 0; i < tokens; i++)
	{
		while (line[idx] == *delim)
			idx++;

		letters = token_len(line + idx, delim);

		ptr[i] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[i])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}

		for (j = 0; j < letters; j++)
		{
			ptr[i][j] = line[idx];
			idx++;
		}

		ptr[i][j] = '\0';
	}
	ptr[i] = NULL;
	ptr[i + 1] = NULL;

	return (ptr);
}
