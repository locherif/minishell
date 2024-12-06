/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locherif <locherif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:06:15 by locherif          #+#    #+#             */
/*   Updated: 2024/12/04 18:54:41 by locherif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR,
}						t_token_type;

typedef struct s_token
{
	char				*content;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef enum e_redir_type
{
	IN,
	OUT,
	HEREDOC,
	APPEND,
}						t_redir_type;

typedef struct s_redir
{
	char				*file;
	t_redir_type		type;
	// struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**args;
	int					redir_size;
	t_redir				*redirs;
	struct s_command	*next;
}						t_command;

typedef struct s_minishell
{
	t_token				*token;
	t_command			*command;
}						t_minishell;

void					printtoken(t_token *tok);
int						get_tokens(t_minishell *mini, char *prompt);
int						get_pipe(t_minishell *mini, int *i);
int						get_redir_double(t_minishell *mini, char *prompt,
							int *i);
int						get_redir_simple(t_minishell *mini, char *prompt,
							int *i);
int						get_word(char *prompt, t_minishell *mini, int *i);
void					add_token_back(t_token **token_list,
							t_token *new_element);
t_token					*last_token(t_token *token);
void					clear_token(t_token *token);
t_token					*new_token(char *str, t_token_type type);
char					*ft_substr(char *s, unsigned int start, int len);
int						ft_strlen(char *str);
int						ft_strncmp(char *s1, char *s2, int n);
int						get_len_word(char *prompt, int i);
int						is_not_word(char c);
int						is_space(char c);
void					add_between_quotes(char *str, char *input, int *j,
							int *i);
int						syntax_analysis(t_token *token);
int						word_status(t_token *token);
int						pipe_status(t_token *token);
int						redir_status(t_token *token);
int						start_status(t_token *token);
int						ranger(t_token *token, t_minishell *minishell);

void					*ft_calloc(size_t nmemb, size_t size);
t_command				*new_command(char **args, t_redir *redirs);
void					add_command_back(t_command **command_list,
							t_command *new_element);
void					clear_command(t_command *command);
void					add_word(char **args, char *current_arg);
int						eclaireur(t_token *token, t_token_type type);

#endif