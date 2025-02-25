/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:38:11 by agruet            #+#    #+#             */
/*   Updated: 2025/02/25 12:56:22 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signals(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
		ft_printf("\n----------\nCTRL+C\n----------\n");
	else if (sig == SIGQUIT)
		ft_printf("\n----------\nCTRL+\\\n----------\n");
	(void)info;
	(void)context;
	return ;
}

void	siginit(struct sigaction *sa, void (*action)(int, siginfo_t *, void *))
{
	sigemptyset(&sa->sa_mask);
	sa->sa_handler = NULL;
	sa->sa_sigaction = action;
	sa->sa_flags = SA_SIGINFO;
}

void	create_signals(t_mini *minishell)
{
	struct sigaction	sa;

	(void)minishell;
	siginit(&sa, handle_signals);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
