#include "shell.h"
 /**
 * sh_loop - main shell loop
 * @info: the parameter & return data struct
 * @arg_vec: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int sh_loop(shell_info_t *shell_info, char **arg_vec)
{
​ssize_t read = 0;
​int builtin_result = 0;
​while (read != -1 && builtin_result != -2)
​{
​​clear_info(shell_info->info);
​​if (interactive(shell_info->info))
​​​_puts("$ ");
​​_eputchar(BUF_FLUSH);
​​read = get_input(shell_info->info);
​​if (read != -1)
​​{
​​​set_info(shell_info->info, arg_vec);
​​​builtin_result = find_builtin(shell_info->info);
​​​if (builtin_resultt == -1)
​​​​find_cmd(shell_info->info);
​​}
​​else if (interactive(shell_info->info))
​​​_putchar('\n');
​​free_info(shell_info->info, 0);
​}
​write_history(shell_info->info);
​free_info(shell_info->info, 1);
​if (!interactive(shell_info->info) && shell_info->info->status)
​​exit(shell_info->info->status);
​if (builtin_result == -2)
​{
​​if (shell_info->info->err_num == -1)
​​​exit(shell_info->info->status);
​​exit(shell_info->info->err_num);
​}
​return (builtin_result);
}
/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * ​     0 if builtin executed successfully,
 * ​     1 if builtin found but not successful,
 * ​     2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
​int i, builtin_result = -1;
​struct builtin_entry {
​​const char *command;
​​int (*function)(info_t *info);
​};
​struct builtin_entry builtin_table[] = {
​​{"exit", custom_exit},
​​{"env", custom _env},
​​{"help", custom _help},
​​{"history", custom _history},
​​{"setenv", custom _setenv},
​​{"unsetenv", custom _unsetenv},
​​{"cd", custom_cd},
​​{"alias", custom _alias},
​​{NULL, NULL}
​};
​for (i = 0; builtin_table[i].comand; i++)
{
​​if (_strcmp(info->argv[0], builtintable[i].command) == 0)
​​​info->line_count++;
​​​built_in_resultt = builtintable[i].function(info);
​​​break;
​​}
​return builtin_result;
}
/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
​char *path = NULL;
​int i, non_del_count;
​info->path = info->argv[0];
​if (info->linecount_flag == 1)
​{
​​info->line_count++;
​​info->linecount_flag = 0;
​}
​non_del_count = count_non_delimeter(info->arg);
​​if (!non_del_count)
​​​return;
​path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
​if (path)
​{
​​info->path = path;
​​fork_cmd(info);
​}
​else
​{
​​if ((interactive(info) || _getenv(info, "PATH=")
​​​​​ || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
​​​fork_cmd(info);
​​else if (*(info->arg) != '\n')
​​{
​​​info->status = 127;
​​​print_error(info, "not found\n");
​​}
​}
}
/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
​pid_t child_pid;
​child_pid = fork();
​if (child_pid == -1)
​{
​​perror("Error:");
​​return;
​}
​if (child_pid == 0)
​{
​​if (execve(info->path, info->argv, get_environ(info)) == -1)
​​{
​​​free_info(info, 1);
​​​if (errno == EACCES)
​​​​exit(126);
​​​exit(1);
​​}
​}
​else
​{
​​wait(&(info->status));
​​if (WIFEXITED(info->status))
​​{
​​​info->status = WEXITSTATUS(info->status);
​​​if (info->status == 126)
​​​​print_error(info, "Permission denied\n");
​​}
​}
}
