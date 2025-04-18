/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/04/16 18:44:09 by tgallet          ###   ########.fr       */
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
# include <sys/stat.h>

# define ENVN_STOP "\'\"$?&|<>()# *[]{}\%\n=:/"

typedef struct s_shell
{
	t_map	*env;
	t_dlist	*history;
	t_arena	*arena;
	t_list	*tk_head;
	char	*input;
	int		std_in;
	int		std_out;
}	t_shell;

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
char	*get_env_value(t_map *env, const char *var, size_t len);
int		modify_var(t_map *var, char *value);
char	**convert_env(t_map *map);

// lexer && parsing

int		token_fillstr(t_token *tok, t_arena *arena);
t_list	*make_tokens(const char	*line_read, t_shell *env);
int		tks_fillstr(t_list *tks, t_arena *arena);
int		is_cmd_token(t_token *tok);
char	*env_exp(char *src, t_shell *env);
t_list	*str_to_name_tks(const char *src, t_arena *arena);
void	lst_insert(t_list *dest, t_list *to_insert);
int		expand_lst_token(t_list **tks, t_shell *shell);
bool	expand_namet(t_list **cur, t_list **tks, t_shell *shell);
bool	expand_redt(t_list *cur, t_shell *shell);
t_ast	*parse_expr(t_list **tokens, t_arena *arena);
t_ast	*build_ast(t_list *tks, t_shell *shell);
bool	exec_ast(t_ast *ast, t_shell *shell);
t_token	*advance_token(t_list **tokens);

// pipex
int		pipex(t_list **tks, t_shell *shell);
int		try_builtins(t_cmd *cmd, t_shell *shell, char **env);
t_cmd	*parse_cmd(t_list *tks, t_arena *arena);
t_list	**ptr_arr_pipeline(t_list *tks, t_arena *arena);

// signals
void	set_signals(void);
void	child_signal(void);

// utils
void	free_minishell(t_shell *minishell);
char	*get_prompt(t_map *env);
int		check_first_arg(t_map *env, char **args, int *exit_code);
bool	var_name_valid(char *var, int *index, int *exit_code);
char	*toktype_to_string(t_token_type type);
int		here_doc(char *delimiter, bool expand, t_shell *env);
bool	token_heredoc(t_token *tok, t_shell *shell);
void	close_heredocs(t_list *tks);
bool	tokens_to_pipeline(t_list **tokens, t_ast *node);
bool	valid_pipeline(t_list *tks, bool after_pipe);

#endif
