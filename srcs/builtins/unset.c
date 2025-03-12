/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:31 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 16:45:23 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	unset(t_map *env, char **args)
{
	t_map	*find;
	int		i;

	i = 0;
	while (args[i])
	{
		find = get_env(env->next, args[i], ft_strlen(args[i]));
		if (find)
			map_remove_node(&env, find);
		i++;
	}
	return (0);
}
