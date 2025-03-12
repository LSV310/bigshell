/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:31 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 11:15:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	unset(t_map *env, char *var)
{
	t_map	*find;

	find = get_env(env->next, var, ft_strlen(var));
	if (!find)
		return (0);
	map_remove_node(&env, find);
	return (0);
}
