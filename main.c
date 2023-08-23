#include "shell.h"

/**
 * main - entry point
 * @arg_cnt: argument count
 * @arg_v: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_cnt, char **arg_v)
{
	info_t info[] = { INFO_INIT };
	int error_desc = 2;

	/*Manipulate fd value using assembly code*/

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (error_desc)
			: "r" (error_desc));

	if (arg_cnt == 2)
	{
		Int file_desc = open(arg_v[1], O_RDONLY);

		if (file_desc == -1)
		{
			Handle_file_open_error(arg_v[0], arg_v[1]);
		}
		info->readfd = file_desc;
	}
	setup_and_run_shell(info, arg_v);
	return (EXIT_SUCCESS);
}

/**
 * handle_file_open_error - Handles errors that occurs while
 *	attempting to open a file
 *	It checks for error conditions, such as permission denied
 *	or file not found and provides an error messages and exit codes
 * @shell_name: Name of the shell program
 * @file_name: Name of the file that failed to open
 *
 * Return: Nothing
 */

void handle_file_open_error(const char *shell_name, const char *file_name)
{
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
	{
		_eputs(av[0]);
		_eputs(": 0: Can not open ");
		_eputs(av[1]);
		_eputchar('\n');
		_eputchar(BUF_FLUSH);
		exit(127);
	}
	return (EXIT_FAILURE);
}

/**
 * setup_and_run_shell - Sets up the shell environ and initiates
 *	the main execution loop of the shell program
 * @info: Pointer to the info_t structure containing shell info
 * @av: Pointer to the argument vector (command line arguments)
 *
 * Return: Nothing
 */

void setup_and_run_shell(info_t *info, char **av)

	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
