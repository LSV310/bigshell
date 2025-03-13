/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:38:11 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 13:34:49 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_signals(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	return ;
}

void	create_signals(void)
{
	struct sigaction	sa;

	siginit(&sa, handle_signals);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
