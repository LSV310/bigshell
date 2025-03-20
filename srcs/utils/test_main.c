/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:35:14 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/20 01:02:49 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	// const char	*input =
	// "(< idk.txt echo *nomatch | grep -v \"idk| bro\" > outfile.txt) || ls | grep .txt";
	const char	*input = "echo -n \"bonjour tout le monde\" | wc && exit";
	t_shell		*shell = test_env();
	t_list		*tks = make_tokens(input, shell);
	t_ast		*ast;

	print_tokens(tks, false);
	ast = build_ast(tks, shell->arena);
	(void) ast;
	return (EXIT_SUCCESS);
}
