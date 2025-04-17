/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:35:24 by agruet            #+#    #+#             */
/*   Updated: 2025/04/17 17:19:28 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	type_corresponding(struct dirent *entry, t_wildcard_type type)
{
	if (entry->d_name[0] == '.')
		return (false);
	if (entry->d_type == DT_REG || entry->d_type == DT_LNK)
	{
		if (type == FILES || type == BOTH)
			return (true);
	}
	else if (entry->d_type == DT_DIR)
	{
		if (type == DIRECTORIES || type == BOTH)
			return (true);
	}
	return (false);
}

void	free_wildcards(t_list *lst, DIR *dir)
{
	ft_lstclear(&lst, &void_content);
	closedir(dir);
}

int	get_wc_expand_size(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count += ft_strlen(lst->content) + 1;
		lst = lst->next;
	}
	return (count);
}
