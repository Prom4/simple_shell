#include "main.h"

/**
 * tread_line - this takes input string.
 * @ti_eof: this returns value of getline
 * Return: string inputted
 */
char *tread_line(int *ti_eof)
{
	char *tinput = NULL;
	size_t tbufsize = 0;

	*ti_eof = getline(&tinput, &tbufsize, stdin);
	return (tinput);
}
