/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:54:01 by agruet            #+#    #+#             */
/*   Updated: 2025/03/24 13:57:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_last_code(t_shell *shell, int exit_code)
{
	char	*itoa_code;

	itoa_code = ft_itoa(exit_code);
	modify_var(shell->env, itoa_code);
	free(itoa_code);
}

int	get_exit_code(int *status, t_shell *shell)
{
	int exit_code;

	exit_code = 1;
	if (WIFEXITED(*status))
		exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		ft_fprintf(2, "\n");
		exit_code = (128 + WTERMSIG(*status));
	}
	return (exit_code);
}

int	wait_childs(t_shell *shell, int cmd_amount, int last_pid, char **env)
{
	int		status;
	int		i;
	int		exit_code;

	i = 0;
	free_tab(env, 0);
	if (shell->std_in != -1)
		dup2(shell->std_in, STDIN_FILENO);
	close(shell->std_in);
	shell->std_in = -1;
	if (cmd_amount <= 0)
		return (0);
	if (last_pid != -1)
		waitpid(last_pid, &status, 0);
	while (i++ < cmd_amount - 1)
		waitpid(-1, NULL, 0);
	exit_code = get_exit_code(&status, shell);
	update_last_code(shell, exit_code);
	return (exit_code);
}
