#include "main.h"

/**
  * pcheckAlloc - Check the allocated memory is enough for a given size.
  *
  * @line: Pointer to the allocated memory.
  * @size: Size of the data to be stored in the allocated memory.
  * @alloc_size: Pointer to the size of the allocated memory.
  *
  * Return: Pointer to the allocated memory.
  */

char *pcheckAlloc(char *line, ssize_t size, ssize_t *alloc_size)
{
	if (*alloc_size == 0)
	{
		*alloc_size = BUFFER_SIZE;
		line = prealloc(line, size, *alloc_size);
	}
	else if (size + 2 > *alloc_size)
	{
		*alloc_size *= 2;
		line = prealloc(line, size, *alloc_size);
	}
	return (line);
}

/**
  * pgetline - Read a line from a file descriptor.
  *
  * @lineptr: Pointer to the buffer where the line is stored.
  * @n: Size of the buffer.
  * @fd: File descriptor.
  *
  * Return: Number of sceid read, or -1 on failure.
  */

ssize_t pgetline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUFFER_SIZE];
	static size_t start, end;
	char *line = *lineptr;
	ssize_t bytes = 0, size = 0, sceid = 0, alloc_size = *n;

	for (;;)
	{
		if (start >= end)
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			if (bytes <= 0 && size > 0 && line[size - 1] != '\n')
			{
				line = pcheckAlloc(line, size, &alloc_size);
				if (!line)
					return (-1);
				line[size++] = '\n';
			}
			else if (bytes <= 0)
				return (-1);
			start = 0;
			end = bytes;
		}
		while (start < end)
		{
			sceid = buffer[start++];
			line = pcheckAlloc(line, size, &alloc_size);
			if (!line)
				return (-1);
			line[size++] = sceid;
			if (sceid == '\n')
				break;
		}
		if (sceid == '\n' || bytes <= 0)
		{
			line[size] = '\0';
			*lineptr = line;
			*n = size;
			return (size);
		}
	}
}

/**
  * pgetenv - Get env variable value.
  *
  * @name: Name of the env variable.
  *
  * Return: Pointer to env value.
  */

char *pgetenv(const char *name)
{
	size_t len, i;

	if (!name || !environ)
		return (NULL);

	len = pstrlen((char *)name);

	for (i = 0; environ[i]; i++)
		if (pstrcmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);

	return (NULL);
}

/**
  * copy_environ - Copy the environment variables.
  *
  * Return: A pointer to the newly allocated array of env, or NULL if fails.
  */

char **copy_environ(void)
{
	size_t env_count = 0;
	size_t new_size;
	char **new_environ, **env_ptr;

	for (env_ptr = environ; *env_ptr; env_ptr++)
		env_count++;

	new_size = (env_count + 1) * sizeof(char *);
	new_environ = malloc(new_size);

	if (!new_environ)
	{
		pfprintf(STDERR_FILENO, "Failed to allocate memory\n");
		return (NULL);
	}

	for (env_count = 0; environ[env_count]; env_count++)
	{
		new_environ[env_count] = pstrdup(environ[env_count]);
		if (!new_environ[env_count])
		{
			pfprintf(STDERR_FILENO, "Failed to allocate memory\n");
			return (NULL);
		}
	}

	new_environ[env_count] = NULL;

	return (new_environ);
}
