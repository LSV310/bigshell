/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:24 by agruet            #+#    #+#             */
/*   Updated: 2025/03/07 11:49:02 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	update_env(char *dir, char *cwd, t_mini *minishell)
{
	t_map	*pwd;
	t_map	*oldpwd;

	pwd = get_env(minishell, "PWD", 3);
	oldpwd = get_env(minishell, "OLDPWD", 6);
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = cwd;
	return (true);
}

int	cd(char *dir, t_mini *minishell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!dir || !cwd)
	{
		if (cwd)
			free(cwd);
		if (chdir("~"))
			return (perror(dir), errno);
	}
	else
	{
		if (chdir(dir))
			return (free(cwd), perror(dir), errno);
	}
	if (update_env(dir, cwd, minishell) == false)
		return (1);
	return (0);
}
