#include "main.h"

/**
 * tget_sigint - takes care of Ctrl + c
 * @tsig: the signal handler
 */
void tget_sigint(int tsig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
