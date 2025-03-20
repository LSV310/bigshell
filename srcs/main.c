/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 17:22:58 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_shell	minishell;
	char	*input;
	t_list	*tks;

	minishell.history = NULL;
	if (!create_env(&minishell))
		return (EXIT_FAILURE);
	minishell.arena = arena_init();
	if (!minishell.arena)
		exit2(&minishell, 1, NULL);
	create_signals();
	while (1)
	{
		input = ft_readline("minishell$> ", &minishell.history, true);
		if (!input)
			break ;
		tks = make_tokens(input, &minishell);
		pipex(ptr_arr_pipeline(tks, minishell.arena), &minishell);
		free(input);
	}
	exit2(&minishell, 0, NULL);
	return (EXIT_SUCCESS);
}
