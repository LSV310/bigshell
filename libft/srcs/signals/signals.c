/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:49:59 by agruet            #+#    #+#             */
/*   Updated: 2025/03/13 16:49:43 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	siginit(struct sigaction *sa, t_sighandler sighandler,
	void (*action)(int, siginfo_t *, void *))
{
	sigemptyset(&sa->sa_mask);
	if (sighandler == HANDLER)
		sa->sa_handler = action;
	else
		sa->sa_sigaction = action;
	sa->sa_flags = SA_SIGINFO;
}
