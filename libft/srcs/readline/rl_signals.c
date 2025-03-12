/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:38:11 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 13:33:15 by agruet           ###   ########.fr       */
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

void	siginit(struct sigaction *sa, void (*action)(int, siginfo_t *, void *))
{
	sigemptyset(&sa->sa_mask);
	sa->sa_handler = NULL;
	sa->sa_sigaction = action;
	sa->sa_flags = SA_SIGINFO;
}

void	rl_signals(void)
{
	struct sigaction	sa;

	siginit(&sa, handle_signals);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
