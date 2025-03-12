/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:17:55 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 11:28:33 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_map	*create_new_var(t_map *env, char *var)
{
	t_map	*new;

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

static int	printenv(t_map *env)
{
	t_map	*current;

	if (!env)
		return (1);
	current = env->next;
	while (current)
	{
		ft_printf("export %s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
	return (0);
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

int	export(t_map *env, char *var)
{
	t_map	*find;
	char	*chr;

	if (!var)
		return (printenv(env));
	chr = ft_strchr(var, '=');
	if (!chr)
		return (0);
	find = get_env(env, var, chr - var);
	if (!find && !create_new_var(env, var))
		return (1);
	else if (!replace_var(find, var, chr))
		return (1);
	return (0);
}
