/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:44:29 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 17:53:33 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_mini	minishell;

	if (!create_env(&minishell))
		return (EXIT_FAILURE);
	create_signals();
	if (start_reading(&minishell))
	{
		ft_mapclear(&minishell.env);
		return (EXIT_FAILURE);
	}
	ft_mapclear(&minishell.env);
	return (EXIT_SUCCESS);
}
