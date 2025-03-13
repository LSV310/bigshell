/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/03/13 14:13:40 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	t_shell	minishell;
	char	*input;

	minishell.history = NULL;
	if (!create_env(&minishell))
		return (EXIT_FAILURE);
	create_signals();
	while (1)
	{
		input = ft_readline("minishell$> ", &minishell.history);
		if (!input)
			break ;
		char *wildcard = get_wildcards(input, BOTH, false);
		ft_printf("%s\n", wildcard);
		free(wildcard);
		free(input);
		if (!isatty(STDIN_FILENO))
			break ;
	}
	exit2(&minishell, 0, NULL);
	return (EXIT_SUCCESS);
}
