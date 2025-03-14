/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/14 13:51:29 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_envar(const char *cur, int *i, t_shell *shell)
{
	size_t		len;
	size_t		n;
	const char	*envar;

	n = 0;
	(*i)++;
	while (cur[*i] && !char_in_set(cur[*i], "\'\"$&|<>()# "))
	{
		(*i)++;
		n++;
	}
	if (n == 0)
		return (0);
	envar = get_env_value(shell->env, cur + *i - n, n);
	len = ft_strlen(envar);
	return (len);
}

size_t	write_envar(char *dst_p, char const *endest, const char **src_p, t_shell *shell)
{
	size_t		len;
	size_t		n;
	const char	*envar;
	size_t		envar_len;

	n = 0;
	*src_p += 1;
	while (**src_p && !char_in_set(**src_p, "\'\"$&|<>()# "))
	{
		*src_p += 1;
		n++;
	}
	envar = get_env_value(shell->env, *src_p - n, n);
	envar_len = ft_strlen(envar);
	if (dst_p + envar_len >= endest)
	{
		ft_printf("error: env value was bigger than buffer\n");
		return (0);
	}
	ft_memcpy(dst_p, envar, envar_len);
	return (envar_len);
}

void	fill_expanded(const char *src, char *dest, char const *dest_end, t_shell *env)
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

size_t	sizeof_expand(char *str, t_shell *env) // must keep the quotes
{
	size_t			n;
	int				i;
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
		return (NULL);
	fill_expanded(src, expanded, expanded + len, env);
	ft_printf("raw input: %s\n", src);
	ft_printf("expanded: %s\n", expanded);
	free(src);
	return (expanded);
}

/*
int	main(void)
{
	t_mini	mini;
	t_map	c = {.key = "PATH", .value = "expanded from path", .next = NULL};
	t_map	b = {.key = "GOAT", .value = "Tristan", .next = &c};
	t_map	a = {.key = "USER", .value = "tgallet", .next = &b};
	char	*src = "\"$GOAT\" \'$GOAT\'$GOATED $USER<$USER$PATH";

	mini.env = &a;
	printf("input: %s\n", src);
	char *expanded = expand_input(src, &mini);
	printf("Expanded: %s\n", expanded);
	free(expanded);
}
*/
