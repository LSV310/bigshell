/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/03/03 11:45:24 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_mini	minishell;
	char	*input;

	if (!create_env(&minishell))
		return (EXIT_FAILURE);
	create_signals();
	minishell.history = NULL;
	while (1)
	{
		input = read_line("minishell$> ", &minishell.history);
		if (!input)
			break ;
		// make_tokens(input, arena_init(), &minishell);
		ft_dlst_top(&minishell.history);
		ft_dlstprint(minishell.history);
		free(input);
	}
	exit2(&minishell, 1);
	return (EXIT_SUCCESS);
}
