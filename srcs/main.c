/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 03:15:42 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	exec_input(char *input, t_shell *shell)
{
	t_list	*tks;
	t_ast	*ast;

	tks = make_tokens(input, shell);
	if (!tks)
		return (modify_var(shell->env, "2"), false);
	ast = build_ast(tks, shell);
	if (!ast)
	{
		close_heredocs(tks);
		return (modify_var(shell->env, "2"), false);
	}
	if (!exec_ast(ast, shell))
	{
		close_heredocs(tks);
		return (false);
	}
	close_heredocs(tks);
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

void	get_input(t_shell *minishell)
{
	char	*prompt;

	prompt = get_prompt(minishell->env);
	if (!prompt)
	{
		minishell->input = ft_readline("\e[0;35m$ \e[0m",
				&minishell->history, true);
		return ;
	}
	minishell->input = ft_readline(prompt, &minishell->history, true);
	free(prompt);
}

int	main(void)
{
	t_shell	minishell;

	init_minishell(&minishell);
	while (1)
	{
		get_input(&minishell);
		create_signals();
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
