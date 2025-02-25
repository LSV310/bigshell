/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/02/25 15:57:59 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_env(t_mini *minishell)
{
	size_t	i;
	t_list	*current;
	t_list	*previous;

	minishell->env = ft_lstnew(ft_strdup(__environ[0]));
	if (!minishell->env)
		return (0);
	i = 1;
	previous = minishell->env;
	while (__environ[i])
	{
		current = ft_lstnew(ft_strdup(__environ[i]));
		if (!current)
			return (ft_lstclear(&minishell->env, &free_content), 0);
		ft_lstadd_back(&previous, current);
		previous = current;
		i++;
	}
	return (1);
}

int	main(void)
{
	t_mini	minishell;

	if (!create_env(&minishell))
		return (EXIT_FAILURE);
	create_signals();
	start_reading(&minishell);
	ft_lstclear(&minishell.env, &free_content);
	return (EXIT_SUCCESS);
}
