#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the maximum number of characters to be copied
 *Return: the destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;
	char *result = dest;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0'

	return (result);
}

/**
 **_strncat - concatenates two strings
 *@dest: the destination string
 *@src: the source string
 *@n: the maximum number of bytes to be used
 *Return: the destination string
 */
char *_strncat(char *dest, char *src, int n)
{
	int dest_len = strlen(dest);
	int I;

	for (i = 0; i < n && src[i] != ‘\0’; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = ‘\0’;

	return (dest);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	while (*s != ‘\0’)
	{
		if (*s == c)
			return ((char *)s);
		s++
};

	return (NULL);
}
