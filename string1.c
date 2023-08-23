#include "shell.h"
/**
 * cus_strcpy - copies a string
 * @dest: destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *cus_strcpy(char *dest, char *src)
{
​int i = 0;
​if (dest == src || src == NULL)
​​return dest;
​while (src[i] != ‘\0’)
​{
​​dest[i] = src[i];
​​i++;
​}
​dest[i] = ‘\0’;
​return dest;
}
/**
 * cus_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *cus_strdup(const char *str)
{
​int len = 0;
​char *result;
​if (str == NULL)
​​return NULL;
​while (str[len] != ‘\0’)
​​len++;
​result = malloc((len + 1) * sizeof(char));
​if (result == NULL)
​​return NULL;
​cus_strcpy(result, str);
​return (result);
}
/**
 * cus_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void cus_puts(char *str)
{
​int i = 0;
​if (str == NULL)
​​return;
​while (str[i] != '\0')
​{
​​_putchar(str[i]);
​​i++;
​}
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: 1 on success.
 * On error, return -1, and errno is set appropriately.
 */
int _putchar(char c)
{
​static int i;
< 200b > static char buff[WRITE_BUFF_SIZE];
​if (c == BUFF_FLUSH || i > = WRITE_BUFF_SIZE)
​{
​​write(1, buff, i);
​​i = 0;
​}
​if (c != BUFF_FLUSH)
​​buff[i++] = c;
​return (1);
}
