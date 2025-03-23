/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:32:21 by agruet            #+#    #+#             */
/*   Updated: 2025/03/23 21:24:44 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipe
{
	int	read_fd;
	int	write_fd;
}	t_pipe;

typedef struct s_shell	t_shell;

char	*search_cmd(char *cmd, char **env, int *exit_code);
int		wait_childs(t_shell *shell, int cmd_amount, int last_pid, char **env);
bool	is_cmd_builtin(t_list *tk);
int		exec_builtins(t_list *cmdtk, t_shell *shell);
void	update_last_code(t_shell *shell, int exit_code);

#endif
