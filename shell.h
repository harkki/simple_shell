#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Constants */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* Global Variables */
extern char **environ;

/* Data Structures */

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguments to pass into a function.
 * @arg:            A string generated from getline with arguments.
 * @argv:           An array of strings generated from arg.
 * @path:           A string path for the current command.
 * @argc:           The argument count.
 * @line_count:     The error count.
 * @err_num:        The error code for exit() calls.
 * @linecount_flag: If on, count this line of input.
 * @fname:          The program filename.
 * @env:            Linked list local copy of environ.
 * @environ:        Custom modified copy of environ from LL env.
 * @history:        The history node.
 * @alias:          The alias node.
 * @env_changed:    On if environ was changed.
 * @status:         The return status of the last exec'd command.
 * @cmd_buf:        Address of the pointer to cmd_buf, on if chaining.
 * @cmd_buf_type:   CMD_type (||, &&, ;).
 * @readfd:         The file descriptor from which to read line input.
 * @histcount:      The history line number count.
 * @size:         A data type for representing size of object in mem
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
	ssize_t size;

} info_t;

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function Declarations */
size_t count_nodes(const list_t *head);
char **nodes_to_strings(list_t *head);
size_t print_nodes(const list_t *head);
list_t *find_node_starts_with(list_t *head, const char *prefix, char c);
ssize_t get_node_position(list_t *head, list_t *node);

/* atoi.c */
int is_interactive(info_t *);
int is_delim(char, char *);
int is_alpha(int);
int atoi(char *);

/* builtin.c */
int sh_exit(info_t *);
int custom_cd(info_t *);
int custom_help(info_t *);

/* builtin1.c */
int custom_history(info_t *);
int custom_alias(info_t *);

/* environ.c */
int custom_env(info_t *);
char *_getenv(info_t *, const char *);
int custom_setenv(info_t *);
int custom_unsetenv(info_t *);
int populate_env_list(info_t *);

/* errors.c */
void cus_putstr(char *);
int cus_putchar(char);
int cus_put_fd(char c, int fd);
int cus_putstr_fd(char *str, int fd);

/* errors1.c */
int str_to_int(char *);
void print_error(info_t *, char *);
int print_dec(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* exits.c */
char *_str_len_cpy(char *, char *, int);
char *_strconcat(char *, char *, int);
char *_strchr_loc(char *, char);

/* getenv.c */
char **i_getenv(info_t *);
int i_unsetenv(info_t *, char *);
int i_setenv(info_t *, char *, char *);

/* getinfo.c */
void initialize_info(info_t *);
void set_info(info_t *, char **);
void cleanup_info(info_t *, int);
void cleanup_dynamic_data(info_t *);

/* getline.c */
ssize_t fill_input_buffer(info_t *);
int get_user_input(info_t *, char **, size_t *);
ssize_t read_into_buffer(info_t *, char *, size_t *)
int get_line(info_t *, char **, size_t *);
void handle_interrupt(int);

/* history.c */
char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* linked_lists.c */
list_t *create_node(list_t **, const char *, int);
list_t *create_node_end(list_t **, const char *, int);
size_t print_list_strings(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void clear_list(list_t **);

/* linked_lists1.c */
size_t count_nodes(const list_t *);
char **nodes_to_strings(list_t *);
size_t print_nodes(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t get_node_position(list_t *, list_t *);

/* memory.c */
int free_pointer(void **);

/* parser.c */
int is_exec_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *path_finder(info_t *, char *, char *);

/* realloc.c */
char *memory_set(char *, char, unsigned int);
void free_str(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* shell loop.c */
int sh_loop(data_t *, char **);
int find_builtin(data_t *);
void find_cmd(data_t *);
void fork_cmd(data_t *);

/* string.c */
int str_length(const char *);
int str_comp(const char *, const char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, const char *);

/* string1.c */
char *cus_strcpy(char *, char *);
char *cus_strdup(const char *);
void cus_puts(char *);
int _putchar(char);

/* tokenizer.c */
char **cus_strtow(char *, char *);
char **cus_strtow2(char *, char);

/* vars.c */
int is_delimeter(info_t *, char *, size_t *);
void chk_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);

/* loophsh.c */
int loophsh(char **);


#endif /* _SHELL_H_ */
