/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:23:42 by agruet            #+#    #+#             */
/*   Updated: 2025/03/21 13:46:32 by agruet           ###   ########.fr       */
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

void	finish_cmp(t_list **lst, t_list *elem, char *content, char *chr)
{
	char	*str;
	char	*find;

	while (*chr == '*')
		chr++;
	str = chr;
	chr = ft_strchr(str, '*');
	while (chr)
	{
		find = ft_strlstr(content, str, chr - str);
		if (!find)
		{
			lst_remove_node(lst, elem, &void_content);
			return ;
		}
		content = find + (chr - str);
		str = chr;
		while (str && *str == '*')
			str++;
		chr = ft_strchr(str, '*');
	}
	if (*str && ft_strrcmp(content, str))
		lst_remove_node(lst, elem, &void_content);
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
	finish_cmp(lst, elem, content, chr);
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
