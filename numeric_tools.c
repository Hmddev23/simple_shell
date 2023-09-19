#include "main.h"

/**
  * is_number - Check if a string represents a numeric value.
  *
  * @str: Input string to be checked.
  *
  * Return: 1 if the string represents a numeric value, 0 otherwise.
  */

int is_number(char *str)
{
	int i = 0;

	if (str[0] == '-' || str[0] == '+')
		i++;

	for (; str[i]; i++)
		if (str[i] >= '0' && str[i] <= '9')
			return (1);

	return (0);
}

/**
  * patoi - Convert a string of digits into an integer.
  *
  * @str: String to be converted.
  *
  * Return: Converted integer.
  */

int patoi(const char *str)
{
	unsigned int i = 0, result = 0, sign = 1;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	for (; str[i] >= '0' && str[i] <= '9'; i++)
		result = result * 10 + (str[i] - '0');

	return (sign * result);
}

/**
  * pitoa - Convert a integer to a string in the given base (n).
  *
  * @x: Integer to convert.
  * @s: Output string.
  * @base: Base of the number.
  * @sign: Whether or not to include a sign character.
  *
  * Return: Length of the string.
  */

int pitoa(long x, char s[], int base, int sign)
{
	unsigned int n, i = 0, neg = 0;

	if (sign && x < 0)
	{
		neg = 1;
		n = -x;
	}
	else
		n = x;

	do
		s[i++] = n % base + '0';
	while ((n /= base) > 0);

	if (neg)
		s[i++] = '-';

	s[i] = '\0';
	reverse_str(s);
	return (i);
}

/**
  * prealloc - Reallocate a block of memory.
  *
  * @ptr: Pointer to the previously allocated memory.
  * @old_size: Size of the memory block pointed by @ptr.
  * @new_size: New size of the memory block to be allocated.
  *
  * Return: pointer to the newly allocated memory, or NULL if it fails.
  */

void *prealloc(void *ptr, ssize_t old_size, ssize_t new_size)
{
	void *new_ptr;

	if (!ptr)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	pmemcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
	free(ptr);

	return (new_ptr);
}

/**
  * free_double - Free a double pointer.
  *
  * @ptr: Double pointer to be freed.
  *
  * Return: Nothing.
  */

void free_double(char ***ptr)
{
	int i;

	for (i = 0; (*ptr)[i]; i++)
		free((*ptr)[i]);
	free(*ptr);
	*ptr = NULL;
}
