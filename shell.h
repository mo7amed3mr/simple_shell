#ifndef SHELL_H_INCLUDED
#define SHELL_H_INCLUDED
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sys/wait.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define END_OF_FILE -2
#define EXIT -3

/**
 * struct alias_s - a struct that represents an alias.
 * @name: the alias name.
 * @value: the alias value.
 * @next: a pointer to the next alias in the list.
 * Description: This typedef defines an alias_t type
 * that is a struct with three fields.
*/
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/**
 * struct builtin_s - a struct that represents a builtin command.
 * @name: the name of the builtin command.
 * @f: a pointer to a function that executes the builtin command.
 * Description: typedef defines a builtin_t type is a struct with two fields.
*/
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
*/
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

extern alias_t *aliases;

extern char **environ;

extern char *program_name;

extern int history;

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
char **replace_aliases(char **args);

int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

char **_getenv(const char *var);
void free_env(void);
char **_copyenv(void);

int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_126(char **args);
char *error_127(char **args);
char *error_syntax(char **args);
char *error_exit(char **args);
char *error_cd(char **args);

int cant_open(char *file_path);
int read_file(char *file_path, char **line, int *exe_ret);
int proc_file_commands(char *file_path, int *exe_ret);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);

char *_strcat(char *dest, char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(char *str, char ch);
int _strlen(const char *str);
int _is_included(char letter, char *prefix);
unsigned int _strspn(char *str, char *prefix);
char *_strcpy(char *dest, char *src);

void free_args(char **args, char **front);
void logical_ops(char *line, ssize_t *new_len);
ssize_t get_new_len(char *line);
void handle_line(char **line, ssize_t read);
int check_args(char **args);
int handle_args(int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int handle_operators(char **args, char **front, int *exe_ret, char *op);
char *get_pid(void);
char *get_env_value(char *beginning, int length);
void variable_replacement(char **line, int *exe_ret);
char *get_substitute(char *old_input, int *exe_ret, int *i, int *start);

int num_len(int num);
char *_itoa(int num);

list_t *add_node_end(list_t **head, char *dir);
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_list(list_t *head);
void free_alias_list(alias_t *head);
list_t *get_path_dir(char *path);
char *get_location(char *command);
char *fill_path_dir(char *path);

int shell_cd(char **args, char __attribute__((__unused__)) **front);
int is_dash(char *arg);
void chdir_to_oldpwd(void);
int is_valid_dir(char *arg, struct stat *dir);
void chdir_to_home(void);
int update_env(char *oldpwd, char *pwd);
void print_pwd(char *pwd);
int handle_error(char **args, char *oldpwd);

int token_length(char *str, char *delim);
int count_tok(char *str, char *delim);
char **_strtok(char *line, char *delim);

void signal_handler(int sign);
int execute(char **args, char **front);
int execute_command(char *command, char **args, char **front);
void clean_up(void);
int handle_interactive(int *exe_ret);
int handle_non_interactive(int *exe_ret);

#endif
