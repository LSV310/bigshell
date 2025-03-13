/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:49:49 by agruet            #+#    #+#             */
/*   Updated: 2025/03/13 12:40:35 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_num(char *nbr)
{
	if (*nbr == '-' || *nbr == '+')
		nbr++;
	while (*nbr && ft_isdigit(*nbr))
		nbr++;
	if (*nbr)
		return (false);
	return (true);
}

static bool	numeric_arg(char *nbr)
{
	char	*limit;

	while (*nbr == 32 || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (is_num(nbr) == false)
		return (false);
	if (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			limit = ft_ltoa(LONG_MIN);
		else
			limit = ft_ltoa(LONG_MAX);
	}
	if (!limit)
		return (false);
	if (ft_strcmp(nbr, limit) <= 0)
		return (free(limit), true);
	else
		return (free(limit), false);
}

int	exit2(t_shell *minishell, int int_code, char **args)
{
	int	code;

	if (args && args[0] && args[1])
		return (ft_fprintf(2, "exit: too many arguments\n"), 1);
	if (args && args[0])
	{
		if (numeric_arg(args[0]) == false)
		{
			ft_fprintf(2, "exit: %s numeric argument required\n", args[0]);
			code = 2;
		}
		else
			code = ft_atol(args[0]);
	}
	else
		code = int_code;
	ft_mapclear(&minishell->env);
	ft_dlstclear(&minishell->history, &free_content);
	ft_printf("exit\n");
	exit(code);
}
