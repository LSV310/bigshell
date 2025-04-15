/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:38:11 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 14:51:27 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle(int sig)
{
	if (sig == SIGQUIT)
		ft_printf("Quit (core dumped)");
	ft_printf("\n");
	return ;
}

void	set_signals(void)
{
	signal(SIGINT, &handle);
	signal(SIGQUIT, &handle);
	signal(SIGPIPE, SIG_IGN);
}

void	child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
