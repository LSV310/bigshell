/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/03/21 13:27:31 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	proute(char *input, t_shell *shell)
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

int	main(void)
{
	t_shell	minishell;
	char	*input;

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
		free(input);
	}
	exit2(&minishell, 0, NULL);
	return (EXIT_SUCCESS);
}
