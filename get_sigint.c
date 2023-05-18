#include "main.h"

/**
 * get_sigint - in prompt takes care of Ctrl + c
 * @sig: the signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
