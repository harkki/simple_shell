#include "shell.h"
/**
 * fill_input_buffer - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @buffer_len: address of len variable
 *
 * Return: bytes read
 */
/* Global variables */
static size_t buffer_index = 0, chain_index = 0, buffer_length = 0;
ssize_t fill_input_buffer(info_t *info, char **buffer, size_t *buffer_len)
{
​ssize_t bytes_read = 0;
​size_t buffer_p = 0;
​if (!*buffer_len)
{
​​free(*buffer);
​​ *buffer = NULL;
​​signal(SIGINT, handle_interrupt);
#if USE_GETLINE
​​bytes_read = getline(buffer, &buffer_p, stdin);
#else
​​bytes_read = get_line(info, buffer, &buffer_p);
#endif
​​if (bytes_read > 0)
​​{
​​​if ((*buffer)[bytes_read - 1] == '\n')
​​​{
​​​​(*buffer)[bytes_read - 1] = '\0';
​​​​bytes_read--;
​​​}
​​​info->linecount_flag = 1;
​​​remove_comments(*buffer);
​​​build_history_list(info, *buffer, info->histcount++);
​​​if (_strchr(*buffer, ';'))
​​​{
​​​​ *buffer_len = bytes_read;
​​info->cmd_buf = buffer;
​​​}
​​}
​}
​return (bytes_read);
}
/**
 * get_user_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_user_input(info_t *info)
{
​static char *buffer;
​ssize_t bytes_read = 0;
​char **arg_ptr = &(info->arg), *position;
​_putchar(BUF_FLUSH);
​bytes_read = fill_input_buffer(info, &buffer, &buffer_length);
​if (bytes_read == -1)
​​return -1;
​if (buffer_length)
​{
​​chain_index = buffer_index;
​​position = buffer + buffer_index;
​​check_chain(info, buffer, &chain_index, buffer_index, buffer_length);
​​while (chain_index < buffer_length)
​​{
​​​if (is_chain(info, buffer, &chain_index))
​​​​break;
​​​chain_index++;
​​}
​​buffer_index = chain_index + 1;
​​if (buffer_index >= buffer_length)
​​{
​​​buffer_index = buffer_length = 0;
​​​info->cmd_buf_type = CMD_NORM;
​​}
​​ *arg_ptr = position;
​​return (_strlen(position));
​}
​ *arg_ptr = buffer;
​return (bytes_read);
}
/**
 * read_info_buffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @index: size
 *
 * Return: byte read
 */
ssize_t read_into_buffer(info_t *info, char *buffer, size_t *index)
{
< 200 > ssize_t bytes_read = 0;
​if (*index)
​​return (0);
​bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
​if (bytes_read >= 0)
​​ *index = (bytes_read);
​return (bytes_read);
}
/**
 * get_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
​static char buffer[READ_BUF_SIZE];
​size_t buff_offset;
​ssize_t bytes_read = 0, line_length = 0;
​char *current_position = NULL, *new_position = NULL, *newline_ptr;
​current_position = *ptr;
​if (current_position && length)
​​line_length = *length;
​if (buffer_index == buffer_length)
​​buffer_index = buffer_length = 0;
​bytes_read = read_into_buffer(info, buffer, &buffer_length);
​if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
​​return (-1);
​newline_ptr = _strchr(buffer + buffer_index, '\n');
​buff_offset = newline_ptr ? 1 + (unsigned int)(newline_ptr - buffer) : buffer_length;
​new_position = _realloc(current_position, line_length, line_length ? line_length + buff_offset : buff_offset + 1);
​if (!new_position)
​​return (current_position ? (free(current_position), -1) : -1);
​if (line_length)
​​_strncat(new_position, buffer + buffer_index, buff_offset - buffer_index);
​else
​​_strncpy(new_position, buffer + buffer_index, buff_offset - buffer_index + 1);
​line_length += buff_offset - buffer_index;
​buffer_index = buff_offset;
​current_position = new_position;
​if (length)
​​ *length = line_length;
​ *ptr = current_position;
​return (line_length);
}
/**
 * handle_interrupt - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_interrupt(int sig_num)
{
​_puts("\n");
​_puts("$ ");
​_putchar(BUF_FLUSH);
}
