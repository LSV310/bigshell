/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:06:36 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/26 16:03:32 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//dummy function
char	*get_env_variable(const char *key, size_t n, void *env)
{
	const t_kv	dummy[] = {
	{.key = "goat", .value = "tristan"},
	{.key = "out", .value = "outfile.txt"},
	{.key = "in", .value = "infile.txt"}
	};
	int			i;

	i = 0;
	while (i < sizeof(dummy) / sizeof(t_kv))
	{
		if (ft_strcmp(key, dummy[i].key) == 0)
			return (dummy[i].value);
		i++;
	}
	if (env)
		printf("env exists\n");
	return ("");
}
