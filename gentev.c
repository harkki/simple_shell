#include "shell.h"
/**
 * getenv - Retrieve user value env variable
 * @info: Structure containing potential arguments.
 * Return:  0
 */
char **getenv(info_t *info)
{
​if (!info->environ || info->env_changed)
​{
​​info->environ = list_to_strings(info->env);
​​info->env_changed = 0;
​}
​return (info->environ);
}
/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
​if (!info->env || !var)
​​return (0);
​int env_changed = 0;
​list_t *prev = NULL;
​list_t *current = info->env;
​while (current)
​{
​​char *p = starts_with(current->str, var);
​​if (p && *p == '=')
​​{
​​​if (prev)
​​​​prev->next = current->next;
​​​else
​​​​info->env = current->next;
​​​free(current->str);
free(current);
current = prev ? prev->next : info->env;
env_changed = 1;
continue;
​​}
​​Prev = current;
​​Current = current->next;
​}
​Info->env_changed = env_changed;
​return (env_changed);
}
/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: 0 on success, 1 on failure
 */
int _setenv(info_t *info, char *var, char *value)
{
if (!var || !value)
​​return (0);
​char *buffer = malloc(_strlen(var) + _strlen(value) + 2);
​if (!buffer)
​​return (1); ​
​_strcpy(buffer, var);
​_strcat(buffer, "=");
​_strcat(buffer, value);
​List_t *node = info->env;
​while (node)
​{
​​Char * p = starts_with(node->str, var);
​​if (p && *p == '=')
​​{
​​​free(node->str);
​​​node->str = buffer;
​​​info->env_changed = 1;
​​​return (0);
​​}
​​node = node->next;
​}
​add_node_end(&(info->env), buffer, 0);
​free(buffer);
​info->env_changed = 1;
​return (0);
}

