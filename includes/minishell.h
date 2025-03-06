/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/03/06 19:32:49 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "arena.h"
# include "lexer.h"
# include "parser.h"
# include "pipex.h"
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>

typedef struct s_kv
{
	char	*key;
	char	*value;
}	t_kv;

typedef struct s_mini
{
	t_map	*env;
	t_dlist	*history;
}	t_mini;

// tristan
int		ft_isspace(char c);
int		char_in_set(char c, const char *set);
char	*get_env_variable(const char *key, size_t n, void *env);
int		expend_token(t_token *tok, t_arena *arena, t_mini *env);
t_list	*make_tokens(const char	*line_read, t_arena *arena, t_mini *env);
int		expend_token_list(t_list *tks, t_arena *arena, t_mini *env);
int		is_cmd_token(t_token *tok);
t_cmd	*parse_cmd(t_list **tks, t_arena *arena);

// env
int		create_env(t_mini *minishell);
int		assign_kv(char *var, t_map *map);
t_map	*get_env(t_mini *minishell, const char *var, size_t len);

// signals
void	create_signals(void);

// builtins
int		cd(char *dir, t_mini *minishell);
int		echo(char **args, int param);
int		env(t_mini *minishell);
int		exit2(t_mini *minishell, int exit_code);
int		export(t_mini *minishell, char *var);
int		pwd(void);
int		unset(t_mini *minishell, char *var);

#endif
