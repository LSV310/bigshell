/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:14:51 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 14:29:37 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	auto_complete(int key, t_rline *line)
{
	if (key != '\t' && key != '\n')
	{
		line->in_auto = false;
		return (0);
	}
	if (key == '\n' && line->in_auto == false)
		return (0);

	return (1);
}
