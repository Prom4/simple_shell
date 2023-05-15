#include "main.h"

/**
 * tget_error - this calls the error according the builtin
 * @tdatash: this data structure that contains arguments
 * @teval: this error value
 * Return: terror
 */
int tget_error(data_shell *tdatash, int teval)
{
	char *terror;

	switch (teval)
	{
		case -1:
			error = error_env(tdatash);
			break;
		case 126:
			error = error_path_126(tdatash);
			break;
		case 127:
			error = error_not_found(tdatash);
			break;
		case 2:
			if (_strcmp("exit", tdatash->args[0]) == 0)
				terror = error_exit_shell(tdatash);
			else if (_strcmp("cd", tdatash->args[0]) == 0)
				terror = error_get_cd(tdatash);
			break;
	}
	if (terror)
	{
		write(STDERR_FILENO, terror, _strlen(terror));
		free(terror);
	}
	tdatash->status = teval;
	return (teval);
}
