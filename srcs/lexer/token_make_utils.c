/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_make_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:38:10 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/20 12:55:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// count characters including quotes and stops at unquoted (space or special)
void	fill_token(t_lexer *lex, t_token *tok, t_token_type type)
{
	char	quote;

	quote = 0;
	tok->p = lex->cur;
	tok->type = type;
	while (*lex->cur != '\0' && (quote || !ft_isspace(*lex->cur))
		&& !(quote == 0 && is_special(*lex->cur)))
	{
		if (quote == 0 && char_in_set(*lex->cur, "\"\'"))
			quote = *lex->cur;
		else if (quote == *lex->cur)
			quote = 0;
		tok->len++;
		lex->cur++;
	}
}

void	make_end_token(t_lexer *lex, t_token *tok)
{
	tok->type = ENDT;
	tok->len = 0;
	tok->p = lex->cur;
}

void	bad_token(t_lexer *lex, t_token *tok)
{
	tok->p = lex->cur;
	tok->type = INVALID;
	while (*lex->cur && !ft_isspace(*lex->cur))
	{
		tok->len++;
		lex->cur++;
	}
}

t_shell	*test_env(void)
{
	t_shell	*shell;
	t_map	*env;
	t_map	*env2;

	shell = malloc(sizeof(t_shell));
	shell->arena = arena_init();
	shell->history = NULL;
	env = malloc(sizeof(t_map));
	env->key = "GOAT";
	env->value = "Tristan";
	env2 = malloc(sizeof(t_map));
	env2->key = "PATH";
	env2->value = "CHEMIN";
	env->next = env2;
	env2->next = NULL;
	shell->env = env;
	return (shell);
}
