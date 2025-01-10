/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:25:58 by braugust          #+#    #+#             */
/*   Updated: 2025/01/10 12:50:30 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *new_env_node(char *key, char *content)
{
    t_env   *node;
    
    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->key = key;
    node->content = content;
    node->next = NULL;
    return (node);
}

t_env   *init_env_list(char **envp)
{
    t_env   *head;
    t_env   *current;
    char    *key;
    char    *content;
    int     i;
    int     separator;

    head = NULL;
    i = 0;
    while (envp[i])
    {
        separator = 0;
        while (envp[i][separator] && envp[i][separator] != '=')
            separator++;
        key = strdup(envp[i]);
        if (!key)
            return (NULL);
        key[separator] = '\0';
        content = strdup(envp[i] + separator + 1);
        if (!content)
        {
            free(key);
            return (NULL);
        }
        if (!head)
        {
            head = new_env_node(key, content);
            current = head;
        }
        else
        {
            current->next = new_env_node(key, content);
            current = current->next;
        }
        i++;
    }
    return (head);
}

void    print_env_list(t_env *env)
{
    while (env)
    {
        printf("Key: %s, Content: %s\n", env->key, env->content);
        env = env->next;
    }
}

void    free_env_list(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->key);
        free(env->content);
        free(env);
        env = tmp;
    }
}

t_env   *find_env(t_env *env, const char *key)
{
    while (env)
    {
        if (!strcmp(env->key, key))
            return (env);
        env = env->next;
    }
    return (NULL);
}

int update_env(t_env *env, const char *key, const char *new_content)
{
    t_env *node = find_env(env, key);

    if (!node)
        return (0);
    free(node->content);
    node->content = strdup(new_content);
    if (!node->content)
        return (0);
    return (1);
}
