#include "main.h"

/**
 * tfree_data - this frees the data structure
 * @tdatash: the data structure
 * Return: no return
 */
void tfree_data(data_shell *tdatash)
{
	unsigned int i;

	for (i = 0; tdatash->_environ[i]; i++)
	{
		free(tdatash->_environ[i]);
	}

	free(tdatash->_environ);
	free(tdatash->pid);
}

/**
 * tset_data - this Initializes the data structure
 * @tdatash: the data structure
 * @tav: the argument vector
 * Return: no return
 */
void tset_data(data_shell *tdatash, char **tav)
{
	unsigned int i;

	tdatash->tav = tav;
	tdatash->input = NULL;
	tdatash->args = NULL;
	tdatash->status = 0;
	tdatash->counter = 1;

	for (i = 0; environ[i]; i++)
	{
		tdatash->_environ = malloc(sizeof(char *) * (i + 1));
	}

	for (i = 0; environ[i]; i++)
	{
		tdatash->_environ[i] = _strdup(environ[i]);
	}
	tdatash->_environ[i] = NULL;
	tdatash->pid = aux_itoa(getpid());
}

/**
 * main - The Entry point
 * @tac: argument count
 * @tav: argument vector
 *
 * Return: 0 on success.
 */
int main(int tac, char **tav)
{
	data_shell tdatash;
	(void) tac;
	signal(SIGINT, get_sigint);
	set_data(&tdatash, tav);
	shell_loop(&tdatash);
	free_data(&tdatash);
	if (tdatash.status < 0)
		return (255);
	return (tdatash.status);
}
