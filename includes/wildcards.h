/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:46:20 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 13:17:26 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

# include "minishell.h"

typedef enum WILDCARD
{
	FILES,
	DIRECTORIES,
	BOTH
}	t_wildcard_type;

char	*get_wildcards(char *str, t_wildcard_type type, bool single_result);
bool	type_corresponding(struct dirent *entry, t_wildcard_type type);
void	free_wildcards(t_list *lst, DIR *dir);

#endif