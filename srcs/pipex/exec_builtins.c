/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:11:37 by agruet            #+#    #+#             */
/*   Updated: 2025/04/04 11:12:35 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtins(t_list *cmdtk, t_shell *shell)
{
	t_cmd	*cmd;
	int		builtins;

	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	cmd = parse_cmd(cmdtk, shell->arena);
	if (!cmd || !cmd->name)
		return (1);
	builtins = try_builtins(cmd, shell, NULL);
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	if (shell->std_in != 0)
		close(shell->std_in);
	if (shell->std_out != 1)
		close(shell->std_out);
	shell->std_in = -1;
	shell->std_out = -1;
	update_last_code(shell, builtins);
	return (builtins);
}

int	try_builtins(t_cmd *cmd, t_shell *shell, char **env)
{
	if (!cmd->name)
		return (-1);
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
	{
		free_tab(env, 0);
		return (exit2(shell, ft_atoi(shell->env->value), &cmd->args[1]));
	}
	return (-1);
}

bool	is_cmd_builtin(t_list *tk)
{
	t_token	*token;

	while (tk && tk->content)
	{
		token = tk->content;
		if (token->type == NAME)
		{
			if (!ft_strcmp(token->str, "echo")
				|| !ft_strcmp(token->str, "cd")
				|| !ft_strcmp(token->str, "pwd")
				|| !ft_strcmp(token->str, "export")
				|| !ft_strcmp(token->str, "unset")
				|| !ft_strcmp(token->str, "env")
				|| !ft_strcmp(token->str, "exit"))
				return (true);
			else
				return (false);
		}
		if (!is_cmd_token(token))
			break ;
		tk = tk->next;
	}
	return (false);
}
