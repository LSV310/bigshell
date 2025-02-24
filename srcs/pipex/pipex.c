/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/02/24 13:07:59 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_childs(int cmd_amount)
{
	int	status;
	int	i;

	i = 0;
	while (i++ < cmd_amount)
		waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

pid_t	exec_cmd(char *cmd, int *pipefd)
{
	char	*cmd;
	char	**args;
	pid_t	pid;

	//set args to the cmd args
	cmd = parse_env(args[0], args);
	if (!cmd)
		return (free_cmd(NULL, args), 0);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		// Free everything
		dup2(pipefd[1], STDOUT_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
		execve(cmd, args, __environ);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	free_cmd(cmd, args);
	return (pid);
}

int	pipex(char **cmds, int infile, int outfile)
{
	int	pipefd[2];
	int	exit_code;
	int	i;

	i = 0;
	while (cmds[i])
	{
		// open REDIN / REDOUT of the current function
		dup2(pipefd[0], STDIN_FILENO); //conditional: either pipefd[0] or redin or nothing (if first)
		(close(pipefd[0]), close(pipefd[1])); // only if i > 0
		pipe(pipefd);
		// if redout dup2(redout, pipefd[1])
		exec_cmd(cmds[i], pipefd);
	}
	(close(pipefd[0]), close(pipefd[1]));
	(close(infile), close(outfile));
	return (wait_childs(i));
}
