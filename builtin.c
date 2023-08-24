#include "shell.h"
 /**
 * sh_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: exits with a given exit status
 */
int sh_exit(info_t *info)
{
​int exitcheck = _erratoi(info->argv[1]);
​if (exitcheck == -1)
​{
​​Info->status = 2;
​​print_error(info, "Invalid number: %s\n", info->argv[1]);
​​​return (1);
​}
​info->err_num = exitcheck;
​​return (-2);
​}
​info->err_num = -1;
​return -2;
}
/**
 * custom_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_cd(info_t *info)
{
​char *current_dir, *new_dir, buffer[1024];
​int chdir_result;
​current_dir = getcwd(buffer, sizeof(buffer));
​if (!current_dir)
​​_puts("TODO: >>getcwd failure emsg here<<\n");
​if (!info->argv[1])
​{
​​new_dir = _getenv(info, "HOME=");
​​if (!new_dir)
​​​new_dir = _getenv(info, “PWD = ”);
​​chdir_result = chdir(new_dir);
​}
​else if (_strcmp(info->argv[1], "-") == 0)
​{
​​new_dir = _getenv(info, "OLDPWD=");
​​if (!new_dir)
​​{
​​​_puts(current_dir);
​​​_putchar('\n');
​​​return 1;
​​}
​​_puts(new_dir);
_putchar('\n');
​​chdir_result = chdirv(new_dir ? new_dir : "/");
​}
​else
​​chdir_result = chdir(info->argv[1]);
​if (chdir_result == -1)
​{
​​print_error(info, "can not cd to %s\n", info->argv[1]);
​}
​else
​{
​​_setenv(info, "OLDPWD", _getenv(info, "PWD="));
​​_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
​}
​return 0;
}
/**
 * custom_help – Displays help information
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0
 */
int custom_help(info_t *info)
{
​_puts("Help functionality not yet implemented \n");
​char **arg_array = info->argv;
​/* Uncomment the following line for debugging */
​_puts(*arg_array);
​return 0;
}
