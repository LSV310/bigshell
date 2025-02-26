/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 15:57:32 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "arena.h"
# include "lexer.h"
# include "pipex.h"
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_kv
{
	char	*key;
	char	*value;
}	t_kv;

typedef struct s_mini
{
	t_map	*env;
}	t_mini;

// tristan
int		ft_isspace(char c);
int		char_in_set(char c, const char *set);
char	*get_env_variable(const char *key, size_t n, void *env);

// env
int		create_env(t_mini *minishell);
int		assign_kv(char *var, t_map *map);

// readline
void	start_reading(t_mini *minishell);

// signals
void	create_signals(void);

// builtins
int		echo(char **args, int param);
int		env(t_mini *minishell);
int		exit2(t_mini *minishell, int exit_code);
int		export(t_mini *minishell, char *var);
int		pwd(void);
int		unset(t_mini *minishell, char *var);

// utils
t_map	*get_env(t_mini *minishell, char *var);

#endif
