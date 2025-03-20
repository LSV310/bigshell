/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:24 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 16:14:40 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	update_env(char *cwd, t_map *env)
{
	t_map	*pwd;
	t_map	*oldpwd;

	pwd = get_env(env, "PWD", 3);
	if (!pwd)
	{
		pwd = add_env_var(env, "PWD", cwd);
		if (!pwd)
			return (1);
	}
	oldpwd = get_env(env, "OLDPWD", 6);
	if (!oldpwd)
	{
		oldpwd = add_env_var(env, "OLDPWD", NULL);
		if (!oldpwd)
			return (1);
	}
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = cwd;
	return (0);
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
		return (ft_fprintf(2, "cd: too many arguments\n"), 1);
	dir = args[0];
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		if (!chdir("~"))
			return (1);
	}
	if (!dir && !go_home(env))
		return (1);
	else
	{
		if (chdir(dir))
			return (free(cwd), perror(dir), errno);
	}
	return (update_env(cwd, env));
}
