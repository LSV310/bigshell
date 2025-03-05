/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:23:42 by agruet            #+#    #+#             */
/*   Updated: 2025/03/05 18:23:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

DIR	*search_directory(t_list **lst, char *str)
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
		if (entry->d_type == DT_REG || entry->d_type == DT_LNK)
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

void	compare_str(t_list **lst, t_list *elem, char *str)
{
	char	*content;
	char	*chr;

	content = elem->content;
	chr = ft_strchr(str, '*');
	if (!chr)
	{
		if (ft_strncmp(str, content, max(ft_strlen(str), ft_strlen(content))))
			lst_remove_node(lst, elem, &void_content);
		return ;
	}
	else if (ft_strncmp(str, content, chr - str))
	{
		lst_remove_node(lst, elem, &void_content);
		return ;
	}
	content += chr - str;
	while (*chr == '*')
		chr++;
	str = chr;
	chr = ft_strchr(str, '*');
	while (chr)
	{
		if (!ft_strlstr(content, str, chr - str))
		{
			lst_remove_node(lst, elem, &void_content);
			return ;
		}
		content += chr - str;
		str = chr + 1;
		chr = ft_strchr(str, '*');
	}
	if (!ft_strnstr(content, str, max(ft_strlen(str), ft_strlen(content))))
		lst_remove_node(lst, elem, &void_content);
}

char	*get_expanded(t_list *lst, DIR *dir)
{
	t_list	*current;
	int		count;
	char	*result;

	if (!lst)
		return (ft_lstclear(&lst, &void_content), closedir(dir), NULL);
	current = lst;
	count = 0;
	while (current)
	{
		count += ft_strlen(current->content) + 1;
		current = current->next;
	}
	result = calloc(count + 1, sizeof(char));
	current = lst;
	while (current)
	{
		ft_strlcat(result, current->content, ft_strlen(result) +
			ft_strlen(current->content) + 1);
		ft_strlcat(result, " ", ft_strlen(result) + 2);
		current = current->next;
	}
	result[count - 1] = 0;
	ft_lstclear(&lst, &void_content);
	return (closedir(dir), result);
}

char	*get_wildcards(char *str)
{
	DIR		*dir;
	t_list	*lst;
	t_list	*current;
	t_list	*next;

	lst = NULL;
	dir = search_directory(&lst, str);
	if (!dir)
		return (NULL);
	if(!lst)
		return (closedir(dir), NULL);
	current = lst;
	while (current)
	{
		next = current->next;
		compare_str(&lst, current, str);
		current = next;
	}
	return (get_expanded(lst, dir));
}
