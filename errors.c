#include "shell.h"

/**
 * cus_puts - prints a string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void cus_puts(char *str)
{
	if (!str)
		return;

	while (*str)
	{
		_eputchar(*str);
		str++;
	}
}

/**
 * cus_putchar - writes the character to stderr
 * @c: The character to print
 *
 * Return: 1 on success.
 * On error, -1, and errno is set appropriately.
 */
int cus_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c != BUF_FLUSH)
		buf[i++] = c;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	return (1);
}

/**
 * cus_put_fd - writes the character to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int cus_put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c != BUF_FLUSH)
		buf[i++] = c;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	return (1);
}

/**
 * cus_putstr_fd - prints a string to a given fd
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int cus_putstr_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	for (int a = 0; str[a]; a++)
	{
		i += _putfd(str[a], fd);
	}
	return (i);
}
