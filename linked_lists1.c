#include "shell.h"
 /**
 * list_len - Counts the number of nodes in a linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *head)
{
​size_t length = 0;
​while (head)
​{
​​head = head->next;
​​length++;
​}
​return (length);
}
/**
 * list_to_strings - returns an array of strings
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
​list_t *node = head;
​size_t list_size = list_len(head);
​char **string_array;
​char *str;
​if (!head || !list_size)
​​return (NULL);
​string_array = malloc(sizeof(char *) * (list_size + 1));
​if (!string_array)
​​return (NULL);
​for (size_t i = 0; node; node = node->next, i++)
​{
​​str = malloc(_strlen(node->str) + 1);
​​if (!str)
​​{
​​​for (size_t j = 0; j < i; j++)
​​​​free(string_array[j]);
​​​free(string_array);
​​​return (NULL);
​​}
​​string_array[i] = str;
​}
​string_array[list_size] = NULL;
​return (string_array);
}
/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
​size_t count = 0;
​while (head)
​{
​​_puts(convert_number(head->num, 10, 0));
​​_putchar(':');
​​_putchar(' ');
​​_puts(head->str ? head->str : "(nil)");
​​_puts("\n");
​​head = head->next;
​​count++;
​}
​return (count);
}
/**
 * node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *head, char *prefix, char c)
{
​char *p = NULL;
​while (head)
​{
​​p = starts_with(head->str, prefix);
​​if (p && ((c == -1) || (*p == c)))
​​​return (head);
​​head = head->next;
​}
​return (NULL);
}
/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
​size_t index = 0;
​while (head)
​{
​​if (head == node)
​​​return (index);
​​head = head->next;
​​index++;
​}
​return (-1);
}
