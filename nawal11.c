#ifndef _S_SHELL_H_
#define _S_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LOWERCASE 1
#define TO_UNSIGNED 2

#define BUFFER_FOR_CLEARING -1
#define BUFFER_WRITE_FUNCTION 1024
#define BUFFER_READ_FUNCTION 1024

#define GETLINE_USING 0

#define HISTORY_DOC ".s_shell_hist"
#define MAXIMUM_LENGTH_HIST 4096

#define NORMAL_MODE_COM 0
#define OR_MODE_COM 1
#define AND_MODE_COM 2
#define END_MODE_COM 3

extern char **c_environ;

/**
 *  struct singly_LL - singly linked list
 *  @number: number of nodes
 *  @str: string
 *  @nxt: pointer to the next node
 */

typedef struct singly_LL
{
	int number;
	char *str;
	struct singly_LL *nxt;
} l_list;

/**
 * struct models_pool - data model for functions
 * @s_of_arg: string of arguments from getline function
 * @arg_v: array of strings from s_of_arg
 * @path: string for current command
 * @arg_c: arguments count
 * @row_error_count: error count
 * @code_error: error code for exit function
 * @line_count: count line of input
 * @f_name: program file name
 * @env_ll: environment linked list
 * @c_environ: custom environment from environment linked list
 * @history: history node
 * @alias: alias node
 * @change_f: flag for changing environment
 * @fb: feedback for last command
 * @buf_chain: pointer to chainning buffer
 * @c_mode: input for || && ;
 * @f_read: flag for reading line
 * @log_counter_row: line counter for history file
 */

typedef struct models_pool
{
	l_list *env_ll;
	l_list *history;
	l_list *alias;
	char *s_of_arg;
	char **arg_v;
	char *path;
	int arg_c;
	unsigned int row_error_count;
	int code_error;
	int change_f;
	int fb;
	int line_count;
	char *f_name;
	char **c_environ;
	char **buf_chain;
	int c_mode;
	int f_read;
	int log_counter_row;
} cmd_model;

/**
 * struct function_call - contains a function string and related function
 * @flag_name: the builtin command flag
 * @func_name: the function
 */

typedef struct function_call
{
	char *flag_name;
	int (*func_name)(cmd_model *);
} func_table;

int _conv(char *);
int _isalpha(int);
int _specified(char, char *);
int onfire(cmd_model *);

int c_cd(cmd_model *);
int c_exit(cmd_model *);
int c_help(cmd_model *);

int c_alias(cmd_model *);
int p_alias(l_list *);
int add_alias(cmd_model *, char *);
int delete_alias(cmd_model *, char *);
int c_history(cmd_model *);

int c_env(cmd_model *);
int c_add_env(cmd_model *);
int c_remove_env(cmd_model *);
int ll_env(cmd_model *);
char *get_value(cmd_model *, const char *);

int wr_char(char c, int fd);
int print_string(char *str, int fd);
void print_error_string(char *);
int putchar_error(char);

int print_decimal(int, int);
char *num_to_str(long int, int, int);
void change_first_char(char *);
int error_conv(char *);
void print_error(cmd_model *, char *);

char *c_strncpy(char *, char *, int);
char *c_strncat(char *, char *, int);
char *c_strchr(char *, char);

void func_ctrl_c(int);
ssize_t buff_chained(cmd_model *, char **, size_t *);
ssize_t read_buff_chained(cmd_model *, char *, size_t *);
ssize_t get_line(cmd_model *);
int c_getline(cmd_model *, char **, size_t *);

char **get_str_environ(cmd_model *);
int remove_env(cmd_model *, char *);
int add_new_env(cmd_model *, char *, char *);

void create_func_data(cmd_model *);
void add_f_data(cmd_model *, char **);
void remove_f_data(cmd_model *, int);

char *get_file_history(cmd_model *);
int new_history(cmd_model *);
int read_history_row(cmd_model *);
int new_ll_history(cmd_model *, char *, int);
int arrang_history(cmd_model *);

l_list *add_node_at_start(l_list **, const char *, int);
l_list *add_node_at_end(l_list **, const char *, int);
size_t print_linked_list(const l_list *);
int remove_node_from_index(l_list **, unsigned int);
void clear_node_of_list(l_list **);

size_t ll_size(const l_list *);
char **ll_array(l_list *);
size_t print_list(const l_list *);
l_list *get_prefix(l_list *, char *, char);
ssize_t index_node(l_list *, l_list *);

int free_memory(void **);

int exe_checker(cmd_model *, char *);
char *duplicate_char(char *, int, int);
char *search_in_dir(cmd_model *, char *, char *);

char *mem_aloc(char *, char, unsigned int);
void str_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

int c_main(cmd_model *, char **);
int call_com(cmd_model *);
void find_com(cmd_model *);
void f_run_command(cmd_model *);

int str_length(char *);
int str_compare(char *, char *);
char *haystack_check(const char *, const char *);
char *string_cat(char *, char *);

char *string_copy(char *, char *);
char *string_duplicate(const char *);
void _puts(char *);
int _putchar(char);

char **string_split_two(char *, char *);
char **string_split_one(char *, char);

int check_chaining_delimeter(cmd_model *, char *, size_t *);
void check_chaining_continue(cmd_model *, char *, size_t *, size_t, size_t);
int change_c_alias(cmd_model *);
int change_c_vars(cmd_model *);
int change_str(char **, char *);

#endif
