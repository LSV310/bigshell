/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:25:51 by agruet            #+#    #+#             */
/*   Updated: 2025/02/19 15:49:35 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args, int param)
{
	int	i;

	i = 1;
	if (!args)
		return (0);
	while (args[i] && args[i + 1])
		ft_printf("%s ", args[i++]);
	if (args[i])
		ft_printf("%s", args[i]);
	if (!param)
		ft_printf("\n");
	return (0);
}
