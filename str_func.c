#include "shell.h"

/**
 * _strlen - will return length of string.
 * @s: pointer to characters string.
 *
 * Return: length of the string.
 */

int _strlen(const char *s)

{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcpy - will copy string pointed to by src, including
 *           terminating null byte, to buffer pointed by des.
 * @dest: The pointer to destination of copied string.
 * @src: The pointer to src of source string.
 *
 * Return: The pointer to dest.
 */

char *_strcpy(char *dest, const char *src)

{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	dest[a] = '\0';
	return (dest);
}

/**
 * _strcat - will concantenate two strings.
 * @dest: the pointer to destination string.
 * @src: the pointer to source string.
 *
 * Return: the pointer to destination string.
 */

char *_strcat(char *dest, const char *src)

{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - will concantenate two strings where n is the number
 * of bytes are copied from source.
 * @dest: the pointer to destination string.
 * @src: the pointer to source string.
 * @n: n bytes to copy from the src string.
 *
 * Return: the pointer to destination string.
 */

char *_strncat(char *dest, const char *src, size_t n)

{
	size_t dest_len = _strlen(dest);
	size_t a;

	for (a = 0; a < n && src[a] != '\0'; a++)
		dest[dest_len + a] = src[a];
	dest[dest_len + a] = '\0';

	return (dest);
}
