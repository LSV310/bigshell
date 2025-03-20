/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:31 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 16:14:40 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(t_map *env, char **args)
{
	t_map	*find;
	int		i;

	i = 0;
	if (args[0] && args[0][0] == '-')
		return (ft_fprintf(2, "unset: -%c: invalid option\n", args[0][1]), 2);
	while (args[i])
	{
		find = get_env(env->next, args[i], ft_strlen(args[i]));
		if (find)
			map_remove_node(&env, find);
		i++;
	}
	return (0);
}
