/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:32:21 by agruet            #+#    #+#             */
/*   Updated: 2025/02/24 15:59:44 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

char	*parse_env(char **envp, char *cmd, char **args);
void	free_cmd(char *cmd, char **args);

#endif
