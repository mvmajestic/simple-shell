#include "shell.h"

/**
 * _strcmp - will compare two strings.
 * @s1: first string to be compared.
 * @s2: second string to be compared.
 *
 * Return: Positive byte difference if s1 > s2
 * 0 if s1 = s2, and negative byte difference if s1 < s2
 */

int _strcmp(char *s1, char *s2)

{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - will compare two strings.
 * @s1: pointer to a string.
 * @s2: pointer to a string.
 * @n: first n bytes of strings to compare.
 *
 * Return: Negative if s1 is shorter than s2,
 * 0 if s1 and s2 match, and positive if s1 is longer thn s2.
 */

int _strncmp(const char *s1, const char *s2, size_t n)

{
	size_t a;

	for (a = 0; s1[a] && s2[a] && a < n; a++)
	{
		if (s1[a] > s2[a])
			return (s1[a] - s2[a]);
		else if (s1[a] < s2[a])
			return (s1[a] - s2[a]);
	}
	if (a == n)
		return (0);
	else
		return (-15);
}

/**
 * _strchr - will locate a character in a string.
 * @s: string to be searched.
 * @c: character to be located.
 *
 * Return: If c is found - a pointer to first occurence.
 * If c is not found - NULL.
 */

char *_strchr(char *s, char c)

{
	int idx;

	for (idx = 0; s[idx]; idx++)
	{
		if (s[idx] == c)
			return (s + idx);
	}

	return (NULL);
}

/**
 * _strspn - will get length of prefix substring.
 * @s: string to be searched.
 * @accept: prefix to be measured.
 *
 * Return: number of bytes in s which
 * consist only of bytes from accept.
 */

int _strspn(char *s, char *accept)

{
	int bytes = 0;
	int idx;

	while (*s)
	{
		for (idx = 0; accept[idx]; idx++)
		{
			if (*s == accept[idx])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}
