/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 16:33:28 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd_name(t_cmd	*cmd, t_shell *shell, char **env)
{
	int		builtins;
	int		exit_code;
	char	*cmd_name;

	if (!cmd || !cmd->name)
		(free_tab(env, 0), exit2(shell, EXIT_FAILURE, NULL));
	builtins = try_builtins(cmd, shell, env);
	if (builtins >= 0)
		(free_tab(env, 0), exit2(shell, builtins, NULL));
	cmd_name = search_cmd(cmd->name, env, &exit_code);
	if (!cmd_name)
		(free_tab(env, 0), exit2(shell, exit_code, NULL));
	return (cmd_name);
}

static pid_t	exec_cmd(t_list *cmdtk, int *pipefd, t_shell *shell, char **env)
{
	t_cmd	*cmd;
	char	*cmd_name;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid != 0)
		return (pid);
	child_signal();
	dup2(pipefd[1], STDOUT_FILENO);
	(close(pipefd[0]), close(pipefd[1]));
	cmd = parse_cmd(cmdtk, shell->arena);
	cmd_name = get_cmd_name(cmd, shell, env);
	if (shell->std_in)
		close(shell->std_in);
	shell->std_in = -1;
	execve(cmd_name, cmd->args, env);
	if (errno == 13)
		return (perror(cmd_name), (free_tab(env, 0), exit2(shell, 127, NULL)));
	return ((free_tab(env, 0), exit2(shell, EXIT_SUCCESS, NULL)));
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

int	pipex(t_list **cmd_arr, t_shell *shell)
{
	int		pipefd[2];
	int		i;
	pid_t	last_pid;
	char	**env;

	if (cmd_arr && cmd_arr[0] && !cmd_arr[1] && is_cmd_builtin(*cmd_arr))
		return (exec_builtins(*cmd_arr, shell));
	env = init_pipex(shell, pipefd);
	if (!env)
		return (1);
	i = 0;
	while (cmd_arr[i])
	{
		pipe(pipefd);
		if (!cmd_arr[i + 1])
			dup2(STDOUT_FILENO, pipefd[1]);
		last_pid = exec_cmd(cmd_arr[i], pipefd, shell, env);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (last_pid == -1)
			break ;
		i++;
	}
	return (wait_childs(shell, i, last_pid, env));
}
