/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/02/25 13:00:36 by agruet           ###   ########.fr       */
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
	while(__environ[i])
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
	create_signals(&minishell);
	export(&minishell, ft_strdup("ARG=salut"));
	ft_printf("%s\n", get_env_var(&minishell, "ARG"));
	ft_printf("> ");
	while (get_next_line(0))
	{
		ft_printf("> ");
	}
	return (EXIT_SUCCESS);
}