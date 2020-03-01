/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:01:07 by pstein            #+#    #+#             */
/*   Updated: 2020/03/01 17:33:31 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int	make_com(t_pars *parser)
{
	if (parser->token->type == COMMENT && parser->comment == NULL)
	{
		if (ft_strlen(parser->token->content) <= COMMENT_LENGTH)
		{
			parser->comment = parser->token->content;
			parser->token = parser->token->next;
		}
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

int	make_name(t_pars *parser)
{
	if (parser->token->type == NAME && parser->name == NULL)
	{
		if (ft_strlen(parser->token->content) <= PROG_NAME_LENGTH)
		{
			parser->name = parser->token->content;
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

	head = parser->token;
	while (parser->token
			&& (parser->token->type == NAME || parser->token->type == COMMENT))
	{
		if (make_name(parser) || make_com(parser))
			continue;
		error_handler(3, parser->token->line, parser->token->column);
		parser->token = head;
		return (0);
	}
	parser->token = head;
	return (1);
}
