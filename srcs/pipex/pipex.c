/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/03/07 12:05:20 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_childs(int cmd_amount, int last_pid)
{
	int	status;
	int	i;

	i = 0;
	while (i++ < cmd_amount - 1)
		waitpid(-1, &status, 0);
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	dupfds(t_cmd *cmds, int *pipefd)
{
	if (cmds->fdin != 0)
		dup2(cmds->fdin, STDIN_FILENO);
	else
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (cmds->fdout != 1)
		dup2(cmds->fdout, pipefd[1]);
}

pid_t	exec_cmd(t_cmd *cmd, int *pipefd, t_mini *mini, char **env)
{
	char	*cmd_name;
	pid_t	pid;

	cmd_name = search_cmd(cmd->name, env);
	if (!cmd_name)
		return (0);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
		execve(cmd_name, cmd->args, env);
		perror("pipex");
		exit2(mini, EXIT_FAILURE);
	}
	return (pid);
}

int	pipex(t_cmd **cmds, t_mini *mini)
{
	int		pipefd[2];
	int		i;
	pid_t	last_pid;
	char	**env;

	i = 0;
	env = convert_env(mini->env);
	if (!env)
		return (1);
	while (cmds[i])
	{
		if (pipefd[1])
			close(pipefd[1]);
		pipe(pipefd);
		dupfds(cmds[i], pipefd);
		last_pid = exec_cmd(cmds[i], pipefd, mini, env);
		if (last_pid == -1)
			return (close(pipefd[1]), (pipefd[1] = 0), 1);
		i++;
	}
	close(pipefd[1]);
	return (wait_childs(i, last_pid));
}
