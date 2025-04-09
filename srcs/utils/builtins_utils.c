/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:30:39 by agruet            #+#    #+#             */
/*   Updated: 2025/04/09 14:29:26 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_arg(t_map *env, char **args, int *exit_code)
{
	if (!args || !args[0])
	{
		*exit_code = env2(env, NULL);
		return (0);
	}
	if (args[0][0] == '-')
	{
		ft_fprintf(2, "export: -%c: invalid option\n", args[0][1]);
		*exit_code = 2;
		return (0);
	}
	return (1);
}

bool	var_name_valid(char *var, int *index, int *exit_code)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
	{
		(*index)++;
		return (false);
	}
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			*exit_code = 1;
			(*index)++;
			ft_fprintf(2, "export: `%s': not a valid identifier\n", var);
			return (false);
		}
		i++;
	}
	return (true);
}
