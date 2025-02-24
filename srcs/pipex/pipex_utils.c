/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:33:18 by agruet            #+#    #+#             */
/*   Updated: 2025/02/24 15:59:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(char *cmd, char **args)
{
	int	i;

	i = 0;
	if (cmd)
		free(cmd);
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	if (fd3 >= 0)
		close(fd3);
	if (fd4 >= 0)
		close(fd4);
}
