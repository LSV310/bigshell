/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:36:40 by agruet            #+#    #+#             */
/*   Updated: 2025/03/21 13:46:32 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(char **args)
{
	char	*cwd;

	if (args && args[0])
	{
		if (args[0][0] == '-')
		{
			ft_fprintf(2, "pwd: -%c: invalid option\n", args[0][1]);
			return (2);
		}
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cwd"), 1);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
