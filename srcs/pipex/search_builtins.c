/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:11:37 by agruet            #+#    #+#             */
/*   Updated: 2025/03/23 14:02:46 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	is_cmdtk_builtin(t_list *tk)
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
		tk = tk->next;
	}
}
