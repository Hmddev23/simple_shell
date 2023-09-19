#include "main.h"

/**
  * main - Entry point for the simple-shell program.
  *
  * @argc: Arguments counter.
  * @argv: Arguments values.
  *
  * Return: Last command executed status code.
  */

int main(int argc, char **argv)
{
	shell sh = {0};

	initialize_shell(&sh, argc, argv);

	while (sh.run)
	{
		if (sh.interactive)
			pprintf("$ ");

		process_command(&sh);
	}

	free_mem_shell(&sh);
	return (sh.status);
}

/**
  * initialize_shell - Initialize the shell struct.
  *
  * @argc: The number of arguments passed to the program.
  * @argv: An array[string] of the arguments passed to the program.
  * @sh: Pointer to the shell structure..
  *
  * Return: Nothing.
  */

void initialize_shell(shell *sh, int argc, char **argv)
{
	command *builtins = get_builtins();

	sh->builtins = builtins;
	sh->run = 1;
	sh->argc = argc;
	sh->argv = argv;

	while (builtins[sh->num_builtins].name)
		sh->num_builtins++;

	sh->interactive = isatty(STDIN_FILENO) && argc == 1;
}

/**
  * free_mem_shell - Frees the memory allocated for a shell structure.
  *
  * @sh: The shell structure to be freed.
  *
  * Return: Nothing.
  */

void free_mem_shell(shell *sh)
{
	int i;

	if (sh->input)
		free_double(&sh->input);

	if (sh->args)
		free(sh->args);

	if (sh->environ_copy)
		free_double(&sh->environ_copy);

	for (i = 0; sh->aliases[i].name; i++)
	{
		if (sh->aliases[i].name)
			free(sh->aliases[i].name);
		if (sh->aliases[i].value)
			free(sh->aliases[i].value);
	}
}
