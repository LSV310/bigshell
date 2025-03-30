/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/03/30 16:41:30 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_minishell(t_shell *minishell)
{
	minishell->arena = NULL;
	minishell->history = NULL;
	minishell->arena = NULL;
	minishell->input = NULL;
	minishell->std_in = -1;
	minishell->std_out = -1;
	if (!create_env(minishell))
		return (EXIT_FAILURE);
	minishell->arena = arena_init();
	if (!minishell->arena)
		exit2(minishell, 1, NULL);
	set_signals();
	return (1);
}

int	get_input(t_shell *minishell, t_readline *params)
{
	char	*prompt;

	prompt = get_prompt(minishell->env);
	params->prompt = prompt;
	if (!prompt)
		params->prompt = "\e[0;35m$ \e[0m";
	minishell->input = ft_readline(params);
	while (params->quit_reason == RL_KILLED && !minishell->input)
	{
		modify_var(minishell->env, "130");
		minishell->input = ft_readline(params);
	}
	if (params->quit_reason == RL_FINISHED && isatty(STDIN_FILENO)
		&& isatty(STDOUT_FILENO))
		ft_printf("exit\n");
	if (prompt)
		free(prompt);
	if (!minishell->input && params->quit_reason == RL_ALLOC_FAILED)
		return (1);
	return (1);
}

bool	exec_input(t_shell *shell)
{
	t_list	*tks;
	t_ast	*ast;

	tks = make_tokens(shell->input, shell);
	if (!tks)
		return (modify_var(shell->env, "2"), false);
	ast = build_ast(tks, shell);
	if (!ast)
	{
		// close_heredocs(tks);
		return (modify_var(shell->env, "2"), false);
	}
	if (!exec_ast(ast, shell))
	{
		// close_heredocs(tks);
		return (false);
	}
	// close_heredocs(tks);
	return (true);
}

int	main(void)
{
	t_shell		minishell;
	t_readline	rl_params;

	init_minishell(&minishell);
	init_readline_params(&rl_params);
	rl_params.history = &minishell.history;
	rl_params.autocomplete = true;
	while (1)
	{
		if (!get_input(&minishell, &rl_params))

		set_signals();
		if (!minishell.input)
			break ;
		exec_input(&minishell);
		reset_arena(&minishell.arena);
		free(minishell.input);
		minishell.input = NULL;
	}
	exit2(&minishell, 0, NULL);
	return (EXIT_SUCCESS);
}
