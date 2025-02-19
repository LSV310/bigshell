/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:32:24 by agruet            #+#    #+#             */
/*   Updated: 2025/02/19 12:23:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef enum
{
	INVALID = 0,
	NAME,

} token_type;

typedef struct s_token
{
	const char	*s;
	size_t		len;
	token_type	type;
}	t_token;
