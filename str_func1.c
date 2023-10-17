#include "shell.h"


/**
 * _strcpy - will copy a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the destinatiotn
 */

char *_strcpy(char *dest, char *src)

{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - will duplicate a string
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
 */

char *_strdup(const char *str)

{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - will print an input string
 *@str: string to print
 *
 * Return: Nothing
 */

void _puts(char *str)

{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - will write character c to stdout
 * @c: character to print
 *
 * Return: On success 1, or -1 on error
 * and errno is set appropriately.
 */

int _putchar(char c)

{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}
