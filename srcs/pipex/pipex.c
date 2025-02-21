/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/02/21 18:15:50 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_child(pid_t pid, int *exit_code, int last)
{
	int	status;

	if (pid == 0)
	{
		*exit_code = 127;
		ft_fprintf(2, "pipex: command not found\n");
		return ;
	}
	if (!last)
		waitpid(pid, &status, WNOHANG);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_code = 128 + WTERMSIG(status);
	else
		*exit_code = 1;
}

pid_t	exec_cmd(char *cmd, int *pipefd, int outfile)
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
		(close(pipefd[0]), close(pipefd[1]), close(outfile));
		execve(cmd, args, __environ);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	free_cmd(cmd, args);
	return (pid);
}

int	pipex(char **cmds, int nbr, int outfile)
{
	int	pipefd[2];
	int	exit_code;
	int	i;

	exit_code = 0;
	pipe(pipefd);
	exec_cmd(cmds[0], pipefd, outfile);
	i = 1;
	while (i < nbr)
	{
		dup2(pipefd[0], STDIN_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
		pipe(pipefd);
		if (i == nbr - 1)
			dup2(outfile, pipefd[1]);
		exec_cmd(cmds[i], pipefd, outfile);
		i++;
	}
	(close(pipefd[0]), close(pipefd[1]));
	return (exit_code);
}
