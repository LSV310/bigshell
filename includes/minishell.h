/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/02/25 12:48:36 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "pipex.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_kv
{
	char	*key;
	char	*value;
}	t_kv;

typedef struct	s_mini
{
	t_list	*env;
}	t_mini;

// tristan
int			ft_isspace(char c);
int			char_in_set(char c, const char *set);
const char	*get_env_variable(char *key, void *env);

// signals
void	create_signals(t_mini *minishell);

// builtins
int		echo(char **args, int param);
int		env(t_mini *minishell);
int		exit2(t_mini *minishell, int exit_code);
int		export(t_mini *minishell, char *var);
int		pwd(void);
int		unset(t_mini *minishell, char *var);

// utils
char	*get_env_var(t_mini *minishell, char *var);

#endif
