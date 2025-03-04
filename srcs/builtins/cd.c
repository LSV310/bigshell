/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:24 by agruet            #+#    #+#             */
/*   Updated: 2025/03/04 14:47:57 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env(char *dir, t_mini *minishell)
{
	t_map	*pwd;
	t_map	*oldpwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	pwd = get_env(minishell, "PWD", 3);
	oldpwd = get_env(minishell, "OLDPWD", 6);
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = cwd;
	return (1);
}

int	cd(char *dir, t_mini *minishell)
{
	if (chdir(dir))
		return (perror(dir), 1);
	if (!update_env(dir, minishell))
		return (1);
	return (0);
}
