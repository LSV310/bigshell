/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_top.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:23:09 by agruet            #+#    #+#             */
/*   Updated: 2025/03/04 14:53:12 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_top(t_dlist **lst)
{
	if (!lst)
		return ;
	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
}
