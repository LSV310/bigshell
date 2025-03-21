/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:22:20 by agruet            #+#    #+#             */
/*   Updated: 2025/03/21 13:46:32 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*new_cmd(char *old_cmd)
{
	char	*new_cmd;

	if (!old_cmd)
		return (NULL);
	new_cmd = ft_strjoin("/", old_cmd);
	if (!new_cmd)
		return (NULL);
	return (new_cmd);
}

static char	*find_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
			return (path + 5);
		i++;
	}
	return (NULL);
}

static char	*try_path(char *cmd, char **path, int i)
{
	char	*join;

	if (!cmd)
		return (NULL);
	join = ft_strjoin(path[i], cmd);
	if (!join)
		return (NULL);
	if (!access(join, F_OK | X_OK))
		return (join);
	free(join);
	return (NULL);
}

char	*search_path(char *cmd, char **env)
{
	char	**path;
	char	*temp;
	int		i;

	cmd = new_cmd(cmd);
	if (!cmd)
		return (NULL);
	temp = find_path(env);
	if (!temp)
		return (free(cmd), NULL);
	path = ft_split(temp, ':');
	if (!path)
		return (free(cmd), NULL);
	temp = NULL;
	i = 0;
	while (path[i])
	{
		temp = try_path(cmd, path, i);
		if (temp)
			break ;
		i++;
	}
	return (free(cmd), free_tab(path, 0), temp);
}

char	*search_cmd(char *cmd, char **env)
{
	char	*in_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK))
		{
			perror(cmd);
			return (NULL);
		}
		return (cmd);
	}
	in_path = search_path(cmd, env);
	if (!in_path)
		ft_fprintf(2, "%s: command not found\n", cmd);
	return (in_path);
}
