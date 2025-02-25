/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:51:52 by agruet            #+#    #+#             */
/*   Updated: 2025/02/25 12:34:46 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_mini *minishell, char *var)
{
	t_list *current;
	char	*chr;

	if (ft_strchr(var, '='))
		return (NULL);
	current = minishell->env;
	while (current)
	{
		chr = ft_strchr((char *)current->content, '=');
		if (!ft_strncmp((char *)current->content, var,
			chr - (char *)current->content))
			return (chr + 1);
		current = current->next;
	}
	return (NULL);
}
