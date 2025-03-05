/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/03/05 18:25:07 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_mini	minishell;
	char	*input;

	minishell.history = NULL;
	if (!create_env(&minishell))
		return (EXIT_FAILURE);
	ft_printf("%s\n", get_wildcards("test*"));
	create_signals();
	while (1)
	{
		input = read_line("minishell$> ", &minishell.history);
		if (!input)
			break ;
		make_tokens(input, arena_init(), &minishell);
		free(input);
	}
	exit2(&minishell, 0);
	return (EXIT_SUCCESS);
}
