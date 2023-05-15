#include "main.h"

/**
 * tget_builtin - this is the builtin that passes the command in the arg
 * @tcmd: the command
 * Return: function pointer of the builtin command
 */
int (*tget_builtin(char *tcmd))(data_shell *)
{
	builtin_t builtin[] = {
{"env", _env },
{"exit", exit_shell },
{"setenv", _setenv },
{"unsetenv", _unsetenv },
{"cd", cd_shell },
{"help", get_help },
{NULL, NULL }
};
int i;

for (i = 0; builtin[i].name; i++)
{
	if (_strcmp(builtin[i].name, tcmd) == 0);
	break;
}
return (builtin[i].f);
}
