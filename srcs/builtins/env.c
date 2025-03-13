/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:53:37 by agruet            #+#    #+#             */
/*   Updated: 2025/03/13 11:43:17 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env2(t_map *env, char **args)
{
	t_map	*current;

	if (!env)
		return (1);
	if (args && args[0])
		return (ft_fprintf(2, "env: too many arguments\n"), 1);
	current = env->next;
	while (current)
	{
		ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
