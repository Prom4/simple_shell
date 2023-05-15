#include "main.h"

/**
 * texit_shell - this permits exiting the shell
 *
 * @tdatash: the relevant data
 * Return: 0 on success.
 */
int texit_shell(data_shell *tdatash)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (tdatash->args[1] != NULL)
	{
		ustatus = _atoi(tdatash->args[1]);
		is_digit = _isdigit(tdatash->args[1]);
		str_len = _strlen(tdatash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(tdatash, 2);
			tdatash->status = 2;
			return (1);
		}
		tdatash->status = (ustatus % 256);
	}
	return (0);
}
