/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:43:31 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 15:13:59 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

/*
** arg types
** DIR = 1
** INDIR = 2
** REG = 3
** DIR || INDIR = 4
** DIR || REG = 5
** INDIR || REG = 6
** DIR || INDIR || REG = 7
*/

int		next_arg(t_pars *parser, int type, int size, char **bytecode)
{
	if ((parser->token->type == DIRECT || parser->token->type == DIRECT_LABEL)
			&& (write_dir(parser, size, bytecode))
			&& (type == 1 || type == 4 || type == 5 || type == 7))
	{
		parser->token = parser->token->next;
		return (1);
	}
	else if ((parser->token->type == INDIRECT
				|| parser->token->type == INDIRECT_LABEL)
			&& (write_indir(parser, bytecode))
			&& (type == 2 || type == 4 || type == 6 || type == 7))
	{
		parser->token = parser->token->next;
		return (1);
	}
	else if ((parser->token->type == REGISTER)
			&& (write_reg(parser, bytecode))
			&& (type == 3 || type == 5 || type == 6 || type == 7))
	{
		parser->token = parser->token->next;
		return (1);
	}
	return (errors_handler(2, parser->token->line, parser->token->column));
}

int		find_value(t_pars *parser)
{
	t_ment	*head;
	int		i;

	head = parser->mention;
	i = -1;
	while (parser->mention
			&& (ft_strcmp(parser->mention->name, parser->token->content)))
		parser->mention = parser->mention->next;
	if (parser->mention)
		i = parser->mention->byte - parser->f_head + 1;
	parser->mention = head;
	return (i);
}

int		write_dir(t_pars *pars, size_t size, char **code)
{
	int	num;

	if (!(pars->token->content))
		return (errors_handler(0, pars->token->line, pars->token->column));
	if (pars->token->type == DIRECT_LABEL)
	{
		if ((num = find_value(pars)) == -1)
			return (errors_handler(1, pars->token->line, pars->token->column));
		int_to_byte(*code, pars->i, num, size);
	}
	else if (pars->token->type == DIRECT)
		int_to_byte(*code, pars->i, ft_atoi_asm(pars->token->content), size);
	else
		return (errors_handler(2, pars->token->line, pars->token->column));
	pars->i += size;
	return (1);
}

int		write_indir(t_pars *pars, char **cd)
{
	int	num;

	if (!(pars->token->content))
		return (errors_handler(0, pars->token->line, pars->token->column));
	if (pars->token->type == INDIRECT_LABEL)
	{
		if ((num = find_value(pars)) == -1)
			return (errors_handler(1, pars->token->line, pars->token->column));
		int_to_byte(*cd, pars->i, num, IND_SIZE);
	}
	else if (pars->token->type == INDIRECT)
		int_to_byte(*cd, pars->i, ft_atoi_asm(pars->token->content), IND_SIZE);
	else
		return (errors_handler(2, pars->token->line, pars->token->column));
	pars->i += IND_SIZE;
	return (1);
}

int		write_reg(t_pars *pars, char **code)
{
	if (!(pars->token->content))
		return (errors_handler(0, pars->token->line, pars->token->column));
	if (pars->token->type == REGISTER)
		int_to_byte(*code, pars->i, ft_atoi_asm(pars->token->content), 1);
	else
		return (errors_handler(1, pars->token->line, pars->token->column));
	pars->i += 1;
	return (1);
}
