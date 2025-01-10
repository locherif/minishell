/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:52:33 by braugust          #+#    #+#             */
/*   Updated: 2025/01/10 13:01:07 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_var_command(t_command *command, int exit_status, char **env)
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
                    handle_quotes(input[j], &state);
                else if (input[j] == '$' && state.in_quote != 2)
                    handle_expansion(&state, input, &j, env);
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
                    handle_expansion(&state, input, &j, env);
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

void	handle_expansion(t_expand_state *state, const char *input, int *i, char **env)
{
	int		start;
	int		j;
	char	*var_name;
	char	*var_value;

	(*i)++;
	start = *i;
	j = 0;
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
