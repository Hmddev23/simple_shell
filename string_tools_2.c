#include "main.h"

/**
  * write_str - Write a string to a file descriptor.
  *
  * @fd: The file descriptor to write to.
  * @s: The string to write.
  *
  * Return: Nothing.
  */

void write_str(int fd, char *s)
{
	(!s) && (s = "(null)");
	write(fd, s, pstrlen(s));
}

/**
  * pstrchr - Searche for a character in a string.
  *
  * @s: Pointer to the string to search.
  * @c: Character to search for.
  *
  * Return: Pointer to the first occurrence of c in s, or NULL if not found.
  */

char *pstrchr(char *s, int c)
{
	while (*s != (char)c)
	if (!*s++)
		return (0);

	return (s);
}

/**
  * pstrdup - Duplicate a string.
  *
  * @s: String to duplicate.
  *
  * Return: Pointer to the duplicated string, or NULL if fails.
  */

char *pstrdup(const char *s)
{
	int i;
	char *result;

	result = malloc(sizeof(char) * (pstrlen((char *)s) + 1));
	if (result == NULL)
		return (NULL);

	for (i = 0; s[i]; i++)
		result[i] = s[i];

	result[i] = '\0';

	return (result);
}

/**
  * pstrtok - Tokenize a string by a given delimiter.
  *
  * @str: String to split.
  * @delim: Delimiter used for tokenization.
  *
  * Return: A pointer to the next token in the string.
  */

char *pstrtok(char *str, char *delim)
{
	static char *next;
	char *curr = str ? str : next;

	if (!curr)
		return (NULL);

	while (*curr && pstrchr(delim, *curr))
		curr++;
	if (!*curr)
		return (NULL);

	next = curr;
	while (*next)
	{
		if (*next == '"')
		{
			next++;
			while (*next && *next != '"')
				next++;
			if (*next == '"')
				next++;
		}
		else if (pstrchr(delim, *next))
		{
			break;
		}
		else
			next++;
	}
	if (*next)
		*next++ = '\0';
	return (curr);
}

/**
  * pstrtok_r - Tokenize a string using a delimiter (safe).
  *
  * @str: String to split.
  * @delim: Delimiter character.
  * @saveptr: Pointer to save position.
  *
  * Return: Pointer to the start of the token, or NULL if no more tokens.
  */

char *pstrtok_r(char *str, const char *delim, char **saveptr)
{
	char *token_start, *token_end;
	const char *d;

	if (str == NULL)
		str = *saveptr;
	token_start = str;
	while (*token_start != '\0')
	{
		for (d = delim; *d != '\0'; d++)
			if (*token_start == *d)
				break;
		if (*d == '\0')
			break;
		token_start++;
	}
	if (*token_start == '\0')
	{
		*saveptr = token_start;
		return (NULL);
	}
	token_end = token_start;
	while (*token_end != '\0')
	{
		for (d = delim; *d != '\0'; d++)
			if (*token_end == *d)
				break;
		if (*d != '\0')
			break;
		token_end++;
	}
	if (*token_end != '\0')
	{
		*token_end = '\0';
		*saveptr = token_end + 1;
	}
	else
		*saveptr = token_end;

	return (token_start);
}
