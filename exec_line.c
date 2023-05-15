#include "main.h"

/**
 * texec_line - thisfinds builtins and commands
 *
 * @datas: this is data relevant (args)
 * Return: 1 on success.
 */
int texec_line(data_shell *datas)
{
	int (*builtin)(data_shell *datas);

	if (datas->args[0] == NULL)
		return (1);
	builtin = get_builtin(datas->args[0]);
	if (builtin != NULL)
		return (builtin(datas));
	return (cmd_exec(datas));
}
