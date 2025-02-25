/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:21:42 by agruet            #+#    #+#             */
/*   Updated: 2025/02/25 16:03:06 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_reading(t_mini *minishell)
{
	char	*input;

	(void)minishell;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		init_lexer(input);
		free(input);
	}
}
