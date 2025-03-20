/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:38:11 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 12:54:06 by agruet           ###   ########.fr       */
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

void	rl_init_signals(void)
{
	struct sigaction	sa;

	init_sigaction(&sa, handle_signals);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	rl_reset_signals(void)
{
	struct sigaction	sa;

	init_sighandler(&sa, SIG_DFL);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	rl_signal_received(t_readline *line, t_dlist **history, char *prompt)
{
	bool	sigint_nl;

	if (g_sig != SIGINT)
		return (1);
	sigint_nl = line->sigint_nl;
	clear_line(line, history, 1);
	if (line->sigint_nl == false)
	{
		ft_printf("\n");
		return (0);
	}
	if (!new_buffer(line, history, sigint_nl))
		return (0);
	ft_fprintf(0, "\n%s", prompt);
	return (1);
}
