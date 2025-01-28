/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:52:33 by braugust          #+#    #+#             */
/*   Updated: 2025/01/28 09:50:41 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_var_command(t_command *command, int exit_status, t_env *env_list)
{
    t_expand_state state;
    int				i;
	int				j;
    const char		*input;

    while (command)
    {
        // Expansion des arguments
        i = 0;
        while (command->args && command->args[i])
        {
            state.result = strdup("");
            state.in_quote = 0;
            state.exit_status = exit_status;
			
            input = command->args[i];
            j = 0;
            while (input[j])
            {
                if (input[j] == '\'' || input[j] == '\"')
				{
                    handle_quotes(input[j], &state);
					append_char(&state.result, input[j]);
				}
                else if (input[j] == '$' && state.in_quote != 2)
                    handle_expansion(&state, input, &j, env_list);
                else
                    append_char(&state.result, input[j]);
                j++;
            }
            command->args[i] = state.result;
            i++;
        }
        // Expansion des fichiers de redirection
        i = 0;
        while (i < command->redir_size)
        {
            state.result = strdup("");
            state.in_quote = 0;
            state.exit_status = exit_status;

            input = command->redirs[i].file;
            j = 0;
            while (input[j])
            {
                if (input[j] == '\'' || input[j] == '\"')
                    handle_quotes(input[j], &state);
                else if (input[j] == '$' && state.in_quote != 2)
                    handle_expansion(&state, input, &j, env_list);
                else
                    append_char(&state.result, input[j]);
                j++;
            }
            command->redirs[i].file = state.result;
            i++;
        }

        command = command->next;
    }
}


int	handle_quotes(char c, t_expand_state *state)
{
	if (c == '"' && state->in_quote != 2)
	{
		if (state->in_quote == 1)
			state->in_quote = 0;
		else
			state->in_quote = 1;
		return (1);
	}
	else if (c == '\'' && state->in_quote != 1)
	{
		if (state->in_quote == 2)
			state->in_quote = 0;
		else
			state->in_quote = 2;
		return (1);
	}
	return (0);
}

void	handle_expansion(t_expand_state *state, const char *input, int *i, t_env *env_list)
{
	int		start;
	char	*var_name;
	char	*var_value;
	size_t	old_len;

	(*i)++;
	start = *i;
	if (input[start] == '?')
	{
	char	*str_value = ft_itoa(state->exit_status);

		if (!str_value)
			return ;
		old_len = ft_strlen(state->result);
		state->result = realloc(state->result, old_len + ft_strlen(str_value) + 1);
		if (!state->result)
			return ;
		ft_strcat(state->result, str_value);
		free(str_value);
		return ;
	}
	
	while (input[*i] && (isalnum((unsigned char)input[*i]) || input[*i] == '_'))
		(*i)++;

	var_name = strndup(input + start, *i - start);
	if (!var_name)
		return ;

	var_value = get_env_value(env_list, var_name);
	free(var_name);

	if (var_value)
	{
		old_len = ft_strlen(state->result);
		state->result = realloc(state->result, old_len + ft_strlen(var_value) + 1);
		if (!state->result)
			return ;
		ft_strcat(state->result, var_value);
	}
	
	(*i)--;
}

void	append_char(char **result, char c)
{
	int		len;
	char	*new_result;

	len = ft_strlen(*result);
	new_result = malloc(len + 2);
	if (!new_result)
		return ;
	ft_strcpy(new_result, *result);
	new_result[len] = c;
	new_result[len + 1] = '\0';
	free(*result);
	*result = new_result;
}

char *get_env_value(t_env *env_list, const char *key)
{
    while (env_list)
    {
        if (!strcmp(env_list->key, key))
            return (env_list->content);
        env_list = env_list->next;
    }
    return (NULL);
}


void expand_test(t_minishell *minishell)
{
    t_command *cmd_check;
    int i;

    printf("----- DEBUG AFTER EXPAND -----\n");
    cmd_check = minishell->command;

    while (cmd_check)
    {
        printf("Commande:\n");
        i = 0;
        while (cmd_check->args && cmd_check->args[i])
        {
            printf("Arg[%d] = '%s'\n", i, cmd_check->args[i]);
            i++;
        }
        cmd_check = cmd_check->next;
    }
    printf("--------------------------------\n");
}
