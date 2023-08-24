#include "shell.h"

/**
 * custom_history - displays the history list
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int custom_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias – unsets an alias
 * @info: parameter struct
 * @alias_str: the alias string to unset
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias_str)
{
	char *eq, c;
	int result;

	eq = _strchr(alias_str, '=');
	if (!eq)
		return (1);
	c = *eq;
	*eq = ‘\0’;
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*eq = c;
	return (result);
}

/**
 * set_alias - sets an alias
 * @info: parameter struct
 * @ alias_str: the alias string to set
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_str)
{
	char *eq, nc;

	eq = _strchr(alias_str, '=');
	if (!eq)
		return (1);

	nc = *++eq;
	if (!nc)
		return (unset_alias(info, alias_str));

	unset_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *eq, *as;

	if (node)
	{
		eq = _strchr(node->str, '=');
		for (as = node->str; as <= eq; as++)
		_putchar(*as);
		_putchar('\'');
		_puts(eq + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * custom_alias - handles the alias builtin
 * @info: Structure containing potential arguments
 *  Return: 0
 */
int custom_alias(info_t *info)
{
	int i;
	char *eq;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		eq = _strchr(info->argv[i], '=');
		if (eq)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
