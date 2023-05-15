#include "main.h"

/**
 * tbring_line - this assigns line var for get_line
 * @tlineptr: Buffer to store input string
 * @tbuffer: string called to the line
 * @tn: Line size
 * @tj: buffer size
 */
void tbring_line(char **tlineptr, size_t *tn, char *tbuffer, size_t tj)
{
	if (*tlineptr == NULL)
	{
		if (tj > BUFSIZE)
			*tn = tj;
		else
			*tn = BUFSIZE;
		*tlineptr = tbuffer;
	}
	else if (*tn < tj)
	{
		if (tj > BUFSIZE)
			*tn = tj;
		else
			*tn = BUFSIZE;
		*tlineptr = tbuffer;
	}
	else
	{
		_strcpy(*tlineptr, tbuffer);
		free(tbuffer);
	}
}
/**
 * tget_line - gets input from the stream
 * @tlineptr: buffer to store input
 * @tn: lineptr size
 * @tstream: source of stream
 * Return: size in bytes
 */
ssize_t tget_line(char **tlineptr, size_t *tn, FILE *tstream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *tbuffer;
	char t = 'z';

	if (input == 0)
		fflush(tstream);
	else
		return (-1);
	input = 0;

	tbuffer = malloc(sizeof(char) * BUFSIZE);
	if (tbuffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(tbuffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			tbuffer = _realloc(tbuffer, input, input + 1);
		tbuffer[input] = t;
		input++;
	}
	tbuffer[input] = '\0';
	bring_line(tlineptr, tn, tbuffer, input);
	tretval = input;
	if (i != 0)
		input = 0;
	return (tretval);
}
