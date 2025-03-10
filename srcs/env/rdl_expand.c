/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdl_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/10 17:27:49 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_envar(const char *cur, int *i, t_mini *env)
{
	size_t		len;
	size_t		n;
	const char	*envar;

	n = 0;
	(*i)++;
	while (cur[*i] && !char_in_set(cur[*i], "\"$&|<>()# "))
	{
		(*i)++;
		n++;
	}
	if (n == 0)
		return (0);
	envar = get_env_value(env, cur + *i - n, n);
	len = ft_strlen(envar);
	return (len);
}

size_t	write_envar(char *dst_p, char const *endest, const char **src_p, t_mini *env)
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
	envar = get_env_value(env, *src_p - n, n);
	envar_len = ft_strlen(envar);
	if (dst_p + envar_len >= endest)
	{
		printf("error: env value was bigger than buffer\n");
		return (0);
	}
	ft_memcpy(dst_p, envar, envar_len);
	return (envar_len);
}

void	fill_expanded(const char *rdl, char *dest, char const *dest_end, t_mini *env)
{
	char			quote;

	quote = 0;
	while (*rdl && dest < dest_end)
	{
		if (!quote && char_in_set(*rdl, "\"'"))
			quote = *rdl;
		else if (*rdl == quote)
			quote = 0;
		if ((!quote || quote == '"') && *rdl == '$')
			dest += write_envar(dest, dest_end, &rdl, env);
		else
		{
			*dest = *rdl;
			dest++;
			rdl++;
		}
	}
}

size_t	sizeof_expand(char *str, t_mini *env)
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

char	*expand_input(char *rdl, t_mini *env)
{
	char	*expanded;
	size_t	len;

	len = sizeof_expand(rdl, env);
	expanded = ft_calloc(len, sizeof(char));
	if (!expanded)
		return (NULL);
	fill_expanded(rdl, expanded, expanded + len, env);
	printf("raw input: %s\n", rdl);
	printf("expanded: %s\n", expanded);
	return (expanded);
}
/*
int	main(void)
{
	t_mini	mini;
	t_map	c = {.key = "PATH", .value = "expanded from path", .next = NULL};
	t_map	b = {.key = "GOAT", .value = "Tristan", .next = &c};
	t_map	a = {.key = "USER", .value = "tgallet", .next = &b};
	char	*rdl = "\"$GOAT\" \'$GOAT\'$GOATED $USER<$USER$PATH";

	mini.env = &a;
	printf("input: %s\n", rdl);
	char *expanded = expand_input(rdl, &mini);
	printf("Expanded: %s\n", expanded);
	free(expanded);
}
*/
