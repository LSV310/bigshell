/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/02/24 15:59:26 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "pipex.h"
# include "builtins.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

int	ft_isspace(char c);
int	char_in_set(char c, const char *set);

#endif
