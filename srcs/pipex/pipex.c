/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/03/21 19:45:07 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	wait_childs(t_shell *shell, int cmd_amount, int last_pid)
{
	int		status;
	int		i;
	int		exit_code;
	char	*itoa_code;

	i = 0;
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
	exit_code = 1;
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = (128 + WTERMSIG(status));
	itoa_code = ft_itoa(exit_code);
	modify_var(shell->env, itoa_code);
	free(itoa_code);
}

static pid_t	exec_cmd(t_list *cmdtk, int *pipefd, t_shell *shell, char **env)
{
	t_cmd	*cmd;
	char	*cmd_name;
	int		builtins;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	else if (pid != 0)
		return (pid);
	restore_signals();
	dup2(pipefd[1], STDOUT_FILENO);
	(close(pipefd[0]), close(pipefd[1]));
	cmd = parse_cmd(cmdtk, shell->arena);
	if (!cmd)
		(free_tab(env, 0), exit2(shell, EXIT_FAILURE, NULL));
	builtins = try_builtins(cmd, shell);
	if (builtins >= 0)
		return (free_tab(env, 0), exit2(shell, builtins, NULL));
	cmd_name = search_cmd(cmd->name, env);
	if (!cmd_name)
		(free_tab(env, 0), exit2(shell, EXIT_FAILURE, NULL));
	execve(cmd_name, cmd->args, env);
	perror("minishell");
	return ((free_tab(env, 0), exit2(shell, EXIT_FAILURE, NULL)));
}

char	**init_pipex(t_shell *shell, int *pipefd)
{
	char	**env;
	int		std_in;

	std_in = dup(STDIN_FILENO);
	if (std_in == -1)
		return (NULL);
	shell->std_in = std_in;
	env = convert_env(shell->env->next);
	if (!env)
		return (NULL);
	pipefd[0] = 0;
	pipefd[1] = 0;
	return (env);
}

int	pipex(t_list **tks, t_shell *shell)
{
	int		pipefd[2];
	int		i;
	pid_t	last_pid;
	char	**env;

	env = init_pipex(shell, pipefd);
	if (!env)
		return (1);
	i = 0;
	while (tks[i])
	{
		pipe(pipefd);
		if (!tks[i + 1])
			dup2(STDOUT_FILENO, pipefd[1]);
		last_pid = exec_cmd(tks[i], pipefd, shell, env);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (last_pid == -1)
			break ;
		i++;
	}
	free_tab(env, 0);
	return (wait_childs(shell, i, last_pid));
}
