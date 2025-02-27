/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:06:36 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/27 17:27:14 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_variable(const char *key, size_t n, void *env)
{
	const t_kv	dummy[] = {
	{.key = "GOAT", .value = "tristan"},
	{.key = "OUT", .value = "outfile.txt"},
	{.key = "IN", .value = "infile.txt"}
	};
	int			i;

	i = 0;
	while (i < sizeof(dummy) / sizeof(t_kv))
	{
		if (ft_strncmp(key, dummy[i].key, n) == 0)
		{
			return (dummy[i].value);
		}
		i++;
	}
	if (env)
		printf("env exists\n");
	return ("");
}
