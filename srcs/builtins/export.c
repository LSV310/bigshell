/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:17:55 by agruet            #+#    #+#             */
/*   Updated: 2025/03/21 13:46:32 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_map	*create_new_var(t_map *env, char *var)
{
	t_map	*new;

	if (var_name_valid(var) == false)
	{
		ft_fprintf(2, "export: %s: not a valid identifier", var);
		return (NULL);
	}
	new = newmap(NULL, NULL);
	if (!new)
		return (NULL);
	if (!assign_kv(var, new))
		return (free(new), NULL);
	ft_addmap(&env, new);
	return (new);
}

static int	replace_var(t_map *find, char *var, char *chr)
{
	free(find->value);
	find->value = ft_substr(var, chr - var + 1, ft_strlen(var));
	if (!find->value)
		return (0);
	return (1);
}

t_map	*add_env_var(t_map *env, char *key, char *value)
{
	char	*join;
	char	*env_str;
	t_map	*new_var;

	if (!key)
		return (NULL);
	join = ft_strjoin(key, "=");
	if (!join)
		return (NULL);
	if (value)
	{
		env_str = ft_strjoin(join, value);
		free(join);
		if (!env_str)
			return (NULL);
	}
	else
		env_str = join;
	new_var = create_new_var(env, env_str);
	free(env_str);
	return (new_var);
}

int	export(t_map *env, char **args)
{
	t_map	*find;
	char	*chr;
	int		exit_code;
	int		i;

	exit_code = 0;
	if (!check_first_arg(env, args, &exit_code))
		return (exit_code);
	i = 0;
	while (args[i])
	{
		chr = ft_strchr(args[i], '=');
		if (!chr)
		{
			i++;
			continue ;
		}
		find = get_env(env, args[i], chr - args[i]);
		if (!find && !create_new_var(env, args[i]))
			exit_code = 1;
		else if (find && !replace_var(find, args[i], chr))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
