#include "main.h"

/**
  * command_exit - Exit the program.
  *
  * @sh: Pointer to the shell structure.
  *
  * Return: Nothing.
  */

static void command_exit(shell *sh)
{
	if (sh->args[1])
	{
		if (!is_number(sh->args[1]) || sh->args[1][0] == '-')
		{
			pfprintf(STDERR_FILENO, "%s: 1: exit: Illegal number: %s\n",
				"./hsh", sh->args[1]);
			sh->status = 2;
			return;
		}

		if (sh->args[2])
		{
			pfprintf(STDERR_FILENO, "exit: too many arguments\n");
			sh->status = 1;
			return;
		}

		if (is_number(sh->args[1]))
			sh->status = patoi(sh->args[1]);
	}

	sh->run = 0;
}

/**
  * command_env - prints the current environment.
  *
  * @sh: Pointer to the shell structure.
  *
  * Return: Nothing.
  */

static void command_env(shell *sh)
{
	unsigned int i;
	(void)(sh);

	if (!environ)
	{
		pfprintf(STDERR_FILENO, "env: environ is NULL\n");
		return;
	}
	for (i = 0; environ[i]; i++)
		pprintf("%s\n", environ[i]);

	sh->status = 0;
}

/**
  * command_cd - Change the current working directory.
  *
  * @sh: Pointer to the shell structure.
  *
  * Return: Nothing.
  */

static void command_cd(shell *sh)
{
	int chdir_status;
	char buf[BUFFER_SIZE];
	char *new_dir, *old_dir, *oldpwd_var, *pwd_var;

	old_dir = getcwd(buf, BUFFER_SIZE);

	if (!sh->args[1])
		new_dir = pgetenv("HOME");
	else if (pstrcmp(sh->args[1], "-", -1) == 0)
	{
		new_dir = pgetenv("OLDPWD");
		if (new_dir)
			pprintf("%s\n", new_dir);
		else
		{
			new_dir = old_dir;
			pprintf("%s\n", old_dir);
		}
	}
	else
		new_dir = sh->args[1];

	if (!new_dir)
		return;
	chdir_status = chdir(new_dir);
	if (chdir_status == 0)
	{
		oldpwd_var = malloc(100);
		psprintf(oldpwd_var, "OLDPWD=%s", old_dir);
		update_environment(sh, oldpwd_var);
		pwd_var = malloc(100);
		psprintf(pwd_var, "PWD=%s", getcwd(buf, BUFFER_SIZE));
		update_environment(sh, pwd_var);
	}
	else if (sh->args[1])
		pfprintf(STDERR_FILENO, "%s: 1: cd: can't cd to %s\n",
			"./hsh", sh->args[1]);
}

/**
  * get_builtins - Returns an array of builtin commands.
  *
  * Return: Pointer to the array of builtin commands.
  */

command *get_builtins(void)
{
	static command builtins[] = {
		{"exit", command_exit},
		{"env", command_env},
		{"cd", command_cd},
		{"setenv", command_setenv},
		{"unsetenv", command_unsetenv},
		{"alias", commandAlias},
		{NULL, NULL},
	};
	return (builtins);
}
