#include "shell.h"

/**
 * interactive - checks if shell is in interactive mode
 * @info: pointer to info struct
 *
 * Return: 1 if interactive mode, 0 if not
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: char to check
 * @delim: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim == c)
			return (1);
		delim++;
	return (0);
}

/**
 * is_alpha - checks for alphabetic character
 * @c: Character to be input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * atoi - converts a string to an integer
 * @str: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int atoi(char *str)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; str[a] != '\0' && flag != 2; a++)
	{
		if (str[a] == '-')
			sign *= -1;

		if (str[a] >= '0' && str[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	output = (sign == -1) ? -result : result;
	return (output);
}
