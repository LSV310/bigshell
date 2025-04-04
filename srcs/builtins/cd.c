/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:24 by agruet            #+#    #+#             */
/*   Updated: 2025/04/04 13:35:22 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_env(t_map *env)
{
	t_map	*pwd;
	t_map	*oldpwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	pwd = get_env(env, "PWD", 3);
	if (!pwd)
	{
		pwd = add_env_var(env, "PWD", cwd);
		if (!pwd)
			return (free(cwd), 1);
	}
	oldpwd = get_env(env, "OLDPWD", 6);
	if (!oldpwd)
	{
		oldpwd = add_env_var(env, "OLDPWD", NULL);
		if (!oldpwd)
			return (free(cwd), 1);
	}
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = cwd;
	return (0);
}

static int	go_home(t_map *env, bool force)
{
	t_map	*find;

	find = get_env(env, "HOME", 4);
	if (!find && force == true)
	{
		chdir("/");
		update_env(env);
		return (1);
	}
	if (!find)
		return (ft_fprintf(2, "cd: HOME not set\n"), 1);
	if (chdir(find->value))
		return (write(2, "cd: ", 4), perror(find->value), 1);
	return (update_env(env));
}

static int	check_args(char **args)
{
	if (args && args[0])
	{
		if (args[0][0] == '-')
		{
			ft_fprintf(2, "cd: -%c: invalid option\n", args[0][1]);
			return (2);
		}
	}
	if (args && args[0] && args[1])
		return (ft_fprintf(2, "cd: too many arguments\n"), 1);
	return (0);
}

int	cd(t_map *env, char **args)
{
	char	*cwd;
	char	*dir;
	int		valid_args;

	valid_args = check_args(args);
	if (valid_args)
		return (valid_args);
	dir = args[0];
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_fprintf(2, "cd: error retrieving current directory\n");
		if (!go_home(env, true))
			return (1);
	}
	free(cwd);
	if (!dir)
		return (go_home(env, false));
	if (chdir(dir))
		return (write(2, "cd: ", 4), perror(dir), 1);
	return (update_env(env));
}
