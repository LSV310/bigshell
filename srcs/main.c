/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/03/23 13:47:44 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	exec_input(char *input, t_shell *shell)
{
	t_list	*tks;
	t_ast	*ast;

	tks = make_tokens(input, shell);
	if (!tks)
		return (false);
	ast = build_ast(tks, shell->arena);
	if (!ast)
		return (false);
	if (!exec_ast(ast, shell))
		return (false);
	return (true);
}

int	init_minishell(t_shell *minishell)
{
	minishell->arena = NULL;
	minishell->history = NULL;
	minishell->arena = NULL;
	minishell->input = NULL;
	minishell->std_in = -1;
	if (!create_env(minishell))
		return (EXIT_FAILURE);
	minishell->arena = arena_init();
	if (!minishell->arena)
		exit2(minishell, 1, NULL);
	create_signals();
	return (1);
}

int	main(void)
{
	t_shell	minishell;

	init_minishell(&minishell);
	while (1)
	{
		minishell.input = ft_readline("minishell$> ", &minishell.history, true);
		if (!minishell.input)
			break ;
		exec_input(minishell.input, &minishell);
		reset_arena(&minishell.arena);
		free(minishell.input);
		minishell.input = NULL;
	}
	exit2(&minishell, 0, NULL);
	return (EXIT_SUCCESS);
}
