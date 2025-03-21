/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:11:37 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 16:26:35 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	try_builtins(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->name, "echo"))
		return (echo(&cmd->args[1]));
	if (!ft_strcmp(cmd->name, "cd"))
		return (cd(shell->env, &cmd->args[1]));
	if (!ft_strcmp(cmd->name, "pwd"))
		return (pwd(&cmd->args[1]));
	if (!ft_strcmp(cmd->name, "export"))
		return (export(shell->env, &cmd->args[1]));
	if (!ft_strcmp(cmd->name, "unset"))
		return (unset(shell->env, &cmd->args[1]));
	if (!ft_strcmp(cmd->name, "env"))
		return (env2(shell->env, &cmd->args[1]));
	if (!ft_strcmp(cmd->name, "exit"))
		return (exit2(shell, EXIT_SUCCESS, &cmd->args[1]));
	return (-1);
}
