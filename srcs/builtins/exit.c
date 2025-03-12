/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:49:49 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 16:11:06 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	long_overflow(char *nbr)
{
	char	*limit;

	while (*nbr == 32 || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			limit = ft_ltoa(LONG_MIN);
		else
			limit = ft_ltoa(LONG_MAX);
	}
	if (!limit)
		return (false);
	if (ft_strcmp(limit, nbr) <= 0)
		return (free(limit), false);
	else
		return (free(limit), true);
}

int	exit2(t_shell *minishell, int int_code, char *char_code)
{
	int	code;

	if (char_code)
	{
		if (long_overflow(char_code) == true)
		{
			ft_fprintf(2, "exit: %s numeric argument required\n", char_code);
			code = 2;
		}
		else
			code = ft_atol(char_code);
	}
	else
		code = int_code;
	ft_mapclear(&minishell->env);
	ft_dlstclear(&minishell->history, &free_content);
	arena_free(minishell->arena);
	ft_printf("exit\n");
	exit(code);
}
