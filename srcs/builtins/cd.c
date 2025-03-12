/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:24 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 11:43:29 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	update_env(char *dir, char *cwd, t_map *env)
{
	t_map	*pwd;
	t_map	*oldpwd;

	pwd = get_env(env, "PWD", 3);
	if (!pwd)
	{
		pwd = add_env_var(env, "PWD", cwd);
		if (!pwd)
			return (false);
	}
	oldpwd = get_env(env, "OLDPWD", 6);
	if (!oldpwd)
	{
		oldpwd = add_env_var(env, "OLDPWD", NULL);
		if (!oldpwd)
			return (false);
	}
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = cwd;
	return (true);
}

int	cd(t_map *env, char *dir)
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
	if (update_env(dir, cwd, env) == false)
		return (1);
	return (0);
}
