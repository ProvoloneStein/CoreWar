/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:01:07 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 16:44:47 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int	make_com(t_pars *parser, int *i)
{
	if (parser->token && parser->token->type == COMMENT && *i == 0)
	{
		if (ft_strlen(parser->token->content) <= COMMENT_LENGTH)
		{
			parser->comment = parser->token->content;
			(*i)++;
			parser->token = parser->token->next;
		}
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

int	make_name(t_pars *parser, int *i)
{
	if (parser->token && parser->token->type == NAME && *i == 0)
	{
		if (ft_strlen(parser->token->content) <= PROG_NAME_LENGTH)
		{
			parser->name = parser->token->content;
			(*i)++;
			parser->token = parser->token->next;
		}
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

int	check_commands(t_pars *parser)
{
	t_token	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	head = parser->token;
	while (parser->token
			&& (parser->token->type == NAME || parser->token->type == COMMENT))
	{
		if (make_name(parser, &i) || make_com(parser, &j))
			continue;
		return (errors_handler(3, parser->token->line, parser->token->column));
	}
	if (i != 1 || j != 1)
		return (errors_handler(3, parser->token->line, parser->token->column));
	parser->token = head;
	return (1);
}
