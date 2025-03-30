/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:17:31 by agruet            #+#    #+#             */
/*   Updated: 2025/03/30 01:15:35 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_home(char *cwd, t_map *home)
{
	if (access(home->value, F_OK))
		return (NULL);
	if (ft_strncmp(cwd, home->value, ft_strlen(home->value)))
		return (NULL);
	return (ft_substr(cwd, ft_strlen(home->value) + 1, ft_strlen(cwd)));
}

static char	*get_relative_cwd(t_map *env)
{
	char	*cwd;
	char	*relative_cwd;
	char	*join;
	t_map	*home;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	home = get_env(env, "HOME", 4);
	if (!home)
		return (cwd);
	relative_cwd = find_home(cwd, home);
	if (!relative_cwd)
		return (cwd);
	free(cwd);
	if (!relative_cwd[0])
		join = ft_strjoin("~", relative_cwd);
	else
		join = ft_strjoin("~/", relative_cwd);
	if (!join)
		return (relative_cwd);
	free(relative_cwd);
	return (join);
}

char	*get_prompt(t_map *env)
{
	char	*cwd;
	char	*join;
	char	*prompt;

	cwd = get_relative_cwd(env);
	if (!cwd)
		return (NULL);
	join = ft_strjoin("\e[0;35m", cwd);
	free(cwd);
	if (!join)
		return (NULL);
	prompt = ft_strjoin(join, "$ \e[0m");
	free(join);
	if (!prompt)
		return (NULL);
	return (prompt);
}
