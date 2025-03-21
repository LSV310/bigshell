/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:35:14 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/20 16:10:07 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf("command name: %s\n", cmd->name);
	i = 0;
	while (cmd->args[i])
	{
		printf("%s\n", cmd->args[i]);
		i++;
	}
}

int	main(void)
{
	// const char	*input =
	// "(< idk.txt echo *nomatch | grep -v \"idk| bro\" > outfile.txt) || ls | grep .txt";
	const char	*input = "< Makefile cat | wc -l";
	t_shell		*shell = test_env();
	t_list		*tks = make_tokens(input, shell);
	t_ast		*ast;
	t_list 		**pipelines = ptr_arr_pipeline(tks, shell->arena);
	t_cmd		*cmd = parse_cmd(pipelines[0]);

	print_cmd(cmd);
	print_tokens(tks, false);
	ast = build_ast(tks, shell->arena);
	(void) ast;
	return (EXIT_SUCCESS);
}
