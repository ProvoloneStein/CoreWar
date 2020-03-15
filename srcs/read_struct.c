/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:33:30 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 15:36:20 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

static int	what_function2(t_pars *parser, char **bytecode)
{
	if (!ft_strcmp(parser->token->content, "xor"))
		return (ft_xor(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "zjmp"))
		return (ft_zjmp(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "sti"))
		return (ft_sti(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "fork"))
		return (ft_fork(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "lldi"))
		return (ft_lldi(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "lld"))
		return (ft_lld(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "lfork"))
		return (ft_lfork(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "aff"))
		return (ft_aff(parser, bytecode));
	return (0);
}

int			what_function(t_pars *parser, char **bytecode)
{
	if (!ft_strcmp(parser->token->content, "live"))
		return (ft_live(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "ldi"))
		return (ft_ldi(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "ld"))
		return (ft_ld(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "st"))
		return (ft_st(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "add"))
		return (ft_add(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "sub"))
		return (ft_sub(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "and"))
		return (ft_and(parser, bytecode));
	else if (!ft_strcmp(parser->token->content, "or"))
		return (ft_or(parser, bytecode));
	return (what_function2(parser, bytecode));
}

int			make_code(t_pars *pars, char **bytecode)
{
	t_token	*head;

	head = pars->token;
	while (pars->token->type == NAME || pars->token->type == COMMENT)
		pars->token = pars->token->next;
	if (pars->token->type == END)
		return (errors_handler(6, pars->token->line, pars->token->column));
	while (pars->token && pars->token->type != END)
	{
		if (pars->token->type == INSTRUCTION)
		{
			pars->f_head = pars->token->byte;
			if (what_function(pars, bytecode))
				continue;
			return (errors_handler(7, pars->token->line, pars->token->column));
		}
		else if (pars->token->type == LABEL)
			pars->token = pars->token->next;
		else
			return (errors_handler(4, pars->token->line, pars->token->column));
	}
	pars->token = head;
	return (1);
}
