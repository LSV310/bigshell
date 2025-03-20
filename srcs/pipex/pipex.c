/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 16:51:47 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	wait_childs(int cmd_amount, int last_pid)
{
	int	status;
	int	i;

	i = 0;
	if (last_pid != -1)
		waitpid(last_pid, &status, 0);
	while (i++ < cmd_amount - 1)
		waitpid(-1, NULL, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static pid_t	exec_cmd(t_list *cmdtk, int *pipefd, t_shell *shell, char **env)
{
	t_cmd	*cmd;
	char	*cmd_name;
	int		builtins;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid != 0)
		return (pid);
	restore_signals();
	cmd = parse_cmd(cmdtk);
	if (!cmd)
		return (exit2(shell, EXIT_FAILURE, NULL));
	(close(pipefd[0]), close(pipefd[1]));
	builtins = try_builtins(cmd, shell);
	if (builtins >= 0)
		exit2(shell, builtins, NULL);
	cmd_name = search_cmd(cmd->name, env);
	if (!cmd_name)
		exit2(shell, EXIT_FAILURE, NULL);
	execve(cmd_name, cmd->args, env);
	perror("pipex");
	return (exit2(shell, EXIT_FAILURE, NULL));
}

int	pipex(t_list **tks, t_shell *shell)
{
	int		pipefd[2];
	int		i;
	pid_t	last_pid;
	char	**env;

	i = 0;
	env = convert_env(shell->env->next);
	if (!env)
		return (1);
	pipefd[0] = 0;
	pipefd[1] = 0;
	while (tks[i])
	{
		if (pipefd[0])
			(dup2(pipefd[0], STDIN_FILENO), close(pipefd[0]));
		pipe(pipefd);
		close(pipefd[1]);
		last_pid = exec_cmd(tks[i], pipefd, shell, env);
		if (last_pid == -1)
			break ;
		i++;
	}
	close(pipefd[0]);
	free_tab(env, 0);
	return (wait_childs(i, last_pid));
}
