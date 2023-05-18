#include "main.h"

/**
 * read_line - this takes input string.
 * @i_eof: this returns value of getline
 * Return: string inputted
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);
	return (input);
}
