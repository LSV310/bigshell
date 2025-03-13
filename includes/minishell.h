/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/03/13 11:12:37 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "arena.h"
# include "lexer.h"
# include "parser.h"
# include "pipex.h"
# include "wildcards.h"
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>

typedef struct s_shell
{
	t_map	*env;
	t_dlist	*history;
}	t_shell;

// builtins
int		cd(t_map *env, char **args);
int		echo(char **args);
int		env2(t_map *env);
int		exit2(t_shell *minishell, int int_code, char *char_code);
int		export(t_map *env, char **args);
int		pwd(void);
int		unset(t_map *env, char **args);

// env
int		create_env(t_shell *minishell);
int		assign_kv(char *var, t_map *map);
t_map	*get_env(t_map *env, const char *var, size_t len);
t_map	*add_env_var(t_map *env, char *key, char *value);
char	**convert_env(t_map *map);

// lexer
int		expend_token(t_token *tok, t_arena *arena, t_shell *env);
t_list	*make_tokens(const char	*line_read, t_arena *arena, t_shell *env);
int		expend_token_list(t_list *tks, t_arena *arena, t_shell *env);

// pipex
int		pipex(t_list **tks, t_shell *shell);
int		try_builtins(t_cmd *cmd, t_shell *shell);

// signals
void	create_signals(void);

#endif
