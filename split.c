#include "main.h"

/**
 * tswap_char - this swaps | and & for non-printed chars
 *
 * @tinput: string input
 * @tbool: type of swap
 * Return: swapped string
 */
char *tswap_char(char *tinput, int tbool)
{
	int i;

	if (tbool == 0)
	{
		for (i = 0; tinput[i]; i++)
		{
			if (tinput[i] == '|')
			{
				if (tinput[i + 1] != '|')
					tinput[i] = 16;
				else
					i++;
			}

			if (tinput[i] == '&')
			{
				if (tinput[i + 1] != '&')
					tinput[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; tinput[i]; i++)
		{
			tinput[i] = (tinput[i] == 16 ? '|' : tinput[i]);
			tinput[i] = (tinput[i] == 12 ? '&' : tinput[i]);
		}
	}
	return (tinput);
}

/**
 * tadd_nodes - this add separators and command lines in lists
 *
 * @thead_s: the head of separator list
 * @thead_l: head of command lines list
 * @tinput: string input
 * Return: no return
 */
void tadd_nodes(sep_list **thead_s, line_list **thead_l, char *tinput)
{
	int i;
	char *line;

	tinput = swap_char(tinput, 0);

	for (i = 0; tinput[i]; i++)
	{
		if (tinput[i] == ';')
			add_sep_node_end(thead_s, tinput[i]);

		if (tinput[i] == '|' || tinput[i] == '&')
		{
			add_sep_node_end(thead_s, tinput[i]);
			i++;
		}
	}

	line = _strtok(tinput, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * tgo_next - this goes to the next command line
 *
 * @tlist_s: the separator list
 * @tlist_l: the command line list
 * @tdatash: the data structure
 * Return: no return
 */
void tgo_next(sep_list **tlist_s, line_list **tlist_l, data_shell *tdatash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;

	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (tdatash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}
	*tlist_s = ls_s;
	*tlist_l = ls_l;
}

/**
 * tsplit_commands - this splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @tdatash: the data structure
 * @tinput: the input string
 * Return: 0 to exit, 1 to continue
 */
int tsplit_commands(data_shell *tdatash, char *tinput)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		tdatash->input = list_l->line;
		tdatash->args = split_line(tdatash->input);
		loop = exec_line(tdatash);
		free(tdatash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, tdatash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * tsplit_line - the tokenizes the input string
 *
 * @tinput: tinput string.
 * Return: string splitted.
 */
char **tsplit_line(char *tinput)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}
	return (tokens);
}
