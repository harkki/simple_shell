#include "shell.h"
/**
 * is_delimeter - test if current char in buffer is a delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @pst: address of current position in buffer
 *
 * Return: 1 if delimeter, 0 otherwise
 */
int is_delimeter(info_t *info, char *buff, size_t *pst)
{
​size_t index = *pst;
​if (buff[index] == '|' && buff[index + 1] == '|')
​{
​​buff[index] = 0;
​​index++;
​​info->cmd_buff_type = CMD_OR;
​}
​else if (buff[x] == '&' && buff[x + 1] == '&')
​{
​​buff[index] = 0;
​​index++;
​​info->cmd_buff_type = CMD_AND;
​}
​else if (buff[index] == ';')
​{
​​buff[index] = 0;
​info->cmd_buff_type = CMD_CHAIN;
​}
​else
​​return (0);
​ *pst = index;
​return (1);
}

/**
 * chk_chain - checks for chain continuation based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @pst: address of current position in buffer
 * @start: starting position of buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void chk_chain(info_t *info, char *buff, size_t *pst, size_t start, size_t len)
{
​size_t index = *pst;

​if (info->cmd_buff_type == CMD_AND)
​{
​​if (info->status)
​​{
​​​buff[start] = 0;
​​​index = len;
​​}
​}
​if (info->cmd_buff_type == CMD_OR)
​{
​​if (!info->status)
​​{
​​​buff[start] = 0;
​​​index = len;
​​}
​}
​ *pst = index;
}
 /**
 * replace_alias - replaces aliases in tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
​int i;
​list_t *node;
​char *ptr;
​for (i = 0; i < 10; i++)
​{
​​node = node_starts_with(info->alias_list, info->arg_list[0], '=');
​​if (!node)
​​​return (0);
​​free(info->arg_list[0]);
​​ptr = _strchr(node->str, '=');
​​if (!ptr)
​​​return (0);
​​p = _strdup(ptr + 1);
​​if (!ptr)
​​​return (0);
​​info->arg_list[0] = ptr;
​}
​return (1);
}
 /**
 * replace_variables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info_t *info)
{
​int i = 0;
​list_t *node;
​for (i = 0; info->arg_list[i]; i++)
​{
​​if (info->arg_list[i][0] != '$' || !info->arg_list[i][1])
​​​continue;
​​if (!_strcmp(info->arg_list[i], "$?"))
​​{
​​​replace_string(&(info->arg_list[i]),
​​​​​_strdup(convert_number(info->status, 10, 0)));
​​​continue;
​​}
​​if (!_strcmp(info->arg_list[i], "$$"))
​​{
​​​replace_string(&(info->arg_list[i]),
​​​​​_strdup(convert_number(getpid(), 10, 0)));
​​​continue;
​​}
​​node = node_starts_with(info->env_list, &info->arg_list[i][1], '=');
​​if (node)
​​{
​​​replace_string(&(info->arg_list[i]),
​​​​​_strdup(_strchr(node->str, '=') + 1));
​​​continue;
​​}
​​replace_string(&info->arg_list[i], _strdup(""));
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
