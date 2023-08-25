#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(info_t *info)
{
	char *dir = _getenv(info, "HOME=");

	if (!dir)
		return (NULL);

	size_t bufsize = _strlen(dir) + _strlen(HIST_FILE) + 2;
	char *buf = malloc(bufsize);

	if (!buf)
		return (NULL);

	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	return (buf);
}

int write_hist(info_t *info)
{
	char *filename = get_hist_file(info);

	if (!filename)
		return (-1);

	ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(filename);

	if (fd == -1)
		return (-1);

	list_t *node = info->history;

	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

int read_hist(info_t *info)
{
	char *filename = get_hist_file(info);

	if (!filename)
		return (0);

	ssize_t fd = open(filename, O_RDONLY);

	free(filename);

	if (fd == -1)
		return (0);

	struct stat st;

	if (fstat(fd, &st) == 0 && st.st_size >= 2)
	{
	size_t fsize = (size_t)st.st_size;
	char *buf = malloc(fsize + 1);

	if (!buf)
	{
		close(fd);
		return (0);
	}

	ssize_t rdlen = read(fd, buf, fsize);

	buf[fsize] = '\0';

	if (rdlen <= 0)
	{
		free(buf);
		close(fd);
		return (0);
	}

	close(fd);

	int last = 0, linecount = 0;

	for (int i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n)
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}
	if (last != fsize)
		build_history_list(info, buf + last, linecount++);
	free(buf);

	info->histcount = linecount;

	while (info->histcount >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0);
		info->histcount--;
	}
	renumber_history(info);
	return (info->histcount);

	close(fd);
	return (0);
}
/**
 * build_hist_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_hist_list(info_t *info, char *buf, int linecount)
{
    add_node_end(&(info->history), buf, linecount);
    return (0);
}

/**
 * renumber_hist - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int renumber_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	info->histcount = i
	return (i);
}
