#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>

#define BUFFER_SIZE 2048
#define ALIASES_SIZE 100
#define MAX_ARGS 10
#define LINE_SIZE 1024


typedef struct shell shell;


/**
  * struct command - Struct to store a command function.
  *
  * @name: Pointer to command name string.
  * @func: Pointer to function associated with the command.
  */

typedef struct command
{
	char *name;
	void (*func)(shell *);
} command;


/**
  * struct alias - Struct for aliasing name and value.
  *
  * @name: Pointer to alias name
  * @value: Pointer to alias value
  */

typedef struct alias
{
	char *name;
	char *value;
} alias;


/**
  * struct shell - Struct for shell environment information.
  *
  * @input: An array of strings containing commands from the user input
  * @args: An array of strings containing arguments from the user input
  * @environ_copy: An array of strings containing a copy of the environ
  * @builtins: A pointer to an array of containing about the builtin commands
  * @num_builtins: The count of builtin commands
  * @cmd_count: The count of commands in the user input
  * @status: The exit status of the last command executed
  * @interactive: A boolean whether the program is running interactively or not
  * @builtins: A pointer to an array of containing about the builtin commands
  * @run: A boolean whether or not the shell should continue running
  * @aliases: An array of alias structures containing user-defined aliases
  * @argc: Arguments counter.
  * @argv: Arguments values.
  */

struct shell
{
	char **input;
	char **args;
	char **environ_copy;
	int num_builtins;
	int cmd_count;
	int status;
	int run;
	int argc;
	char **argv;
	int interactive;
	command *builtins;
	alias aliases[ALIASES_SIZE];
};


extern char **environ;

/* string_tools.c */
int pstrlen(char *s);
void reverse_str(char s[]);
int pstoa(char *s, char *buf);
int pstrcmp(const char *s1, const char *s2, size_t n);
void *pmemcpy(void *dest, const void *src, size_t n);

/* string_tools2.c */
char *pstrchr(char *s, int c);
char *pstrdup(const char *s);
char *pstrtok(char *str, char *delim);
char *pstrtok_r(char *str, const char *delim, char **saveptr);

/* main.c */
void initialize_shell(shell *sh, int argc, char **argv);
void free_mem_shell(shell *sh);

/* alias_functions.c */
void commandAlias(shell *sh);
char *getAliasValue(shell *sh, char *name);

/* print_shell.c */
void pprintf(const char *fmt, ...);
void pfprintf(int fd, const char *fmt, ...);
void psprintf(char *str, const char *fmt, ...);

/* find_command.c */
char *find_command(char *command);

/* command_execution.c */
int builtin_command(shell *sh);
void external_command(shell *sh, int *curr_line);
void execute_command(shell *sh, int *curr_line);
void process_command(shell *sh);

/* numeric_tools.c */
int is_number(char *str);
int patoi(const char *str);
int pitoa(long n, char s[], int base, int sign);
void *prealloc(void *ptr, ssize_t old_size, ssize_t new_size);
void free_double(char ***ptr);

/* std_input.c */
void read_input(shell *sh);
void parse_command(shell *sh, char *cmd);

/* builtin_functions.c */
command *get_builtins(void);

/* builtin_functions2.c */
void update_environment(shell *sh, char *env_var);
void command_setenv(shell *sh);
void command_unsetenv(shell *sh);

/* system_tools.c */
ssize_t pgetline(char **lineptr, size_t *n, int fd);
char *pgetenv(const char *name);
char **copy_environ(void);


command *get_built(void);
int num_built(void);


#endif /* MAIN_H */
