/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/02/27 13:52:11 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_mini		minishell;
	t_history	history;
	char	*input;

	if (!create_env(&minishell))
		return (EXIT_FAILURE);
	create_signals();
	minishell.history = &history;
	if (!init_history(minishell.history))
		return (ft_mapclear(&minishell.env), EXIT_FAILURE);
	while (1)
	{
		input = read_line("minishell$> ", minishell.history);
		if (!input)
			break ;
		ft_printf("%s\n", input);
		// send the line to the lexer
		free(input);
	}
	int	i = 0;
	while (history.history[i])
		printf("%d: %s\n", i, history.history[i++]);
	exit2(&minishell, 1);
	return (EXIT_SUCCESS);
}
