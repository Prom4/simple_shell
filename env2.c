#include "main.h"

/**
 * tcopy_info - this copies the info it is to create
 * to a new env or alias
 * @tname: the name either env or alias
 * @tvalue: the value either env or alias
 *
 * Return: either new env or new alias.
 */
char *tcopy_info(char *tname, char *tvalue)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(tname);
	len_value = _strlen(tvalue);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, tname);
	_strcat(new, "=");
	_strcat(new, tvalue);
	_strcat(new, "\0");
	return (new);
}

/**
 * tset_env - this sets an environment variable
 *
 * @tname: this is the name of the environment variable
 * @tvalue: the value of the environment variable used
 * @tdatas: data structure
 * Return: no return
 */
void tset_env(char *tname, char *tvalue, data_shell *tdatas)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; tdatas->_environ[i]; i++)
	{
		var_env = _strdup(tdatas->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, tname) == 0)
		{
			free(tdatas->_environ[i]);
			tdatas->_environ[i] = copy_info(name_env, tvalue);
			free(var_env);
			return;
		}
		free(var_env);
	}
	tdatas->_environ = _reallocdp(tdatas->_environ, i, sizeof(char *) * (i + 2));
	tdatas->_environ[i] = copy_info(name, tvalue);
	datash->_environ[i + 1] = NULL;
}

/**
 * _tsetenv - this compares env variables names
 * with the name inputted.
 * @tdatash: data relevant
 *
 * Return: 1 on success.
 */
int _tsetenv(data_shell *tdatash)
{
	if (tdatash->args[1] == NULL || tdatash->args[2] == NULL)
	{
		get_error(tdatash, -1);
		return (1);
	}
	set_env(tdatash->args[1], tdatash->args[2], tdatash);
	return (1);
}

/**
 * _tunsetenv - this deletes an environment variable
 *
 * @tdatash: data relevant
 *
 * Return: 1 on success.
 */
int _tunsetenv(data_shell *tdatash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (tdatash->args[1] == NULL)
	{
		get_error(tdatash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; tdatash->_environ[i]; i++)
	{
		var_env = _strdup(tdatash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, tdatash->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(tdatash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; tdatash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = tdatash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(tdatash->_environ[k]);
	free(tdatash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
