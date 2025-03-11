/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:17:55 by agruet            #+#    #+#             */
/*   Updated: 2025/03/11 17:12:30 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	create_new_var(t_mini *minishell, char *var)
{
	t_map	*new;

	new = newmap(NULL, NULL);
	if (!new)
		return (0);
	if (!assign_kv(var, new))
		return (free(new), 0);
	ft_addmap(&minishell->env, new);
	return (1);
}

static int	replace_var(t_map *find, char *var, char *chr)
{
	free(find->value);
	find->value = ft_substr(var, chr - var + 1, ft_strlen(var));
	if (!find->value)
		return (0);
	return (1);
}

int	export(t_mini *minishell, char *var)
{
	t_map	*find;
	char	*chr;

	if (!var)
		return (env(minishell));
	chr = ft_strchr(var, '=');
	if (!chr)
		return (1);
	find = get_env(minishell, var, chr - var);
	if (!find && !create_new_var(minishell, var))
		return (1);
	else if (!replace_var(find, var, chr))
		return (1);
	return (0);
}
