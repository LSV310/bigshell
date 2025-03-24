/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoarena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:12:55 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/24 00:14:04 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_size(unsigned int n)
{
	unsigned int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*itoarena(int n, t_arena *arena)
{
	char			*str;
	unsigned int	nb;
	int				size;
	int				is_negative;

	nb = n;
	is_negative = 0;
	if (n < 0)
	{
		nb = -n;
		is_negative = 1;
	}
	size = get_size(nb) + is_negative;
	str = arena_alloc(sizeof(char) * (size + 1), arena);
	if (!str)
		return (NULL);
	if (is_negative)
		str[0] = '-';
	str[size] = 0;
	while (--size >= is_negative)
	{
		str[size] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
