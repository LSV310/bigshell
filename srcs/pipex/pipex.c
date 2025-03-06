/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/03/06 12:41:42 by agruet           ###   ########.fr       */
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
	else
		return (1);
}

pid_t	exec_cmd(t_cmd *cmd, int *pipefd, t_mini *mini)
{
	// char	*cmd;
	pid_t	pid;
	char	**env;

	/* cmd = parse_env(cmd);
	if (!cmd)
		return (0); */
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
		env = convert_env(mini->env);
		if (!env)
			exit2(mini, 1);
		execve(cmd->cmd, cmd->args, env);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	pipex(t_cmd **cmds, t_mini *mini)
{
	int		pipefd[2];
	int		exit_code;
	int		i;
	pid_t	last_pid;

	i = 0;
	while (cmds[i])
	{
		if (pipefd[1])
			close(pipefd[1]);
		pipe(pipefd);
		if (cmds[i]->fdin != -1)
			dup2(cmds[i]->fdin, STDIN_FILENO);
		else
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		if (cmds[i]->fdout != -1)
			dup2(cmds[i]->fdout, pipefd[1]);
		last_pid = exec_cmd(cmds[i], pipefd, mini);
	}
	close(pipefd[1]);
	return (wait_childs(i, last_pid));
}
