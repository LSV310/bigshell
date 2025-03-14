/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/03/14 13:23:07 by agruet           ###   ########.fr       */
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
# include <signal.h>

typedef struct s_shell
{
	t_map	*env;
	t_dlist	*history;
	t_arena	*arena;
}	t_shell;

//idk
int		expend_token_list(t_list *tks, t_arena *arena, t_shell *env);
int		is_cmd_token(t_token *tok);
t_cmd	*parse_cmd(t_list *tks);
char	*env_exp(char *src, t_shell *env);

// builtins
int		cd(t_map *env, char **args);
int		echo(char **args);
int		env2(t_map *env, char **args);
int		exit2(t_shell *minishell, int int_code, char **args);
int		export(t_map *env, char **args);
int		pwd(char **args);
int		unset(t_map *env, char **args);

// env
int		create_env(t_shell *minishell);
int		assign_kv(char *var, t_map *map);
t_map	*get_env(t_map *env, const char *var, size_t len);
t_map	*add_env_var(t_map *env, char *key, char *value);
char	**convert_env(t_map *map);
char	*get_env_value(t_map *env, const char *var, size_t len);

// lexer
int		expend_token(t_token *tok, t_arena *arena, t_shell *env);
t_list	*make_tokens(const char	*line_read, t_arena *arena, t_shell *env);
int		expend_token_list(t_list *tks, t_arena *arena, t_shell *env);

// pipex
int		pipex(t_list **tks, t_shell *shell);
int		try_builtins(t_cmd *cmd, t_shell *shell);

// signals
void	create_signals(void);
void	restore_signals(void);

// utils
int		check_first_arg(t_map *env, char **args, int *exit_code);
bool	var_name_valid(char *var);

#endif
