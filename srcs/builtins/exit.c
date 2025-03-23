/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:49:49 by agruet            #+#    #+#             */
/*   Updated: 2025/03/21 13:40:43 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*nb_start(char *nbr)
{
	int		i;
	bool	sign;

	i = 0;
	sign = false;
	while (*nbr == 32 || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (nbr[0] == '-' || nbr[0] == '+')
	{
		i++;
		sign = true;
	}
	while (ft_isdigit(nbr[i]))
		i++;
	if ((i >= 20 && !sign) || (i >= 21 && sign))
		return (NULL);
	while (nbr[i] == 32 || (nbr[i] >= 9 && nbr[i] <= 13))
		i++;
	if (nbr[i] != 0 || (i == 0 && !sign) || (i == 1 && sign))
		return (NULL);
	if (*nbr == '+')
		nbr++;
	return (nbr);
}

static bool	numeric_arg(char *nbr)
{
	char	*limit;
	int		len;
	int		i;

	nbr = nb_start(nbr);
	if (!nbr)
		return (false);
	i = 0;
	while (ft_isdigit(nbr[i]) ||  nbr[i] == '-')
		i++;
	if ((i < 20 && *nbr == '-') || (i < 19 && ft_isdigit(*nbr)))
		return (true);
	len = 19;
	if (*nbr == '-')
	{
		len = 20;
		limit = ft_ltoa(LONG_MIN);
	}
	else
		limit = ft_ltoa(LONG_MAX);
	if (!limit)
		return (false);
	if (ft_strncmp(nbr, limit, len) <= 0)
		return (free(limit), true);
	else
		return (free(limit), false);
}

void	free_minishell(t_shell *minishell)
{
	if (minishell->env)
		ft_mapclear(&minishell->env);
	if (minishell->history)
		ft_dlstclear(&minishell->history, &free_content);
	if (minishell->arena)
	{
		arena_regions_free(minishell->arena);
		free(minishell->arena);
	}
	if (minishell->input)
		free(minishell->input);
	if (minishell->std_in != -1)
	{
		close(minishell->std_in);
		minishell->std_in = -1;
	}
}

int	exit2(t_shell *minishell, int int_code, char **args)
{
	int	code;

	if (args && args[0])
	{
		if (numeric_arg(args[0]) == false)
		{
			ft_fprintf(2, "exit: '%s': numeric argument required\n", args[0]);
			code = 2;
		}
		else
		{
			if (args[1])
				return (ft_fprintf(2, "exit: too many arguments\n"), 1);
			code = ft_atol(args[0]);
		}
	}
	else
		code = int_code;
	if (args)
		ft_printf("exit\n");
	free_minishell(minishell);
	exit(code);
}
