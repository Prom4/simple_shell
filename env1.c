#include "main.h"

/**
 * tcmp_env_name - this section compares env names
 * when the names are passed
 * @tnenv: this is the environment variable
 * @tname: this is the passed name
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int tcmp_env_name(const char *tnenv, const char *tname)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
	if (tnenv[i] != tname[i])
	{
		return (0);
}
}
return (i + 1);
}

/**
 * _tgetenv - this gets an environment variable
 * @tname: this gives the name of the environment variable
 * @_tenviron: this is the environment variable
 *
 * Return: the value of the environment variable if it is found successfully.
 * else, returns NULL.
 */
char *_tgetenv(const char *tname, char **_tenviron)
{
	char *tptr_env;
	int i, move;

	/* Initialize ptr_env value */
	tptr_env = NULL;
	move = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		move = tcmp_env_name(_environ[i], tname);
		if (move)
		{
			tptr_env = _tenviron[i];
			break;
		}
	}
	return (tptr_env + move);
}

/**
 * _tenv - this actually prints the evironment variables
 *
 * @tdatash: the relevant data.
 * Return: 1 on success.
 */
int _tenv(data_shell *tdatash)
{
	int i, j;

	for (i = 0; tdatash->_tenviron[i]; i++)
	{
		for (j = 0; tdatash->_tenviron[i][j]; j++)
			;
		write(STDOUT_FILENO, tdatash->_tenviron[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	tdatash->status = 0;
	return (1);
}
