/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:21:42 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 14:33:52 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_reading(t_mini *minishell)
{
	char		*input;
	// t_lexer		lex;

	(void)minishell;
	while (1)
	{
		input = readline("minishell$> ");
		if (input == NULL)
			break ;
		if (*input)
		{
			ft_printf("%s\n", input);
			add_history(input);
		}
		// lex = init_lexer(input);
		free(input);
	}
}
