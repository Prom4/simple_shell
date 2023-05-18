#include "main.h"

/**
 * cmp_env_name - this section compares env names
 * when the names are passed
 * @nenv: this is the environment variable
 * @name: this is the passed name
 *
 * Return: 0 if are not equal else another value
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
	if (nenv[i] != name[i])
	{
		return (0);
}
}
return (i + 1);
}

/**
 * _getenv - this gets an environment variable
 * @name: this gives the name of the environment variable
 * @_environ: this is the environment variable
 *
 * Return: the value of the environment variable if it is found successfully.
 * else, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, move;

	/* Initializing ptr_env value */
	ptr_env = NULL;
	move = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		move = cmp_env_name(_environ[i], name);
		if (move)
		{
			ptr_env = _environ[i];
			break;
		}
	}
	return (ptr_env + move);
}

/**
 * _env - this actually prints the evironment variables
 *
 * @datash: the relevant data.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{
		for (j = 0; datash->_environ[i][j]; j++)
			;
		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;
	return (1);
}
