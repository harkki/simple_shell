#include "shell.h"

/**
 * count_nodes - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */

size_t count_nodes(const list_t *head)
{
	size_t length = 0;

	while (head)
	{
		head = head->next;
		length++;
	}
	return (length);
}

/**
 * nodes_to_strings - returns an array of strings
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **nodes_to_strings(list_t *head)
{
	size_t nodes_count = count_nodes(head);

	if (!head || !nodes_count)
		return (NULL);

	char **string_array = malloc(sizeof(char *) * (nodes_count + 1));

	if (!string_array)
		return (NULL);

	size_t i = 0;

	while (head)
	{
		string_array[i] = _strdup(head->str);
		if (!string_array[i])
		{
		for (size_t j = 0; j < i; j++)
			free(string_array[j]);
			free(string_array);
			return (NULL);
		}
		i++;
		head = head->next;
	}
	string_array[nodes_count] = (NULL);
	return (string_array);
}

/**
 * print_nodes - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of the list
 */

size_t print_nodes(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * find_node_starts_with - returns node whose string starting with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *find_node_starts_with(list_t *head, const char *prefix, char c)
{
	while (head)
	{
		if (starts_with(head->str, prefix) &&
			(c == -1 || head->str[_strlen(prefix)] == c))
			return (head);

		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_position - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t get_node_position(list_t *head, list_t *node)
{
	size_t position = 0;

	while (head)
	{
		if (head == node)
			return (position);
	head = head->next;
	position++;
	}
	return (-1);
}
