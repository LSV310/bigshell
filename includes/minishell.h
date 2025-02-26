/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 18:26:44 by agruet           ###   ########.fr       */
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
# include <termios.h>
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
char	*get_env_variable(char *key, void *env);

// env
int		create_env(t_mini *minishell);
int		assign_kv(char *var, t_map *map);
t_map	*get_env(t_mini *minishell, char *var, size_t len);

// readline
int		start_reading(t_mini *minishell);
int		read_key(void);
void	set_raw_mode(void);
void	reset_terminal_mode(void);

// signals
void	create_signals(void);

// builtins
int		echo(char **args, int param);
int		env(t_mini *minishell);
int		exit2(t_mini *minishell, int exit_code);
int		export(t_mini *minishell, char *var);
int		pwd(void);
int		unset(t_mini *minishell, char *var);

#endif
