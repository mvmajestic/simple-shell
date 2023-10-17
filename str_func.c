#include "shell.h"

/**
 * _strlen - will returns length of string
 * @s: string length to check
 *
 * Return: integer length of string
 */

int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - will perform comparison of two strangs.
 * @s1: first string
 * @s2: second string
 *
 * Return: negative s1 less s2, positive s1 greater s2 and zero s1 equals s2
 */

int _strcmp(char *s1, char *s2)

{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - will check if needle starts with haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)

{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - will concatenate two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination string
 */

char *_strcat(char *dest, char *src)

{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
