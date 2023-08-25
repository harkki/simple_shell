#include "shell.h"

/**
 * initialize_info - initializes info_t struct
 * @info: struct address
 */

void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */

void set_info(info_t *info, char **av)
{
	info->fname = av[0];

	if (info->arg)
	{
	info->argv = create_argv(info->arg);
	info->argc = count_argv_elements(info->argv);

	replace_alias(info);
	replace_vars(info);
	}
}

/**
 * cleanup_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */

void cleanup_info(info_t *info, int all)
{
	free(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
	cleanup_dynamic_data(info);
	clear_static_data(info);
	}
}

/**
 * **create_argv - frees info_t struct fields
 * @arg: struct address
 *
 * Return: an array of strings
 */

char **create_argv(const char *arg)
{
	char **argv = strtow(arg, " \t");

	if (!argv)
	{
	argv = create_single_argv(arg);
	}
	return (argv);
}
/**
 * cleanup_dynamic_data - frees dynamic data on struct fields
 * @info: struct address
 */
void cleanup_dynamic_data(info_t *info)
{
	free(info->environ);

	if (info->readfd > 2)
	{
		close(info->readfd);
	}
	_putchar(BUF_FLUSH);
}
