/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:49:59 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 17:50:23 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	siginit(struct sigaction *sa, void (*action)(int, siginfo_t *, void *))
{
	sigemptyset(&sa->sa_mask);
	sa->sa_handler = NULL;
	sa->sa_sigaction = action;
	sa->sa_flags = SA_SIGINFO;
}
