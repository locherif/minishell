/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:52:33 by braugust          #+#    #+#             */
/*   Updated: 2025/01/07 15:58:24 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void expand_command(t_command *command, int exit_status, char **env)
{
    int i;

    while (command)
    {
        i = 0;
        while (command->args && command->args[i])
        {
            char *expanded = strdup("");
            t_expand_state state = {expanded, 0, exit_status};
            expand_var(command->args[i], &state, env);
            free(command->args[i]);
            command->args[i] = state.result;
            i++;
        }
		
        i = 0;
        while (i < command->redir_size)
        {
            char *expanded = strdup("");
            t_expand_state state = {expanded, 0, exit_status};
            expand_var(command->redirs[i].file, &state, env);
            free(command->redirs[i].file);
            command->redirs[i].file = state.result;
            i++;
        }

        command = command->next;
    }
}

void expand_var(const char *input, t_expand_state *state, char **env)
{
    int i = 0;

    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '\"')
            handle_quotes(input[i], state);
        else if (input[i] == '$' && state->in_quote != 2)
            handle_expansion(state, input, &i, env);
        else
            append_char(&state->result, input[i]);
        i++;
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

void	handle_expansion(t_expand_state *state, const char *input, int *i, char **env)
{
	int		start;
	int		j;
	char	*var_name;
	char	*var_value;

	j = 0;
	(*i)++;
	start = *i;
	if (input[start] == '?')
	{
		var_value = malloc(12);
		if (!var_value)
			return ;
		snprintf(var_value, 12, "%d", state->exit_status);
		state->result = strncat(state->result, var_value, strlen(var_value));
		free(var_value);
		return ;
	}
	while (input[*i] && (isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	var_name = strndup(input + start, *i - start);
	var_value = NULL;
	while (env[j])
	{
		if (!strncmp(env[j], var_name, strlen(var_name)) && env[j][strlen(var_name)] == '=')
		{
			var_value = env[j] + strlen(var_name) + 1;
			break ;
		}
		j++;
	}
	free(var_name);
	if (var_value)
		state->result = strncat(state->result, var_value, strlen(var_value));
	(*i)--;
}

void	append_char(char **result, char c)
{
	int		len;
	char	*new_result;

	len = strlen(*result);
	new_result = malloc(len + 2);
	if (!new_result)
		return ;
	strcpy(new_result, *result);
	new_result[len] = c;
	new_result[len + 1] = '\0';
	free(*result);
	*result = new_result;
}