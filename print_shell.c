#include "main.h"

/**
  * pvsprintf - Write a formatted string to a buffer.
  *
  * @str: The buffer to write to.
  * @fmt: The format string.
  * @ap: The list of arguments.
  *
  * Return: Nothing.
  */

void pvsprintf(char *str, const char *fmt, va_list ap)
{
	char c;
	int i, state = 0;

	for (i = 0; fmt[i]; i++)
	{
		c = fmt[i];
		if (state == 0)
			(c == '%') ? (state = '%') : (*str++ = c);
		else if (state == '%')
		{
			if (c == 'd')
				str += pitoa(va_arg(ap, int), str, 10, 1);
			else if (c == 'l')
				str += pitoa(va_arg(ap, size_t), str, 10, 0);
			else if (c == 'x')
				str += pitoa(va_arg(ap, int), str, 16, 0);
			else if (c == 'p')
			{
				(*str++ = '0', *str++ = 'x');
				str += pitoa(va_arg(ap, size_t), str, 16, 0);
			}
			else if (c == 's')
				str += pstoa(va_arg(ap, char *), str);
			else if (c == 'c')
				*str++ = va_arg(ap, int);
			else if (c == '%')
				*str++ = c;
			else
				(*str++ = '%', *str++ = c);
			state = 0;
		}
	}
	*str = '\0';
}

/**
  * psprintf - Write a formatted string to a array of chars.
  *
  * @str: The char array to write the formatted string to.
  * @fmt: The format string to use for writing.
  * @...: Optional arguments used in the format string.
  *
  * Return: Nothing.
  */

void psprintf(char *str, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	pvsprintf(str, fmt, ap);
	va_end(ap);
}

/**
  * pfprintf - Print a formatted string to a file descriptor.
  *
  * @fd: File descriptor to write to.
  * @fmt: Format string.
  * @...: Optional arguments used in the format string.
  *
  * Return: Nothing.
  */

void pfprintf(int fd, const char *fmt, ...)
{
	char buf[BUFFER_SIZE];
	va_list ap;

	va_start(ap, fmt);
	pvsprintf(buf, fmt, ap);
	write(fd, buf, pstrlen(buf));
	va_end(ap);
}

/**
  * pprintf - Print a formatted string to the standard output.
  *
  * @fmt: Format string containing text and format specifiers.
  * @...: Optional arguments used in the format string.
  *
  * Return: Nothing.
  */

void pprintf(const char *fmt, ...)
{
	va_list ap;
	char buf[BUFFER_SIZE];

	va_start(ap, fmt);
	pvsprintf(buf, fmt, ap);
	write(1, buf, pstrlen(buf));
	va_end(ap);
}
