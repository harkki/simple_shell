#include "shell.h"
/**
 * is_delimeter - test if current char in buffer is a delimeter
 * @data: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buffer
 *
 * Return: 1 if delimeter, 0 otherwise
 */
int is_chain(data_t *data, char *buff, size_t *position)
{
​size_t index = *position;
​if (buff[index] == '|' && buff[index + 1] == '|')
​{
​​buff[index] = 0;
​​index++;
​​data->cmd_buff_type = CMD_OR;
​}
​else if (buff[x] == '&' && buff[x + 1] == '&')
​{
​​buff[index] = 0;
​​index++;
​​data->cmd_buff_type = CMD_AND;
​}
​else if (buff[index] == ';')
​{
​​buff[index] = 0;
​data->cmd_buff_type = CMD_CHAIN;
​}
​else
​​return (0);
​ *position = index;
​return (1);
}

/**
 * check_chain - checks for chain continuation based on last status
 * @data: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buffer
 * @i: starting position of buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *data, char *buff, size_t *position, size_t start, size_t len)
{
​size_t index = *position;

​if (data->cmd_buff_type == CMD_AND)
​{
​​if (data->status)
​​{
​​​buff[start] = 0;
​​​index = len;
​​}
​}
​if (data->cmd_buff_type == CMD_OR)
​{
​​if (!data->status)
​​{
​​​buff[start] = 0;
​​​index = len;
​​}
​}
​ *position = index;
}
 /**
 * replace_alias - replaces aliases in tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(data_t *data)
{
​int i;
​list_t *node;
​char *ptr;
​for (i = 0; i < 10; i++)
​{
​​node = node_starts_with(data->alias_list, data->arg_list[0], '=');
​​if (!node)
​​​return (0);
​​free(data->arg_list[0]);
​​ptr = _strchr(node->str, '=');
​​if (!ptr)
​​​return (0);
​​p = _strdup(ptr + 1);
​​if (!ptr)
​​​return (0);
​​data->arg_list[0] = ptr;
​}
​return (1);
}
 /**
 * replace_variables - replaces variables in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(data_t *data)
{
​int i = 0;
​list_t *node;
​for (i = 0; data->arg_list[i]; i++)
​{
​​if (data->arg_list[i][0] != '$' || !info->arg-list[i][1])
​​​continue;
​​if (!_strcmp(data->arg_list[i], "$?"))
​​{
​​​replace_string(&(data->arg_list[i]),
​​​​​_strdup(convert_number(data->status, 10, 0)));
​​​continue;
​​}
​​if (!_strcmp(info->arg_list[i], "$$"))
​​{
​​​replace_string(&(info->arg_list[i]),
​​​​​_strdup(convert_number(getpid(), 10, 0)));
​​​continue;
​​}
​​node = node_starts_with(data->env_list, &data->arg_list[i][1], '=');
​​if (node)
​​{
​​​replace_string(&(data->arg_list[i]),
​​​​​_strdup(_strchr(node->str, '=') + 1));
​​​continue;
​​}
​​replace_string(&data->arg_list[i], _strdup(""));
​}
​return (0);
}
/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
​free(*old);
​ *old = new;
​return (1);
}
