#include "main.h"

/**
 * twithout_comment - this deletes comments from input
 *
 * @tin: string input
 * Return: input without comments
 */
char *twithout_comment(char *tin)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; tin[i]; i++)
	{
		if (tin[i] == '#')
		{
			if (i == 0)
			{
				free(tin);
				return (NULL);
			}
			if (tin[i - 1] == ' ' || tin[i - 1] == '\t' || tin[i - 1] == ';')
				up_to = i;
		}
	}
	if (up_to != 0)
	{
		tin = _realloc(tin, i, up_to + 1);
		in[up_to] = '\0';
	}
	return (tin);
}

/**
 * tshell_loop - the shell loop
 * @tdatash: the data relevant (av, input, args)
 *
 * Return: no return.
 */
void tshell_loop(data_shell *tdatash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(tdatash, input) == 1)
			{
				tdatash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, tdatash);
			loop = split_commands(tdatash, input);
			tdatash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
