#include "main.h"

/**
  * printAliases - Print all aliases in a shell struct.
  *
  * @sh: Pointer to the shell structure
  *
  * Return: Nothing.
  */

void printAliases(shell *sh)
{
	int j;

	for (j = 0; j < ALIASES_SIZE; j++)
	{
		if (sh->aliases[j].name != NULL)
		{
			pprintf("%s='%s'\n", sh->aliases[j].name, sh->aliases[j].value);
		}
	}
}

/**
  * printAlias - Print the alias of a given name.
  *
  * @sh: Pointer to shell struct.
  * @name: Name of the alias to be printed with value.
  *
  * Return: Nothing.
  */

void printAlias(shell *sh, char *name)
{
	int j;

	for (j = 0; j < ALIASES_SIZE; j++)
	{
		if (sh->aliases[j].name && pstrcmp(sh->aliases[j].name, name, -1) == 0)
		{
			pprintf("%s='%s'\n", sh->aliases[j].name, sh->aliases[j].value);
		}
	}
}

/**
  * setAlias - Set an alias in the shell.
  *
  * @sh: Pointer to the shell struct.
  * @name: Name of the alias.
  * @value: Value of the alias.
  *
  * Return: Nothing.
  */

void setAlias(shell *sh, char *name, char *value)
{
	char *new_value;
	int i, j = 0, found = 0;
	int len = pstrlen(value);

	new_value = malloc(len + 1);

	for (i = 0; i < len; i++)
	{
		if (value[i] != '"' && value[i] != '\'')
			new_value[j++] = value[i];
	}
	new_value[j] = '\0';
	for (j = 0; j < ALIASES_SIZE; j++)
	{
		if (sh->aliases[j].name && pstrcmp(sh->aliases[j].name, name, -1) == 0)
		{
			free(sh->aliases[j].value);
			sh->aliases[j].value = pstrdup(new_value);
			found = 1;
			break;
		}
	}

	if (!found)
	{
		for (j = 0; j < ALIASES_SIZE; j++)
		{
			if (sh->aliases[j].name == NULL)
			{
				sh->aliases[j].name = pstrdup(name);
				sh->aliases[j].value = pstrdup(new_value);
				break;
			}
		}
	}

	free(new_value);
}

/**
  * commandAlias - Set or print aliases.
  *
  * @sh: Pointer to the shell struct.
  *
  * Return: Nothing.
  */

void commandAlias(shell *sh)
{
	int i = 1, index, j;
	char name[ALIASES_SIZE];
	char *arg, *value, *equal_sign;

	if (sh->args[i] == NULL)
	{
		printAliases(sh);
		return;
	}

	for (; sh->args[i] != NULL; i++)
	{
		arg = sh->args[i];
		equal_sign = NULL;
		for (index = 0; arg[index] != '\0'; index++)
		{
			if (arg[index] == '=')
			{
				equal_sign = &arg[index];
				break;
			}
		}

		if (equal_sign)
		{
			index = equal_sign - arg;
			for (j = 0; j < index && j < ALIASES_SIZE - 1; j++)
				name[j] = arg[j];

			name[j] = '\0';
			value = equal_sign + 1;
			setAlias(sh, name, value);
		}
		else
			printAlias(sh, arg);
	}
}

/**
  * getAliasValue - Retrieve the value of an alias from a shell struct.
  *
  * @sh: Pointer to the shell structure.
  * @name: Name of the alias to retrieve.
  *
  * Return: The value of the alias, or NULL if not found.
  */

char *getAliasValue(shell *sh, char *name)
{
	int i;
	char *value = NULL;
	alias *curr_alias;

	for (i = 0; i < ALIASES_SIZE; i++)
	{
		curr_alias = &sh->aliases[i];
		if (curr_alias->name && pstrcmp(curr_alias->name, name, -1) == 0)
		{
			value = curr_alias->value;
			break;
		}
	}

	for (i = 0; value && i < ALIASES_SIZE; i++)
	{
		curr_alias = &sh->aliases[i];
		if (curr_alias->name && pstrcmp(curr_alias->name, value, -1) == 0)
		{
			value = curr_alias->value;
			break;
		}
	}

	return (value);
}
