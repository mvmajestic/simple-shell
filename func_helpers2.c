#include "shell.h"

/**
 * handle_line - will partition line read from standard input as needed.
 * @line: pointer to line read from standard input.
 * @read: length of line.
 *
 * Description: spaces inserted to separate ";", "||", and "&&",
 * replaces "#" with '\0'.
 */

void handle_line(char **line, ssize_t read)

{
	char *old_line, *new_line;
	char previous, current, next;
	size_t m, n;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	n = 0;
	old_line = *line;
	for (m = 0; old_line[m]; m++)
	{
		current = old_line[m];
		next = old_line[m + 1];
		if (m != 0)
		{
			previous = old_line[m - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[n++] = ' ';
					new_line[n++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_line[n++] = ';';
					new_line[n++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[n++] = ' ';
				new_line[n++] = ';';
				if (next != ' ')
					new_line[n++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[n++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[n++] = '&';
					new_line[n++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[n++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[n++] = '|';
					new_line[n++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (m != 0 && old_line[m - 1] != ' ')
				new_line[n++] = ' ';
			new_line[n++] = ';';
			if (next != ' ' && next != ';')
				new_line[n++] = ' ';
			continue;
		}
		new_line[n++] = old_line[m];
	}
	new_line[n] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_len - will get new length of line partitioned
 * by ";", "||", "&&&", or "#".
 * @line: line to check.
 *
 * Return: new length of line.
 *
 * Description: will cut short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)

{
	size_t a;
	ssize_t new_len = 0;
	char current, next;

	for (a = 0; line[a]; a++)
	{
		current = line[a];
		next = line[a + 1];
		if (current == '#')
		{
			if (a == 0 || line[a - 1] == ' ')
			{
				line[a] = '\0';
				break;
			}
		}
		else if (a != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[a - 1] != ' ' && line[a - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[a - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[a - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[a], &new_len);
		}
		else if (current == ';')
		{
			if (a != 0 && line[a - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logical_ops - will inspect line for logical operators "||" or "&&".
 * @line: pointer to character to check in line.
 * @new_len: the pointer to new_len in get_new_len function.
 */

void logical_ops(char *line, ssize_t *new_len)

{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
