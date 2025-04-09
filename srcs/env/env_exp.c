/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/09 15:40:28 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_envar(const char *cur, size_t *i, t_shell *shell)
{
	size_t		len;
	size_t		n;
	const char	*envar;

	n = 0;
	(*i)++;
	while (cur[*i] && !char_in_set(cur[*i], ENVN_STOP))
	{
		(*i)++;
		n++;
	}
	if (n == 0 && cur[*i] == '?')
	{
		n++;
		(*i)++;
	}
	if (!n)
		return (1);
	envar = get_env_value(shell->env, cur + *i - n, n);
	len = ft_strlen(envar);
	return (len);
}

size_t	write_envar(char *dst_p, char const *endest,
	const char **src_p, t_shell *shell)
{
	size_t		n;
	const char	*envar;
	size_t		envar_len;

	n = 0;
	*src_p += 1;
	while (**src_p && !char_in_set(**src_p, ENVN_STOP))
	{
		*src_p += 1;
		n++;
	}
	if (n == 0 && **src_p == '?')
	{
		n++;
		*src_p += 1;
	}
	if (!n)
		return (ft_memmove(dst_p, "$", 1), 1);
	envar = get_env_value(shell->env, *src_p - n, n);
	envar_len = ft_strlen(envar);
	if (dst_p + envar_len >= endest)
		return (0);
	ft_memmove(dst_p, envar, envar_len);
	return (envar_len);
}

void	fill_expanded(const char *src, char *dest,
	char const *dest_end, t_shell *env)
{
	char			quote;

	quote = 0;
	while (*src && dest < dest_end)
	{
		if (!quote && char_in_set(*src, "\"'"))
			quote = *src;
		else if (*src == quote)
			quote = 0;
		if ((!quote || quote == '"') && *src == '$')
			dest += write_envar(dest, dest_end, &src, env);
		else
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
}

size_t	sizeof_expand(char *str, t_shell *env)
{
	size_t			n;
	size_t			i;
	char			quote;
	const size_t	strlen = ft_strlen(str);

	i = 0;
	n = 0;
	quote = 0;
	while (i < strlen)
	{
		if (!quote && char_in_set(str[i], "\"'"))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		if ((!quote || quote == '"') && str[i] == '$')
			n += size_envar(str, &i, env);
		else
		{
			n++;
			i++;
		}
	}
	return (n + 1);
}

char	*env_exp(char *src, t_shell *env)
{
	char	*expanded;
	size_t	len;

	if (!src)
		return (NULL);
	len = sizeof_expand(src, env);
	expanded = ft_calloc(len, sizeof(char));
	if (!expanded)
	{
		free(src);
		return (NULL);
	}
	fill_expanded(src, expanded, expanded + len, env);
	free(src);
	return (expanded);
}
