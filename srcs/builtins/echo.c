/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:25:51 by agruet            #+#    #+#             */
/*   Updated: 2025/03/26 15:16:44 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_n_arg(char *arg)
{
	int	i;

	i = 1;
	if (!arg[i])
		return (false);
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i])
		return (false);
	return (true);
}

int	echo(char **args)
{
	int		current_arg;
	bool	n_arg;

	if (!args)
		return (0);
	n_arg = false;
	current_arg = 0;
	while (args[current_arg])
	{
		if (args[current_arg][0] != '-')
			break ;
		n_arg = find_n_arg(args[current_arg]);
		if (n_arg == false)
			break ;
		current_arg++;
	}
	if (current_arg != 0)
		n_arg = true;
	while (args[current_arg] && args[current_arg + 1])
		ft_printf("%s ", args[current_arg++]);
	if (args[current_arg])
		ft_printf("%s", args[current_arg]);
	if (!n_arg)
		ft_printf("\n");
	return (0);
}
