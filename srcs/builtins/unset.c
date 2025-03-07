/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:31 by agruet            #+#    #+#             */
/*   Updated: 2025/03/07 11:49:02 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	unset(t_mini *minishell, char *var)
{
	t_map	*find;

	find = get_env(minishell, var, ft_strlen(var));
	if (!find)
		return (1);
	map_remove_node(&minishell->env, find);
	return (0);
}
