/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:24 by agruet            #+#    #+#             */
/*   Updated: 2025/03/13 12:40:27 by agruet           ###   ########.fr       */
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

static int	go_home(t_map *env)
{
	t_map	*find;

	find = get_env(env, "HOME", 5);
	if (!find->value)
		return (ft_fprintf(2, "cd: HOME not set\n"), 0);
	if (chdir(find->value))
		return (perror(find->value), 1);
	return (0);
}

int	cd(t_map *env, char **args)
{
	char	*cwd;
	char	*dir;

	if (args && args[1])
	{
		ft_fprintf(2, "cd: too many arguments\n");
		return (1);
	}
	dir = args[0];
	cwd = getcwd(NULL, 0);
	if (!dir || !cwd)
	{
		if (cwd)
			free(cwd);
		if (!go_home(env))
			return (1);
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
