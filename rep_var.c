#include "main.h"

/**
 * tcheck_env - verifies if variable is an env variable
 * @th: the head of linked list
 * @tin: the input string
 * @tdata: the data structure
 * Return: no return
 */
void tcheck_env(r_var **th, char *tin, data_shell *tdata)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = tdata->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(th, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}
	add_rvar_node(th, j, NULL, 0);
}

/**
 * tcheck_vars - this checks if variable is $$ or $?
 *
 * @th: the linked list's head
 * @tin: string input
 * @tst: the shell's last status
 * @tdata: this is the data structure
 * Return: no return
 */
int tcheck_vars(r_var **th, char *tin, char *tst, data_shell *tdata)
{
	int i, lst, lpd;

	lst = _strlen(tst);
	lpd = _strlen(tdata->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node(th, 2, tst, lst), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(th, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(th, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node(th, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node(th, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node(th, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node(th, 0, NULL, 0);
			else
				check_env(th, tin + i, tdata);
		}
	}
	return (i);
}

/**
 * treplaced_input - this replaces the string into variables
 *
 * @thead: the linked list's head
 * @tinput: string input
 * @tnew_input: new replaced input string
 * @tnlen: the new length
 * Return: replaced string
 */
char *treplaced_input(r_var **thead, char *tinput, char *tnew_input, int tnlen)
{
	r_var *indx;
	int i, j, k;

	indx = *thead;
	for (j = i = 0; i < tnlen; i++)
	{
		if (tinput[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				tnew_input[i] = tinput[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					tnew_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			tnew_input[i] = tinput[j];
			j++;
		}
	}
	return (tnew_input);
}

/**
 * trep_var - this calls functions replace string with vars
 *
 * @tinput: string input
 * @tdatash: the data structure
 * Return: replaced string
 */
char *trep_var(char *tinput, data_shell *tdatash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(tdatash->status);
	head = NULL;

	olen = check_vars(&head, tinput, status, tdatash);
	if (head == NULL)
	{
		free(status);
		return (tinput);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;
	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';
	new_input = replaced_input(&head, input, new_input, nlen);

	free(tinput);
	free(status);
	free_rvar_list(&head);
	return (new_input);
}
