/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:38:11 by agruet            #+#    #+#             */
/*   Updated: 2025/03/14 13:20:53 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

volatile int	g_sig;

static void	handle_signals(int sig, siginfo_t *info, void *context)
{
	g_sig = sig;
	(void)info;
	(void)context;
	return ;
}

void	rl_init_signals(bool use_sigint)
{
	struct sigaction	sa;

	init_sigaction(&sa, handle_signals);
	if (use_sigint)
		sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	rl_reset_signals(bool use_sigint)
{
	struct sigaction	sa;

	init_sighandler(&sa, SIG_DFL);
	if (use_sigint)
		sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	rl_signal_received(t_readline *line, t_dlist **history, char *prompt)
{
	if (g_sig != SIGINT)
	{
		g_sig = 0;
		return (1);
	}
	clear_line(line, history, 1);
	if (!new_buffer(line, history))
		return (0);
	ft_fprintf(0, "\n%s", prompt);
	return (1);
}
