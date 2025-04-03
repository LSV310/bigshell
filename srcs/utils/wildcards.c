/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:23:42 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 13:44:39 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

DIR	*search_directory(t_list **lst, t_wildcard_type type)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*new;

	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (type_corresponding(entry, type))
		{
			new = ft_lstnew(entry->d_name);
			if (!new)
			{
				ft_lstclear(lst, &void_content);
				return (dir);
			}
			ft_lstadd_back(lst, new);
		}
		entry = readdir(dir);
	}
	return (dir);
}

bool	wildcard_cmp(char *content, char *pattern)
{
	if (*pattern == '\0')
	{
		if (*content == '\0')
			return (true);
		return (false);
	}
	else if (*pattern == '*')
		return ((*content && wildcard_cmp(content + 1, pattern))
			|| wildcard_cmp(content, pattern + 1));
	else
	{
		if (*pattern == *content)
			return (wildcard_cmp(content + 1, pattern + 1));
		else
			return (false);
	}
}

void	compare_str(t_list **lst, t_list *elem, char *str)
{
	char	*content;

	content = elem->content;
	if (!wildcard_cmp(content, str))
		lst_remove_node(lst, elem, &void_content);
}

char	*get_expanded(t_list *lst, DIR *dir, char *str)
{
	t_list	*current;
	int		count;
	char	*result;

	if (!lst)
		return (free_wildcards(lst, dir), ft_strdup(str));
	current = lst;
	count = 0;
	while (current)
	{
		count += ft_strlen(current->content) + 1;
		current = current->next;
	}
	result = ft_calloc(count + 1, sizeof(char));
	current = lst;
	while (current)
	{
		ft_strlcat(result, current->content, ft_strlen(result)
			+ ft_strlen(current->content) + 1);
		ft_strlcat(result, " ", ft_strlen(result) + 2);
		current = current->next;
	}
	result[count - 1] = 0;
	return (free_wildcards(lst, dir), result);
}

char	*get_wildcards(char *str, t_wildcard_type type, bool single_result)
{
	DIR		*dir;
	t_list	*lst;
	t_list	*current;
	t_list	*next;

	if (!str)
		return (NULL);
	if (!ft_strchr(str, '*'))
		return (ft_strdup(str));
	lst = NULL;
	dir = search_directory(&lst, type);
	if (!dir)
		return (NULL);
	if (!lst)
		return (closedir(dir), ft_strdup(str));
	current = lst;
	while (current)
	{
		next = current->next;
		compare_str(&lst, current, str);
		current = next;
	}
	if (type == FILES && single_result == true && ft_lstsize(lst) > 1)
		return (free_wildcards(lst, dir), NULL);
	return (get_expanded(lst, dir, str));
}
