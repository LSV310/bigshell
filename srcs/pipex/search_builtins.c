/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:11:37 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 16:27:43 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	try_builtins(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->cmd, "echo"))
		return (echo(&cmd->args[1]));
	if (ft_strcmp(cmd->cmd, "cd"))
		return (cd(shell->env, &cmd->args[1]));
	if (ft_strcmp(cmd->cmd, "pwd"))
		return (pwd());
	if (ft_strcmp(cmd->cmd, "export"))
		return (export(shell->env, &cmd->args[1]));
	if (ft_strcmp(cmd->cmd, "unset"))
		return (unset(shell->env, &cmd->args[1]));
	if (ft_strcmp(cmd->cmd, "env"))
		return (env2(shell->env));
	if (ft_strcmp(cmd->cmd, "exit"))
		exit2(shell, EXIT_SUCCESS, &cmd->args[1]);
	return (-1);
}
